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

#ifndef TRINITY_TOTEMAI_H
#define TRINITY_TOTEMAI_H

#include "CreatureAI.h"
#include "PassiveAI.h"
#include "Timer.h"

class Creature;
class Totem;

class TC_GAME_API TotemAI : public NullCreatureAI
{
    public:
        explicit TotemAI(Creature* creature);

        void AttackStart(Unit* victim) override;
        /** @epoch-start */
        void DamageTaken(Unit* attacker, uint32& /*damage*/, DamageEffectType /*damageType*/, SpellInfo const* /*spellInfo = nullptr*/) override { AttackStart(attacker); }
        /** @epoch-end */

        void UpdateAI(uint32 diff) override;
        static int32 Permissible(Creature const* creature);

    private:
        ObjectGuid _victimGUID;
};

/*!
 * \class KillMagnetEvent
 * \brief Use in conjonction with EventProcessor to self kill Totem (ex: Grounding Totem getting hit by Polymorph/Fear spells)
 */
class KillMagnetEvent : public BasicEvent
{
    public:
        KillMagnetEvent(Unit& self) : _self(self) {}
        bool Execute(uint64 /*e_time*/, uint32 /*p_time*/) override
        {
            _self.setDeathState(DEAD);
            return true;
        }

    protected:
        Unit& _self;
};
#endif
