/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "FollowMovementGenerator.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "Optional.h"
#include "PathGenerator.h"
#include "Pet.h"
#include "Unit.h"
#include "Util.h"
#include "TSCreature.h"

static void DoMovementInform(Unit* owner, Unit* target)
{
    if (owner->GetTypeId() != TYPEID_UNIT)
        return;

    if (CreatureAI* AI = owner->ToCreature()->AI())
        AI->MovementInform(FOLLOW_MOTION_TYPE, target->GetGUID().GetCounter());

    // @tswow-begin
    if (owner->IsCreature()) {
        FIRE_ID(owner->ToCreature()->GetCreatureTemplate()->events.id,Creature,OnMovementInform,TSCreature(owner->ToCreature()),FOLLOW_MOTION_TYPE, target->GetGUID().GetCounter());
    }
    // @tswow-end
}

FollowMovementGenerator::FollowMovementGenerator(Unit* target, float range, ChaseAngle angle) : AbstractFollower(ASSERT_NOTNULL(target)), _range(range), _angle(angle), _recheckPredictedDistanceTimer(0), _recheckPredictedDistance(false)
{
    Mode = MOTION_MODE_DEFAULT;
    Priority = MOTION_PRIORITY_NORMAL;
    Flags = MOVEMENTGENERATOR_FLAG_INITIALIZATION_PENDING;
    BaseUnitState = UNIT_STATE_FOLLOW;
}
FollowMovementGenerator::~FollowMovementGenerator() = default;

static Optional<float> GetVelocity(Unit* owner, Unit* target, G3D::Vector3 const& dest, bool playerPet)
{
    Optional<float> speed = {};
    if (!owner->IsInCombat() && !owner->IsVehicle() && !owner->HasUnitFlag(UNIT_FLAG_POSSESSED) &&
        (owner->IsPet() || owner->IsGuardian() || owner->GetGUID() == target->GetCritterGUID() || owner->GetCharmerOrOwnerGUID() == target->GetGUID()))
    {
        uint32 moveFlags = target->GetUnitMovementFlags();
        if (target->IsWalking())
        {
            moveFlags |= MOVEMENTFLAG_WALKING;
        }

        UnitMoveType moveType = Movement::SelectSpeedType(moveFlags);
        speed = target->GetSpeed(moveType);

        if (owner->IsCreature() && target->IsCreature())
            speed = target->GetSpeedInMotion();

        float distance = owner->GetDistance2d(dest.x, dest.y) - target->GetObjectSize() - (*speed / 2.f);
        if (distance > 0.f)
        {
            float multiplier = 1.0f;

            if (playerPet)
                multiplier += (distance / 30.f);
            else
                *speed = owner->IsCreature() ? owner->ToCreature()->GetCreatureTemplate()->speed_run : owner->GetSpeed(MOVE_RUN);
            
            *speed *= multiplier;
        }
    }

    return speed;
}

static Position const PredictPosition(Unit* target)
{
    Position pos = target->GetPosition();

     // 0.5 - it's time (0.5 sec) between starting movement opcode (e.g. MSG_MOVE_START_FORWARD) and MSG_MOVE_HEARTBEAT sent by client
    float speed = target->GetSpeed(Movement::SelectSpeedType(target->GetUnitMovementFlags())) * 0.5f;
    float orientation = target->GetOrientation();

    if (target->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_FORWARD))
    {
        pos.m_positionX += cos(orientation) * speed;
        pos.m_positionY += std::sin(orientation) * speed;
    }
    else if (target->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_BACKWARD))
    {
        pos.m_positionX -= cos(orientation) * speed;
        pos.m_positionY -= std::sin(orientation) * speed;
    }

    if (target->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_STRAFE_LEFT))
    {
        pos.m_positionX += cos(orientation + M_PI / 2.f) * speed;
        pos.m_positionY += std::sin(orientation + M_PI / 2.f) * speed;
    }
    else if (target->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_STRAFE_RIGHT))
    {
        pos.m_positionX += cos(orientation - M_PI / 2.f) * speed;
        pos.m_positionY += std::sin(orientation - M_PI / 2.f) * speed;
    }

    return pos;
}

bool FollowMovementGenerator::PositionOkay(Unit* target, bool isPlayerPet, bool& targetIsMoving, uint32 diff)
{
    if (!_lastTargetPosition)
        return false;

    float exactDistSq = target->GetExactDistSq(_lastTargetPosition->GetPositionX(), _lastTargetPosition->GetPositionY(), _lastTargetPosition->GetPositionZ());
    float distanceTolerance = 0.25f;
    // For creatures, increase tolerance
    if (target->GetTypeId() == TYPEID_UNIT)
    {
        distanceTolerance += _range + _range;
    }

    if (isPlayerPet)
    {
        targetIsMoving = target->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_FORWARD | MOVEMENTFLAG_BACKWARD | MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT);
    }

    if (exactDistSq > distanceTolerance)
        return false;

    if (isPlayerPet)
    {
        if (!targetIsMoving)
        {
            if (_recheckPredictedDistanceTimer.GetExpiry() > 0ms)
            {
                _recheckPredictedDistanceTimer.Update(diff);
                if (_recheckPredictedDistanceTimer.Passed())
                {
                    _recheckPredictedDistanceTimer = 0;
                    return false;
                }
            }

            return true;
        }

        return false;
    }

    return true;
}

void FollowMovementGenerator::Initialize(Unit* owner)
{
    RemoveFlag(MOVEMENTGENERATOR_FLAG_INITIALIZATION_PENDING | MOVEMENTGENERATOR_FLAG_DEACTIVATED);
    AddFlag(MOVEMENTGENERATOR_FLAG_INITIALIZED | MOVEMENTGENERATOR_FLAG_INFORM_ENABLED);

    owner->StopMoving();
    UpdatePetSpeed(owner);
    _path = nullptr;
    _lastTargetPosition.reset();
}

void FollowMovementGenerator::Reset(Unit* owner)
{
    RemoveFlag(MOVEMENTGENERATOR_FLAG_DEACTIVATED);

    Initialize(owner);
}

bool FollowMovementGenerator::Update(Unit* owner, uint32 diff)
{
    // owner might be dead or gone
    if (!owner || !owner->IsAlive())
        return false;

    // our target might have gone away
    Unit* const target = GetTarget();
    if (!target || !target->IsInWorld())
        return false;

    Creature* cOwner = owner->ToCreature();

    // the owner might be unable to move (rooted or casting), or we have lost the target, pause movement
    if (owner->HasUnitState(UNIT_STATE_NOT_MOVE) || (cOwner && owner->ToCreature()->IsMovementPreventedByCasting()))
    {
        _path = nullptr;
        owner->StopMoving();
        _lastTargetPosition.reset();
        return true;
    }

    bool followingMaster = false;
    Pet* oPet = owner->ToPet();
    if (oPet)
    {
        if (target->GetGUID() == oPet->GetOwnerGUID())
            followingMaster = true;
    }

    bool forceDest =
        (followingMaster) || // allow pets following their master to cheat while generating paths
        (target->GetTypeId() == TYPEID_PLAYER && target->ToPlayer()->IsGameMaster()) // for .npc follow
        ; // closes "bool forceDest", that way it is more appropriate, so we can comment out crap whenever we need to

    bool targetIsMoving = false;

    if (PositionOkay(target, owner->IsGuardian() && target->GetTypeId() == TYPEID_PLAYER, targetIsMoving, diff))
    {
        if (owner->HasUnitState(UNIT_STATE_FOLLOW_MOVE) && owner->movespline->Finalized())
        {
            owner->ClearUnitState(UNIT_STATE_FOLLOW_MOVE);
            _path = nullptr;
            DoMovementInform(owner, target);

            if (_recheckPredictedDistance)
            {
                _recheckPredictedDistanceTimer.Reset(1000);
            }

            owner->SetFacingTo(target->GetOrientation());
        }
    }
    else
    {
        Position targetPosition = target->GetPosition();
        _lastTargetPosition = targetPosition;

        // If player is moving and their position is not updated, we need to predict position
        if (targetIsMoving)
        {
            Position predictedPosition = PredictPosition(target);
            if (_lastPredictedPosition && _lastPredictedPosition->GetExactDistSq(&predictedPosition) < 0.25f)
                return true;

            _lastPredictedPosition = predictedPosition;
            targetPosition = predictedPosition;
            _recheckPredictedDistance = true;
        }
        else
        {
            _recheckPredictedDistance = false;
            _recheckPredictedDistanceTimer.Reset(0);
        }

        if (!_path)
            _path = std::make_unique<PathGenerator>(owner);
        else
            _path->Clear();

        target->MovePositionToFirstCollision(targetPosition, owner->GetCombatReach() + _range, target->ToAbsoluteAngle(_angle.RelativeAngle) - target->GetOrientation());

        float x, y, z;
        targetPosition.GetPosition(x, y, z);

        if (owner->IsHovering())
            owner->UpdateAllowedPositionZ(x, y, z);

        bool success = _path->CalculatePath(x, y, z, forceDest);
        if (!success || (_path->GetPathType() & PATHFIND_NOPATH && !followingMaster))
        {
            if (!owner->IsStopped())
                owner->StopMoving();

            return true;
        }

        owner->AddUnitState(UNIT_STATE_FOLLOW_MOVE);

        Movement::MoveSplineInit init(owner);
        init.MovebyPath(_path->GetPath());
        init.SetWalk(target->IsWalking() || target->IsWalking());
        if (Optional<float> velocity = GetVelocity(owner, target, _path->GetActualEndPosition(), owner->IsGuardian()))
            init.SetVelocity(*velocity);
        init.Launch();
    }
    
    return true;
}

void FollowMovementGenerator::Deactivate(Unit* owner)
{
    AddFlag(MOVEMENTGENERATOR_FLAG_DEACTIVATED);
    RemoveFlag(MOVEMENTGENERATOR_FLAG_TRANSITORY | MOVEMENTGENERATOR_FLAG_INFORM_ENABLED);
    owner->ClearUnitState(UNIT_STATE_FOLLOW_MOVE);
}

void FollowMovementGenerator::Finalize(Unit* owner, bool active, bool/* movementInform*/)
{
    AddFlag(MOVEMENTGENERATOR_FLAG_FINALIZED);
    if (active)
    {
        owner->ClearUnitState(UNIT_STATE_FOLLOW_MOVE);
        UpdatePetSpeed(owner);
    }
}

void FollowMovementGenerator::UpdatePetSpeed(Unit* owner)
{
    if (Pet* oPet = owner->ToPet())
    {
        if (!GetTarget() || GetTarget()->GetGUID() == owner->GetOwnerGUID())
        {
            oPet->UpdateSpeed(MOVE_RUN);
            oPet->UpdateSpeed(MOVE_WALK);
            oPet->UpdateSpeed(MOVE_SWIM);
        }
    }
}
