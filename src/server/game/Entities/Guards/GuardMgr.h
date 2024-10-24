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

#ifndef TRINITYCORE_GUARD_MGR_H
#define TRINITYCORE_GUARD_MGR_H

#include <unordered_map>

enum GuardAreas
{
    AREA_NORTHSHIRE          = 9,
    AREA_WETLANDS            = 11,
    AREA_DUSTWALLOW_MARSH    = 15,
    AREA_BOOTY_BAY           = 35,
    AREA_DARKSHIRE           = 42,
    AREA_ARATHI_HIGHLANDS    = 45,
    AREA_LAKESHIRE           = 69,
    AREA_STONARD             = 75,
    AREA_TIRISFAL_GLADES     = 85,
    AREA_GOLDSHIRE           = 87,
    AREA_SENTINEL_HILL       = 108,
    AREA_GROMGOL             = 117,
    AREA_SILVERPINE          = 130,
    AREA_KHARANOS            = 131,
    AREA_COLDRIDGE_VALLEY    = 132,
    AREA_TELDRASSIL          = 141,
    AREA_THELSAMAR           = 144,
    AREA_MENETHIL            = 150,
    AREA_DEATHKNELL          = 154,
    AREA_BRILL               = 159,
    AREA_DOLANAAR            = 186,
    AREA_SHADOWGLEN          = 188,
    AREA_MULGORE             = 215,
    AREA_CAMP_NARACHE        = 221,
    AREA_BLOODHOOF_VILLAGE   = 222,
    AREA_SEPULCHER           = 228,
    AREA_HILLSBRAD_FOOTHILLS = 267,
    AREA_SOUTHSHORE          = 271,
    AREA_TARREN_MILL         = 272,
    AREA_REFUGE_POINTE       = 320,
    AREA_HAMERFALL           = 321,
    AREA_KARGATH             = 340,
    AREA_RAZOR_HILL          = 362,
    AREA_VALLEY_OF_TRIALS    = 363,
    AREA_SENJIN_VILLAGE      = 367,
    AREA_CROSSROADS          = 380,
    AREA_RATCHET             = 392,
    AREA_STONETALON          = 406,
    AREA_ASTRANAAR           = 415,
    AREA_AUBERDINE           = 442,
    AREA_FREEWIND_POST       = 484,
    AREA_BRACKENWALL_VILLAGE = 496,
    AREA_THERAMORE           = 513,
    AREA_RUTHERAN_VILLAGE    = 702,
    AREA_GADGETZAN           = 976,
    AREA_CAMP_MOJACHE        = 1099,
    AREA_FEATHERMOON         = 1116,
    AREA_UNDERCITY           = 1497,
    AREA_STORMWIND           = 1519,
    AREA_IRONFORGE           = 1537,
    AREA_ORGRIMMAR           = 1637,
    AREA_THUNDERBLUFF        = 1638,
    AREA_DARNASSUS           = 1657,
    AREA_EVERLOOK            = 2255,
    AREA_LIGHTS_HOPE_CHAPEL  = 2268,
    AREA_NIGHTHAVEN          = 2361,
    AREA_REVANTUSK_VILLAGE   = 3317,
};

enum GuardTexts
{
    TEXT_NONE            = 0,
    TEXT_GUARD_HUMAN     = 4403, // Guards! Help me!
    TEXT_GUARD_NIGHT_ELF = 4564, // Sentinels, come to my defense!
    TEXT_GUARD_ORC       = 4561, // Guards!
    TEXT_GUARD_ORC_2     = 4558, // Grunts! Attack!
    TEXT_GUARD_TAUREN    = 4560, // You will not defile our sacred land!
    TEXT_GUARD_TROLL     = 4559, // Guardians! Defend Sen'jin!
    TEXT_GUARD_DWARF     = 4583, // Guards!
    TEXT_GUARD_UNDEAD    = 4484, // Intruders! Attack the intruders!
    TEXT_GUARD_GNOME     = 8546, // Help! Guards! It's going to step on me!
};

enum ModelIds
{
    MODEL_HUMAN_MALE    = 49,
    MODEL_HUMAN_FEMALE  = 50,
    MODEL_ORC_MALE      = 51,
    MODEL_ORC_FEMALE    = 52,
    MODEL_DWARF_MALE    = 53,
    MODEL_DWARF_FEMALE  = 54,
    MODEL_NELF_MALE     = 55,
    MODEL_NELF_FEMALE   = 56,
    MODEL_UNDEAD_MALE   = 57,
    MODEL_UNDEAD_FEMALE = 58,
    MODEL_TAUREN_MALE   = 59,
    MODEL_TAUREN_FEMALE = 60,
    MODEL_GNOME_MALE    = 182,
    MODEL_GNOME_FEMALE  = 183,
    MODEL_TROLL_MALE    = 185,
    MODEL_TROLL_FEMALE  = 186,
};

class Unit;
class Creature;

class GuardMgr
{
    public:
        GuardMgr();
        virtual ~GuardMgr();
        static GuardMgr* instance();
        [[nodiscard]] uint32 GetTextId(uint32 factionTemplateId, uint32 areaId, uint32 displayId) const;
        void SummonGuard(Creature* civilian, Unit* enemy, bool ignoreCooldown = false);
        void SummonGuard(Player* attackedPlayer, Unit* enemy, bool ignoreCooldown = false);
};

#define sGuardMgr GuardMgr::instance()

#endif
