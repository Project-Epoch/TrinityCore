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

#include "GuardMgr.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "GridNotifiers.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "DBCStores.h"

GuardMgr* GuardMgr::instance()
{
    static GuardMgr instance;
    return &instance;
}

GuardMgr::~GuardMgr()
{
}

GuardMgr::GuardMgr() { }

uint32 GuardMgr::GetTextId(uint32 factionTemplateId, uint32 areaId, uint32 displayId) const
{
    // Do only Razor Hill npcs use this text?
    // https://youtu.be/jkBYnb0EBXU?t=63
    // https://www.youtube.com/watch?v=r7aveH_fyTw
    if (areaId == AREA_RAZOR_HILL)
        return TEXT_GUARD_ORC_2;

    // It appears the text used depends on the model, not faction?
    // Night Elf and Human NPC with same faction say different texts.
    // https://youtu.be/LEmiZsv78Bo?t=107
    if (CreatureDisplayInfoEntry const* displayInfo = sCreatureDisplayInfoStore.LookupEntry(displayId))
    {
        switch (displayInfo->ModelID)
        {
            case MODEL_HUMAN_MALE:
            case MODEL_HUMAN_FEMALE:
                return TEXT_GUARD_HUMAN;
            case MODEL_ORC_MALE:
            case MODEL_ORC_FEMALE:
                return TEXT_GUARD_ORC;
            case MODEL_DWARF_MALE:
            case MODEL_DWARF_FEMALE:
                return TEXT_GUARD_DWARF;
            case MODEL_NELF_MALE:
            case MODEL_NELF_FEMALE:
                return TEXT_GUARD_NIGHT_ELF;
            case MODEL_UNDEAD_MALE:
            case MODEL_UNDEAD_FEMALE:
                return TEXT_GUARD_UNDEAD;
            case MODEL_TAUREN_MALE:
            case MODEL_TAUREN_FEMALE:
                return TEXT_GUARD_TAUREN;
            case MODEL_GNOME_MALE:
            case MODEL_GNOME_FEMALE:
                return TEXT_GUARD_GNOME;
            case MODEL_TROLL_MALE:
            case MODEL_TROLL_FEMALE:
                return TEXT_GUARD_TROLL;
        }
    }

    switch (factionTemplateId)
    {
        // Stormwind City
        case 11:
        case 12:
        case 123:
        case 1078:
        case 1575:
        // The Night Watch
        case 53:
        case 56:
        // Alliance Generic
        case 84:
        case 210:
        case 534:
        case 1315:
        // Theramore
        case 149:
        case 150:
        case 151:
        case 894:
        case 1075:
        case 1077:
        case 1096:
        // League of Arathor
        case 1577:
        // Silvermoon Remnant
        case 371:
        case 1576:
            return TEXT_GUARD_HUMAN;
        // Orgrimmar
        case 29:
        case 65:
        case 85:
        case 125:
        case 1074:
        case 1174:
        case 1595:
        case 1612:
        case 1619:
        // Horde Generic
        case 83:
        case 106:
        case 714:
        case 1034:
        case 1314:
        // Frostwold Clan
        case 1215:
        // Warsong Outriders
        case 1515:
            return TEXT_GUARD_ORC;
        // Ironforge
        case 55:
        case 57:
        case 122:
        case 1611:
        case 1618:
        // Wildhammer Clan
        case 694:
        case 1054:
        case 1055:
        // Stormpike Guard
        case 1217:
            return TEXT_GUARD_DWARF;
        // Gnomeregan Exiles
        case 23:
        case 64:
        case 875:
            return TEXT_GUARD_GNOME;
        // Undercity
        case 68:
        case 71:
        case 98:
        case 118:
        case 1134:
        case 1154:
        // The Defilers
        case 412:
            return TEXT_GUARD_UNDEAD;
        // Darnassus
        case 79:
        case 80:
        case 124:
        case 1076:
        case 1097:
        case 1594:
        case 1600:
        // Silverwing Sentinels
        case 1514:
            return TEXT_GUARD_NIGHT_ELF;
        // Thunder Bluff
        case 104:
        case 105:
        case 995:
            return TEXT_GUARD_TAUREN;
        // Darkspear Trolls
        case 126:
        case 876:
        case 877:
            return TEXT_GUARD_TROLL;
    }

    return TEXT_NONE;
}

void GuardMgr::SummonGuard(Creature* civilian, Unit* enemy, bool ignoreCooldown)
{
    if (!civilian || !enemy)
        return;

    TC_LOG_ERROR("sql.sql", "GuardMgr::SummonGuard {}", civilian->GetEntry());

    bool summonedOrCalledGuard = false;
    if (GameObject* guardPost = civilian->FindNearestGuardPost(50.0f))
    {
        summonedOrCalledGuard = guardPost->SummonGuard(civilian, enemy, ignoreCooldown);
    }
    else
    {
        summonedOrCalledGuard = civilian->CallNearestGuard(enemy);
    }
    // civilian say call for guard
    if (ignoreCooldown || summonedOrCalledGuard)
    {
        if (uint32 textId = GetTextId(civilian->GetFactionTemplateEntry()->ID, civilian->GetAreaId(), civilian->GetDisplayId()))
        {
            civilian->Say(textId, enemy);
        }
    }
}

void GuardMgr::SummonGuard(Player* attackedPlayer, Unit* enemy, bool ignoreCooldown)
{
    if (!attackedPlayer)
        return;

    // TC_LOG_DEBUG("misc", "GuardMgr::SummonGuard Player {}", attackedPlayer->GetName());

    AreaTableEntry const* area = sAreaTableStore.LookupEntry(attackedPlayer->GetAreaId());
    if (!area || !(area->Flags & AREA_FLAG_PLAYERS_CALL_GUARDS))
        return;

    // call MoveInLineOfSight for nearby contested guards
    Trinity::AIRelocationNotifier notifier(*enemy);
    Cell::VisitWorldObjects(enemy, notifier, enemy->GetVisibilityRange());

    if (GameObject* guardPost = attackedPlayer->FindNearestGuardPost(50.0f))
    {
        guardPost->SummonGuard(attackedPlayer, enemy, ignoreCooldown);
    }
}
