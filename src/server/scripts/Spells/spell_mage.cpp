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

/*
 * Scripts for spells with SPELLFAMILY_MAGE and SPELLFAMILY_GENERIC spells used by mage players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_mage_".
 */

#include "ScriptMgr.h"
#include "GridNotifiers.h"
#include "Creature.h"
#include "Player.h"
#include "Random.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellMgr.h"
#include "SpellScript.h"

enum MageSpells
{
    SPELL_MAGE_BLAZING_SPEED                     = 31643,
    SPELL_MAGE_BURNOUT                           = 44450,
    SPELL_MAGE_COLD_SNAP                         = 11958,
    SPELL_MAGE_FOCUS_MAGIC_PROC                  = 54648,
    SPELL_MAGE_FROST_WARDING_R1                  = 11189,
    SPELL_MAGE_FROST_WARDING_TRIGGERED           = 57776,
    SPELL_MAGE_INCANTERS_ABSORBTION              = 1280035,
    SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED    = 1280036,
    SPELL_MAGE_IGNITE                            = 1300005,
    SPELL_MAGE_MASTER_OF_ELEMENTS_ENERGIZE       = 29077,
    SPELL_MAGE_SQUIRREL_FORM                     = 32813,
    SPELL_MAGE_GIRAFFE_FORM                      = 32816,
    SPELL_MAGE_SERPENT_FORM                      = 32817,
    SPELL_MAGE_DRAGONHAWK_FORM                   = 32818,
    SPELL_MAGE_WORGEN_FORM                       = 32819,
    SPELL_MAGE_SHEEP_FORM                        = 32820,
    SPELL_MAGE_GLYPH_OF_ETERNAL_WATER            = 70937,
    SPELL_MAGE_SHATTERED_BARRIER                 = 55080,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT  = 70908,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY  = 70907,
    SPELL_MAGE_GLYPH_OF_BLAST_WAVE               = 62126,
    SPELL_MAGE_CHILLED                           = 12484,
    SPELL_MAGE_MANA_SURGE                        = 37445,
    SPELL_MAGE_MAGIC_ABSORPTION_MANA             = 29442,
    SPELL_MAGE_ARCANE_POTENCY_RANK_1             = 57529,
    SPELL_MAGE_ARCANE_POTENCY_RANK_2             = 57531,
    SPELL_MAGE_HOT_STREAK_PROC                   = 1300001,
    SPELL_MAGE_ARCANE_SURGE                      = 37436,
    SPELL_MAGE_COMBUSTION                        = 11129,
    SPELL_MAGE_COMBUSTION_PROC                   = 28682,
    SPELL_MAGE_EMPOWERED_FIRE_PROC               = 67545,
    SPELL_MAGE_T10_2P_BONUS                      = 70752,
    SPELL_MAGE_T10_2P_BONUS_EFFECT               = 70753,
    SPELL_MAGE_T8_4P_BONUS                       = 64869,
    SPELL_MAGE_MISSILE_BARRAGE                   = 44401,
    SPELL_MAGE_FINGERS_OF_FROST_AURASTATE_AURA   = 44544,
    SPELL_MAGE_PERMAFROST_AURA                   = 68391,
    SPELL_MAGE_ARCANE_MISSILES_R1                = 5143,

    // Duskhaven
    SPELL_MAGE_BITTING_FROST                     = 1290000,
    SPELL_MAGE_BLAZING_BARRIER                   = 1280024,
    SPELL_MAGE_BLAZING_BARRIER_PROC              = 1280025,
    SPELL_MAGE_BLINK                             = 1280011,
    SPELL_MAGE_BLIZZARD                          = 1290005,
    SPELL_MAGE_BRAIN_CHILL                       = 1290049,
    SPELL_MAGE_BRAIN_FREEZE_PROC                 = 1290018,
    SPELL_MAGE_BURN_IT_ALL_DOWN                  = 1300027,
    SPELL_MAGE_BURNING_ADRENALINE                = 1300032,
    SPELL_MAGE_CHAIN_REACTION_PROC               = 1290046,
    SPELL_MAGE_CHILLED_ENERGIZE                  = 1290002,
    SPELL_MAGE_CHILLING_SIPHON                   = 1290001,
    SPELL_MAGE_COLD_WINDS                        = 1280032,
    SPELL_MAGE_COLD_WINDS_PROC                   = 1280033,
    SPELL_MAGE_DISPLACEMENT_ALLOW_CAST           = 1280072,
    SPELL_MAGE_DISPLACEMENT_DUMMY_TALENT         = 1280073,
    SPELL_MAGE_DISPLACEMENT_SUMMON               = 1280071,
    SPELL_MAGE_DISPLACEMENT_TELEPORT             = 1280070,
    SPELL_MAGE_DRAGON_HEART_MANA_PROC            = 1300014,
    SPELL_MAGE_DRAGON_HEART_PROC                 = 1300015,
    SPELL_MAGE_DRAGON_HEART_TALENT               = 1300013,
    SPELL_MAGE_ELEMENTAL_HEART_PROC              = 1300026,
    SPELL_MAGE_ELEMENTAL_HEART_TALENT            = 1300025,
    SPELL_MAGE_FEEL_THE_BURN_PROC                = 1300039,
    SPELL_MAGE_FEEL_THE_BURN_TALENT              = 1390038,
    SPELL_MAGE_FIREBALL                          = 1280000,
    SPELL_MAGE_FINGERS_OF_FROST_PROC             = 1290004,
    SPELL_MAGE_FIRE_BLAST                        = 1300007,
    SPELL_MAGE_FLURRY_BRITTLEFROST               = 1290013,
    SPELL_MAGE_FRICTION_BARRIER_PROC             = 1280029,
    SPELL_MAGE_FRICTION_BARRIER_TALENT           = 1280028,
    SPELL_MAGE_FROST_ARMOR_AURA                  = 1280043,
    SPELL_MAGE_FROST_ARMOR_TALENT                = 1280042,
    SPELL_MAGE_FROST_BOMB_PROC                   = 1290063,
    SPELL_MAGE_FROST_BOMB_TALENT                 = 1290048,
    SPELL_MAGE_FROST_MASTERY_ICICLE              = 1290019,
    SPELL_MAGE_FROST_MASTERY_ICICLE_AURA         = 1290021,
    SPELL_MAGE_FROST_MASTERY_ICICLE_VIS1         = 1290022,
    SPELL_MAGE_FROST_MASTERY_ICICLE_VIS2         = 1290023,
    SPELL_MAGE_FROST_MASTERY_ICICLE_VIS3         = 1290024,
    SPELL_MAGE_FROST_MASTERY_ICICLE_VIS4         = 1290025,
    SPELL_MAGE_FROST_MASTERY_ICICLE_VIS5         = 1290026,
    SPELL_MAGE_FROST_MASTERY_ICICLE_SPELL        = 1290027,
    SPELL_MAGE_FROZEN_ORB_DOT                    = 1290035,
    SPELL_MAGE_FUEL_THE_FIRE                     = 1300012,
    SPELL_MAGE_GALEFURY                          = 1290061,
    SPELL_MAGE_GALEFURY_CONE_OF_COLD             = 1290062,
    SPELL_MAGE_GREAT_INFERNO                     = 1300031,
    SPELL_MAGE_GROUND_ZERO_PROC                  = 1300043,
    SPELL_MAGE_GROUND_ZERO_TALENT                = 1300042,
    SPELL_MAGE_HEAT_WAVE                         = 1280045,
    SPELL_MAGE_HEAT_WAVE_PROC                    = 1280046,
    SPELL_MAGE_HOT_SECOND_PROC                   = 1300049,
    SPELL_MAGE_HOT_SECOND_TALENT                 = 1300048,
    SPELL_MAGE_ICEFALL_PROC                      = 1290041,
    SPELL_MAGE_ICEFALL_PROC_DMG                  = 1290042,
    SPELL_MAGE_ICEFALL_TALENT                    = 1290040,
    SPELL_MAGE_ICEFLURRY                         = 1290016,
    SPELL_MAGE_ICE_LANCE                         = 1290008,
    SPELL_MAGE_ICY_GALE                          = 1290054,
    SPELL_MAGE_LIVING_BOMB_DIRECT_DAMAGE         = 1300028,
    SPELL_MAGE_LIVING_BOMB_DUMMY                 = 1300017,
    SPELL_MAGE_LIVING_BOMB_DUMMY_AURA            = 1300018,
    SPELL_MAGE_LIVING_BOMB_LB                    = 1300019,
    SPELL_MAGE_LIVING_BOMBARDMENT                = 1300016,
    SPELL_MAGE_LIVING_MINEFIELD_PROC             = 1300041,
    SPELL_MAGE_LIVING_MINEFIELD_TALENT           = 1300040,
    SPELL_MAGE_MANA_BARRIER                      = 1280030,
    SPELL_MAGE_MANA_GEM                          = 1280013,
    SPELL_MAGE_MANA_GEM_ENERGIZE                 = 1280062,
    SPELL_MAGE_MOLTEN_ARMOR_AURA                 = 1280041,
    SPELL_MAGE_MOLTEN_ARMOR_TALENT               = 1280040,
    SPELL_MAGE_MANA_BARRIER_PROC                 = 1280031,
    SPELL_MAGE_PRISTINE_MANA_GEM                 = 1280061,
    SPELL_MAGE_SLICE_AND_ICE_BUFF                = 1290029,
    SPELL_MAGE_SMOLDERING_PROC                   = 1300030,
    SPELL_MAGE_SNOWCONE                          = 1290071,
    SPELL_MAGE_SNOWSTORM_PROC                    = 1290056,
    SPELL_MAGE_SNOWSTORM_TALENT                  = 1290055,
    SPELL_MAGE_SPLITTING_ICE                     = 1290030,
    SPELL_MAGE_SPLITTING_ICE_ICE_LANCE           = 1290031,
    SPELL_MAGE_SPLITTING_ICE_ICICLE              = 1290032,
    SPELL_MAGE_TEMPORAL_DISPLACEMENT             = 1280021,
    SPELL_MAGE_WORLD_IN_FLAMES_PROC              = 1300056,
    SPELL_MAGE_WORLD_IN_FLAMES_TALENT            = 1300055
};

enum MageSpellIcons
{
    SPELL_ICON_MAGE_SHATTERED_BARRIER = 2945,
    SPELL_ICON_MAGE_PRESENCE_OF_MIND  = 139,
    SPELL_ICON_MAGE_CLEARCASTING      = 212,
    SPELL_ICON_MAGE_LIVING_BOMB       = 3000
};

enum SpellHelpers
{
    SPELL_SHAMAN_EXHAUSTION                      = 57723,
    SPELL_SHAMAN_SATED                           = 57724,
};

// Incanter's Absorbtion
class spell_mage_incanters_absorbtion_base_AuraScript : public AuraScript
{
    public:
        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo(
            {
                SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED,
                SPELL_MAGE_INCANTERS_ABSORBTION
            });
        }

        void Trigger(AuraEffect* aurEff, DamageInfo& /*dmgInfo*/, uint32& absorbAmount)
        {
            Unit* target = GetTarget();

            if (AuraEffect* talentAurEff = target->GetAuraEffect(SPELL_MAGE_INCANTERS_ABSORBTION, EFFECT_0))
            {
                int32 bp = CalculatePct(absorbAmount, talentAurEff->GetAmount());
                CastSpellExtraArgs args(aurEff);
                args.AddSpellBP0(bp);
                target->CastSpell(target, SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, args);
            }
        }
};

// -5143 - Arcane Missiles
class spell_mage_arcane_missiles : public AuraScript
{
    PrepareAuraScript(spell_mage_arcane_missiles);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_T10_2P_BONUS, SPELL_MAGE_T10_2P_BONUS_EFFECT });
    }

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        if (target->HasAura(SPELL_MAGE_T10_2P_BONUS) && _canProcT10)
            target->CastSpell(nullptr, SPELL_MAGE_T10_2P_BONUS_EFFECT, aurEff);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_mage_arcane_missiles::OnRemove, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }

private:
    bool _canProcT10 = false;

public:
    void AllowT10Proc()
    {
        _canProcT10 = true;
    }
};

// -31571 - Arcane Potency
class spell_mage_arcane_potency : public AuraScript
{
    PrepareAuraScript(spell_mage_arcane_potency);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MAGE_ARCANE_POTENCY_RANK_1,
            SPELL_MAGE_ARCANE_POTENCY_RANK_2
        });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        // due to family mask sharing with brain freeze/missile barrage proc, we need to filter out by icon id
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (!spellInfo || (spellInfo->SpellIconID != SPELL_ICON_MAGE_CLEARCASTING && spellInfo->SpellIconID != SPELL_ICON_MAGE_PRESENCE_OF_MIND))
            return false;

        return true;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        static uint32 const triggerSpell[2] = { SPELL_MAGE_ARCANE_POTENCY_RANK_1, SPELL_MAGE_ARCANE_POTENCY_RANK_2 };

        PreventDefaultAction();
        Unit* caster = eventInfo.GetActor();
        uint32 spellId = triggerSpell[GetSpellInfo()->GetRank() - 1];
        caster->CastSpell(caster, spellId, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_arcane_potency::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_mage_arcane_potency::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 1280038 - Blast Wave
class spell_mage_blast_wave : public SpellScript
{
    PrepareSpellScript(spell_mage_blast_wave);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MAGE_HEAT_WAVE,
            SPELL_MAGE_HEAT_WAVE_PROC
        });
    }

    void HandleOnCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_BURN_IT_ALL_DOWN))
                caster->CastSpell(caster, SPELL_MAGE_HOT_STREAK_PROC, true);
    }

    void HandleEffect(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
                if (caster->HasAura(SPELL_MAGE_HEAT_WAVE))
                    caster->CastSpell(target, SPELL_MAGE_HEAT_WAVE_PROC, true);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mage_blast_wave::HandleOnCast);
        OnEffectHitTarget += SpellEffectFn(spell_mage_blast_wave::HandleEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// -31641 - Blazing Speed
class spell_mage_blazing_speed : public AuraScript
{
    PrepareAuraScript(spell_mage_blazing_speed);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_BLAZING_SPEED });
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        if (Unit* target = eventInfo.GetActionTarget())
            target->CastSpell(target, SPELL_MAGE_BLAZING_SPEED, aurEff);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_mage_blazing_speed::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// -54747 - Burning Determination
// 54748 - Burning Determination
// 1280052, 1280053 - Intense Focus
class spell_mage_burning_determination : public AuraScript
{
    PrepareAuraScript(spell_mage_burning_determination);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (SpellInfo const* spellInfo = eventInfo.GetSpellInfo())
            if (spellInfo->GetAllEffectsMechanicMask() & ((1 << MECHANIC_INTERRUPT) | (1 << MECHANIC_SILENCE)))
                return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_burning_determination::CheckProc);
    }
};

// -44449 - Burnout
class spell_mage_burnout : public AuraScript
{
    PrepareAuraScript(spell_mage_burnout);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_BURNOUT });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!damageInfo || !damageInfo->GetSpellInfo())
            return false;

        return true;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        int32 mana = eventInfo.GetDamageInfo()->GetSpellInfo()->CalcPowerCost(GetTarget(), eventInfo.GetDamageInfo()->GetSchoolMask());
        mana = CalculatePct(mana, aurEff->GetAmount());

        CastSpellExtraArgs args(aurEff);
        args.AddSpellBP0(mana);
        GetTarget()->CastSpell(GetTarget(), SPELL_MAGE_BURNOUT, args);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_burnout::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_mage_burnout::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
    }
};

// 1290044 - Cold Snap
class spell_mage_cold_snap : public SpellScript
{
    PrepareSpellScript(spell_mage_cold_snap);

    bool Load() override
    {
        return GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->GetSpellHistory()->ResetCooldowns([](SpellHistory::CooldownStorageType::iterator itr) -> bool
        {
            SpellInfo const* spellInfo = sSpellMgr->AssertSpellInfo(itr->first);
            return spellInfo->SpellFamilyName == SPELLFAMILY_MAGE && (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_FROST) &&
                spellInfo->SpellFamilyFlags[0] & 0x28420 && spellInfo->GetRecoveryTime() > 0;
        }, true);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_mage_cold_snap::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 11129 - Combustion
class spell_mage_combustion : public AuraScript
{
    PrepareAuraScript(spell_mage_combustion);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_COMBUSTION_PROC });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        // Do not take charges, add a stack of crit buff
        if (!(eventInfo.GetHitMask() & PROC_HIT_CRITICAL))
        {
            eventInfo.GetActor()->CastSpell(nullptr, SPELL_MAGE_COMBUSTION_PROC, true);
            return false;
        }

        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_combustion::CheckProc);
    }
};

// 28682 - Combustion proc
class spell_mage_combustion_proc : public AuraScript
{
    PrepareAuraScript(spell_mage_combustion_proc);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_COMBUSTION });
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->RemoveAurasDueToSpell(SPELL_MAGE_COMBUSTION);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_mage_combustion_proc::OnRemove, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

// -31661 - Dragon's Breath
class spell_mage_dragon_breath : public AuraScript
{
    PrepareAuraScript(spell_mage_dragon_breath);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        // Dont proc with Living Bomb explosion
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (spellInfo && spellInfo->SpellIconID == SPELL_ICON_MAGE_LIVING_BOMB && spellInfo->SpellFamilyName == SPELLFAMILY_MAGE)
            return false;
        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_dragon_breath::CheckProc);
    }
};

// -11185 - Improved Blizzard
class spell_mage_imp_blizzard : public AuraScript
{
    PrepareAuraScript(spell_mage_imp_blizzard);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_CHILLED });
    }

    void HandleChill(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        uint32 triggerSpellId = sSpellMgr->GetSpellWithRank(SPELL_MAGE_CHILLED, GetSpellInfo()->GetRank());
        eventInfo.GetActor()->CastSpell(eventInfo.GetProcTarget(), triggerSpellId, aurEff);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_mage_imp_blizzard::HandleChill, EFFECT_0, SPELL_AURA_OVERRIDE_CLASS_SCRIPTS);
    }
};

// 37447 - Improved Mana Gems
// 61062 - Improved Mana Gems
class spell_mage_imp_mana_gems : public AuraScript
{
    PrepareAuraScript(spell_mage_imp_mana_gems);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_MANA_SURGE });
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        eventInfo.GetActor()->CastSpell(nullptr, SPELL_MAGE_MANA_SURGE, aurEff);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_mage_imp_mana_gems::HandleProc, EFFECT_1, SPELL_AURA_OVERRIDE_CLASS_SCRIPTS);
    }
};

// -31656 - Empowered Fire
class spell_mage_empowered_fire : public AuraScript
{
    PrepareAuraScript(spell_mage_empowered_fire);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_EMPOWERED_FIRE_PROC });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (SpellInfo const* spellInfo = eventInfo.GetSpellInfo())
            if (spellInfo->Id == SPELL_MAGE_IGNITE)
                return true;

        return false;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        Unit* target = GetTarget();
        CastSpellExtraArgs args(aurEff);
        uint8 percent = sSpellMgr->AssertSpellInfo(SPELL_MAGE_EMPOWERED_FIRE_PROC)->GetEffect(EFFECT_0).CalcValue();
        args.AddSpellBP0(CalculatePct(target->GetCreateMana(), percent));
        target->CastSpell(target, SPELL_MAGE_EMPOWERED_FIRE_PROC, args);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_empowered_fire::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_mage_empowered_fire::HandleProc, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER);
    }
};

// 74396 - Fingers of Frost
class spell_mage_fingers_of_frost : public AuraScript
{
    PrepareAuraScript(spell_mage_fingers_of_frost);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_FINGERS_OF_FROST_AURASTATE_AURA });
    }

    void HandleDummy(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        eventInfo.GetActor()->RemoveAuraFromStack(GetId());
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->RemoveAurasDueToSpell(SPELL_MAGE_FINGERS_OF_FROST_AURASTATE_AURA);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_mage_fingers_of_frost::HandleDummy, EFFECT_0, SPELL_AURA_DUMMY);
        AfterEffectRemove += AuraEffectRemoveFn(spell_mage_fingers_of_frost::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// -543  - Fire Ward
// -6143 - Frost Ward
class spell_mage_fire_frost_ward : public spell_mage_incanters_absorbtion_base_AuraScript
{
    PrepareAuraScript(spell_mage_fire_frost_ward);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MAGE_FROST_WARDING_TRIGGERED,
            SPELL_MAGE_FROST_WARDING_R1
        });
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = false;
        if (Unit* caster = GetCaster())
        {
            // +80.68% from sp bonus
            float bonus = 0.8068f;

            bonus *= caster->SpellBaseHealingBonusDone(GetSpellInfo()->GetSchoolMask());
            bonus *= caster->CalculateSpellpowerCoefficientLevelPenalty(GetSpellInfo());

            amount += int32(bonus);
        }
    }

    void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        Unit* target = GetTarget();
        if (AuraEffect* talentAurEff = target->GetAuraEffectOfRankedSpell(SPELL_MAGE_FROST_WARDING_R1, EFFECT_0))
        {
            int32 chance = talentAurEff->GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(); // SPELL_EFFECT_DUMMY with NO_TARGET

            if (roll_chance_i(chance))
            {
                int32 bp = dmgInfo.GetDamage();
                dmgInfo.AbsorbDamage(bp);
                CastSpellExtraArgs args(aurEff);
                args.AddSpellBP0(bp);
                target->CastSpell(target, SPELL_MAGE_FROST_WARDING_TRIGGERED, args);
                absorbAmount = 0;
                PreventDefaultAction();
            }
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_fire_frost_ward::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_fire_frost_ward::Absorb, EFFECT_0);
        AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_fire_frost_ward::Trigger, EFFECT_0);
    }
};

// -44614 - Frostfire Bolt
class spell_mage_frostfire_bolt : public AuraScript
{
    PrepareAuraScript(spell_mage_frostfire_bolt);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_PERMAFROST_AURA });
    }

    void ApplyPermafrost(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(GetTarget(), SPELL_MAGE_PERMAFROST_AURA, aurEff);
    }

    void RemovePermafrost(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->RemoveAurasDueToSpell(SPELL_MAGE_PERMAFROST_AURA);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_mage_frostfire_bolt::ApplyPermafrost, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        AfterEffectRemove += AuraEffectRemoveFn(spell_mage_frostfire_bolt::RemovePermafrost, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
    }
};

// 54646 - Focus Magic
class spell_mage_focus_magic : public AuraScript
{
    PrepareAuraScript(spell_mage_focus_magic);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_FOCUS_MAGIC_PROC });
    }

    bool CheckProc(ProcEventInfo& /*eventInfo*/)
    {
        _procTarget = GetCaster();
        return _procTarget && _procTarget->IsAlive();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();
        GetTarget()->CastSpell(_procTarget, SPELL_MAGE_FOCUS_MAGIC_PROC, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_focus_magic::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_mage_focus_magic::HandleProc, EFFECT_0, SPELL_AURA_MOD_SPELL_CRIT_CHANCE);
    }

    Unit* _procTarget = nullptr;
};

// 48108 - Hot Streak
// 57761 - Fireball!
class spell_mage_gen_extra_effects : public AuraScript
{
    PrepareAuraScript(spell_mage_gen_extra_effects);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MAGE_T10_2P_BONUS,
            SPELL_MAGE_T10_2P_BONUS_EFFECT,
            SPELL_MAGE_T8_4P_BONUS
        });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = eventInfo.GetActor();
        // Prevent double proc for Arcane missiles
        if (caster == eventInfo.GetProcTarget())
            return false;

        // Proc chance is unknown, we'll just use dummy aura amount
        if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_MAGE_T8_4P_BONUS, EFFECT_0))
            if (roll_chance_i(aurEff->GetAmount()))
                return false;

        return true;
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = eventInfo.GetActor();

        if (caster->HasAura(SPELL_MAGE_T10_2P_BONUS))
            caster->CastSpell(nullptr, SPELL_MAGE_T10_2P_BONUS_EFFECT, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_gen_extra_effects::CheckProc);
        OnProc += AuraProcFn(spell_mage_gen_extra_effects::HandleProc);
    }
};

// 56375 - Glyph of Polymorph
class spell_mage_glyph_of_polymorph : public AuraScript
{
    PrepareAuraScript(spell_mage_glyph_of_polymorph);

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Unit* target = eventInfo.GetProcTarget();
        target->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, ObjectGuid::Empty, target->GetAura(32409)); // SW:D shall not be removed.
        target->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
        target->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_mage_glyph_of_polymorph::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 56374 - Glyph of Icy Veins
class spell_mage_glyph_of_icy_veins : public AuraScript
{
    PrepareAuraScript(spell_mage_glyph_of_icy_veins);

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Unit* caster = eventInfo.GetActor();
        caster->RemoveAurasByType(SPELL_AURA_HASTE_SPELLS, ObjectGuid::Empty, 0, true, false);
        caster->RemoveAurasByType(SPELL_AURA_MOD_DECREASE_SPEED);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_mage_glyph_of_icy_veins::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 56372 - Glyph of Ice Block
class spell_mage_glyph_of_ice_block : public AuraScript
{
    PrepareAuraScript(spell_mage_glyph_of_ice_block);

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        Unit* caster = eventInfo.GetActor();
        caster->GetSpellHistory()->ResetCooldowns([](SpellHistory::CooldownStorageType::iterator itr) -> bool
        {
            SpellInfo const* cdSpell = sSpellMgr->GetSpellInfo(itr->first);
            if (!cdSpell || cdSpell->SpellFamilyName != SPELLFAMILY_MAGE
                || !(cdSpell->SpellFamilyFlags[0] & 0x00000040))
                return false;
            return true;
        }, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_mage_glyph_of_ice_block::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// -44445 - Hot Streak
class spell_mage_hot_streak : public AuraScript
{
    PrepareAuraScript(spell_mage_hot_streak);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_HOT_STREAK_PROC });
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        AuraEffect* counter = GetEffect(EFFECT_1);
        if (!counter)
            return;

        // Count spell criticals in a row in second aura
        if (eventInfo.GetHitMask() & PROC_HIT_CRITICAL)
        {
            counter->SetAmount(counter->GetAmount() * 2);
            if (counter->GetAmount() < 100) // not enough
                return;

            // roll chance
            if (!roll_chance_i(aurEff->GetAmount()))
                return;

            Unit* caster = eventInfo.GetActor();
            caster->CastSpell(caster, SPELL_MAGE_HOT_STREAK_PROC, aurEff);
        }

        // reset counter
        counter->SetAmount(25);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_mage_hot_streak::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// -11426 - Ice Barrier
class spell_mage_ice_barrier : public spell_mage_incanters_absorbtion_base_AuraScript
{
    PrepareAuraScript(spell_mage_ice_barrier);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_SHATTERED_BARRIER });
    }

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = false;
        if (Unit* caster = GetCaster())
        {
            // +80.68% from sp bonus
            float bonus = 0.8068f;

            bonus *= caster->SpellBaseHealingBonusDone(GetSpellInfo()->GetSchoolMask());

            // Glyph of Ice Barrier: its weird having a SPELLMOD_ALL_EFFECTS here but its blizzards doing :)
            // Glyph of Ice Barrier is only applied at the spell damage bonus because it was already applied to the base value in CalculateSpellDamage
            bonus = caster->ApplyEffectModifiers(GetSpellInfo(), aurEff->GetEffIndex(), bonus);

            bonus *= caster->CalculateSpellpowerCoefficientLevelPenalty(GetSpellInfo());

            amount += int32(bonus);
        }
    }

    void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        // Shattered Barrier
        // Procs only if removed by damage.
        if (aurEff->GetAmount() <= 0)
            if (Unit* caster = GetCaster())
                if (AuraEffect* dummy = caster->GetDummyAuraEffect(SPELLFAMILY_MAGE, SPELL_ICON_MAGE_SHATTERED_BARRIER, EFFECT_0))
                    if (roll_chance_i(dummy->GetSpellInfo()->ProcChance))
                        caster->CastSpell(GetTarget(), SPELL_MAGE_SHATTERED_BARRIER, aurEff);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_ice_barrier::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_ice_barrier::Trigger, EFFECT_0);
        AfterEffectRemove += AuraEffectRemoveFn(spell_mage_ice_barrier::AfterRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
    }
};

// 45438 - Ice Block
class spell_mage_ice_block : public SpellScript
{
    PrepareSpellScript(spell_mage_ice_block);

    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellInfo({ spellInfo->ExcludeCasterAuraSpell });
    }

    void TriggerHypothermia()
    {
        GetCaster()->CastSpell(nullptr, GetSpellInfo()->ExcludeCasterAuraSpell, true);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_mage_ice_block::TriggerHypothermia);
    }
};

// -11119 - Ignite
class spell_mage_ignite : public AuraScript
{
    PrepareAuraScript(spell_mage_ignite);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_IGNITE });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetProcTarget();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        SpellInfo const* igniteDot = sSpellMgr->AssertSpellInfo(SPELL_MAGE_IGNITE);
        int32 pct = aurEff->GetAmount();

        // Aleist3r: description of this talent could be interpreted in multiple ways
        // unless I am overthinking
        if (GetCaster()->HasAura(SPELL_MAGE_FUEL_THE_FIRE) && eventInfo.GetSpellInfo()->Id == SPELL_MAGE_FIRE_BLAST)
            AddPct(pct, sSpellMgr->GetSpellInfo(SPELL_MAGE_FUEL_THE_FIRE)->GetEffect(EFFECT_0).CalcValue());

        ASSERT(igniteDot->GetMaxTicks(eventInfo.GetActor()) > 0);
        int32 amount = int32(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), pct) / igniteDot->GetMaxTicks(eventInfo.GetActor()));

        CastSpellExtraArgs args(aurEff);
        args.AddSpellBP0(amount);
        GetTarget()->CastSpell(eventInfo.GetProcTarget(), SPELL_MAGE_IGNITE, args);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_ignite::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_mage_ignite::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// -44457 - Living Bomb
class spell_mage_living_bomb : public AuraScript
{
    PrepareAuraScript(spell_mage_living_bomb);

    bool Validate(SpellInfo const* spell) override
    {
        return ValidateSpellInfo({ static_cast<uint32>(spell->GetEffect(EFFECT_1).CalcValue()) });
    }

    void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(GetTarget(), SPELL_MAGE_LIVING_BOMB_DIRECT_DAMAGE, aurEff);
            if (caster->HasAura(SPELL_MAGE_LIVING_BOMBARDMENT) && aurEff->GetId() != SPELL_MAGE_LIVING_BOMB_LB)
                caster->CastSpell(GetTarget(), SPELL_MAGE_LIVING_BOMB_DUMMY_AURA, aurEff);

            if (caster->HasAura(SPELL_MAGE_FEEL_THE_BURN_TALENT))
                caster->CastSpell(caster, SPELL_MAGE_FEEL_THE_BURN_PROC, true);
        }
    }

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_GROUND_ZERO_TALENT))
                caster->CastSpell(GetTarget(), SPELL_MAGE_GROUND_ZERO_PROC, aurEff);
    }

    void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
        if (removeMode != AURA_REMOVE_BY_ENEMY_SPELL && removeMode != AURA_REMOVE_BY_EXPIRE)
            return;

        if (Unit* caster = GetCaster())
        {
            caster->CastSpell(GetTarget(), uint32(aurEff->GetAmount()), aurEff);

            if (caster->HasAura(SPELL_MAGE_LIVING_BOMBARDMENT) && aurEff->GetId() != SPELL_MAGE_LIVING_BOMB_LB)
                caster->CastSpell(GetTarget(), SPELL_MAGE_LIVING_BOMB_DUMMY, aurEff);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_mage_living_bomb::OnApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_mage_living_bomb::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_mage_living_bomb::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// -29441 - Magic Absorption
class spell_mage_magic_absorption : public AuraScript
{
    PrepareAuraScript(spell_mage_magic_absorption);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_MAGIC_ABSORPTION_MANA });
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* caster = eventInfo.GetActionTarget();
        CastSpellExtraArgs args(aurEff);
        args.AddSpellBP0(CalculatePct(caster->GetMaxPower(POWER_MANA), aurEff->GetAmount()));
        caster->CastSpell(caster, SPELL_MAGE_MAGIC_ABSORPTION_MANA, args);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_mage_magic_absorption::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// -1463 - Mana Shield
class spell_mage_mana_shield : public spell_mage_incanters_absorbtion_base_AuraScript
{
    PrepareAuraScript(spell_mage_mana_shield);

    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_ARCANE_SURGE }) &&
            spell_mage_incanters_absorbtion_base_AuraScript::Validate(spellInfo);
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = false;
        if (Unit* caster = GetCaster())
        {
            // +80.53% from sp bonus
            float bonus = 0.8053f;

            bonus *= caster->SpellBaseHealingBonusDone(GetSpellInfo()->GetSchoolMask());
            bonus *= caster->CalculateSpellpowerCoefficientLevelPenalty(GetSpellInfo());

            amount += int32(bonus);
        }
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = eventInfo.GetActionTarget();
        caster->CastSpell(caster, SPELL_MAGE_ARCANE_SURGE, aurEff);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_mana_shield::CalculateAmount, EFFECT_0, SPELL_AURA_MANA_SHIELD);
        AfterEffectManaShield += AuraEffectManaShieldFn(spell_mage_mana_shield::Trigger, EFFECT_0);

        OnEffectProc += AuraEffectProcFn(spell_mage_mana_shield::HandleProc, EFFECT_0, SPELL_AURA_MANA_SHIELD);
    }
};

// -29074 - Master of Elements
class spell_mage_master_of_elements : public AuraScript
{
    PrepareAuraScript(spell_mage_master_of_elements);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_MASTER_OF_ELEMENTS_ENERGIZE });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!damageInfo || !damageInfo->GetSpellInfo())
            return false;

        return true;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        int32 mana = eventInfo.GetDamageInfo()->GetSpellInfo()->CalcPowerCost(GetTarget(), eventInfo.GetDamageInfo()->GetSchoolMask());
        mana = CalculatePct(mana, aurEff->GetAmount());

        if (mana > 0)
        {
            CastSpellExtraArgs args(aurEff);
            args.AddSpellBP0(mana);
            GetTarget()->CastSpell(GetTarget(), SPELL_MAGE_MASTER_OF_ELEMENTS_ENERGIZE, args);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_master_of_elements::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_mage_master_of_elements::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 55342 - Mirror Image
class spell_mage_mirror_image : public AuraScript
{
    PrepareAuraScript(spell_mage_mirror_image);

    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellInfo({ spellInfo->GetEffect(EFFECT_2).TriggerSpell });
    }

    void PeriodicTick(AuraEffect const* aurEff)
    {
        // Set name of summons to name of caster
        GetTarget()->CastSpell(nullptr, aurEff->GetSpellEffectInfo().TriggerSpell, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_mirror_image::PeriodicTick, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// -44404 - Missile Barrage
class spell_mage_missile_barrage : public AuraScript
{
    PrepareAuraScript(spell_mage_missile_barrage);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (!spellInfo)
            return false;

        // Arcane Blast - full chance
        if (spellInfo->SpellFamilyFlags[0] & 0x20000000)
            return true;

        // Rest of spells have half chance
        return roll_chance_i(50);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_missile_barrage::CheckProc);
    }
};

// 44401 - Missile Barrage
class spell_mage_missile_barrage_proc : public AuraScript
{
    PrepareAuraScript(spell_mage_missile_barrage_proc);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_T10_2P_BONUS, SPELL_MAGE_T8_4P_BONUS });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = eventInfo.GetActor();
        // Prevent double proc for Arcane missiles
        if (caster == eventInfo.GetProcTarget())
            return false;

        // Proc chance is unknown, we'll just use dummy aura amount
        if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_MAGE_T8_4P_BONUS, EFFECT_0))
            if (roll_chance_i(aurEff->GetAmount()))
                return false;

        return true;
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetTarget();
        if (caster->HasAura(SPELL_MAGE_T10_2P_BONUS))
            if (Aura* aura = caster->GetAuraOfRankedSpell(SPELL_MAGE_ARCANE_MISSILES_R1))
                if (spell_mage_arcane_missiles* missiles = aura->GetScript<spell_mage_arcane_missiles>(ScriptName))
                    missiles->AllowT10Proc();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_missile_barrage_proc::CheckProc);
        AfterEffectRemove += AuraEffectRemoveFn(spell_mage_missile_barrage_proc::OnRemove, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }

public:
    static char constexpr const ScriptName[] = "spell_mage_arcane_missiles";
};

enum SilvermoonPolymorph
{
    NPC_AUROSALIA   = 18744,
};

/// @todo move out of here and rename - not a mage spell
// 32826 - Polymorph (Visual)
class spell_mage_polymorph_cast_visual : public SpellScriptLoader
{
    public:
        spell_mage_polymorph_cast_visual() : SpellScriptLoader("spell_mage_polymorph_visual") { }

        class spell_mage_polymorph_cast_visual_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_polymorph_cast_visual_SpellScript);

            static const uint32 PolymorphForms[6];

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo(PolymorphForms);
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetCaster()->FindNearestCreature(NPC_AUROSALIA, 30.0f))
                    if (target->GetTypeId() == TYPEID_UNIT)
                        target->CastSpell(target, PolymorphForms[urand(0, 5)], true);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_mage_polymorph_cast_visual_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_mage_polymorph_cast_visual_SpellScript();
        }
};

const uint32 spell_mage_polymorph_cast_visual::spell_mage_polymorph_cast_visual_SpellScript::PolymorphForms[6] =
{
    SPELL_MAGE_SQUIRREL_FORM,
    SPELL_MAGE_GIRAFFE_FORM,
    SPELL_MAGE_SERPENT_FORM,
    SPELL_MAGE_DRAGONHAWK_FORM,
    SPELL_MAGE_WORGEN_FORM,
    SPELL_MAGE_SHEEP_FORM
};

// 31687 - Summon Water Elemental
class spell_mage_summon_water_elemental : public SpellScript
{
    PrepareSpellScript(spell_mage_summon_water_elemental);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MAGE_GLYPH_OF_ETERNAL_WATER,
            SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY,
            SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT
        });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        // Glyph of Eternal Water
        if (caster->HasAura(SPELL_MAGE_GLYPH_OF_ETERNAL_WATER))
            caster->CastSpell(caster, SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT, true);
        else
            caster->CastSpell(caster, SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY, true);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_mage_summon_water_elemental::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// Duskhaven
class SpellMageCastEvent : public BasicEvent
{
public:
    SpellMageCastEvent(Unit* caster, Unit* victim, uint32 spellId) : _caster(caster), _victim(victim), _spellId(spellId) {}

    bool Execute(uint64 /*time*/, uint32 /*diff*/) override
    {
        _caster->CastSpell(_victim, _spellId);
        return true;
    }

private:
    Unit* _caster;
    Unit* _victim;
    uint32 _spellId;
};

class SpellMageRemoveAuraChargeEvent : public BasicEvent
{
public:
    SpellMageRemoveAuraChargeEvent(Unit* target, uint32 spellId) : _target(target), _spellId(spellId) {}

    bool Execute(uint64 /*time*/, uint32 /*diff*/) override
    {
        _target->GetAura(_spellId)->DropCharge();
        return true;
    }

private:
    Unit* _target;
    uint32 _spellId;
};

// 1280011 - Blink
class spell_mage_blink : public SpellScript
{
    PrepareSpellScript(spell_mage_blink);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MAGE_BLINK,
            SPELL_MAGE_FRICTION_BARRIER_PROC,
            SPELL_MAGE_FRICTION_BARRIER_TALENT
        });
    }

    void HandleOnCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_MAGE_FRICTION_BARRIER_TALENT))
                caster->CastSpell(caster, SPELL_MAGE_FRICTION_BARRIER_PROC, true);

            if (caster->HasAura(SPELL_MAGE_HOT_SECOND_TALENT))
                caster->CastSpell(caster, SPELL_MAGE_HOT_SECOND_PROC, true);
        }
    }

    void HandleAfterHit()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_DISPLACEMENT_DUMMY_TALENT))
                caster->CastSpell(caster, SPELL_MAGE_DISPLACEMENT_SUMMON, true);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mage_blink::HandleOnCast);
        AfterHit += SpellHitFn(spell_mage_blink::HandleAfterHit);
    }
};

// 1280023, 1280024, 1280026, 1280029 - Barriers
class spell_mage_barriers_aura : public AuraScript
{
    PrepareAuraScript(spell_mage_barriers_aura);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MAGE_COLD_WINDS,
            SPELL_MAGE_COLD_WINDS_PROC,
            SPELL_MAGE_MANA_BARRIER,
            SPELL_MAGE_MANA_BARRIER_PROC
        });
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = false;
        if (Unit* caster = GetCaster())
        {
            int32 casterHp = caster->GetMaxHealth();
            int32 spellPct = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue();
            amount += CalculatePct(casterHp, spellPct);

            if (caster->HasAura(SPELL_MAGE_MANA_BARRIER))
                amount += CalculatePct(amount, sSpellMgr->GetSpellInfo(SPELL_MAGE_MANA_BARRIER)->GetEffect(EFFECT_0).CalcValue());
        }
    }

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_MAGE_MANA_BARRIER))
            {
                int32 spellPct = sSpellMgr->GetSpellInfo(SPELL_MAGE_MANA_BARRIER)->GetEffect(EFFECT_1).CalcValue();
                CastSpellExtraArgs args(aurEff);
                args.AddSpellBP0(int32(CalculatePct(caster->GetMaxPower(POWER_MANA), spellPct)));
                caster->CastSpell(caster, SPELL_MAGE_MANA_BARRIER_PROC, args);
            }

            if (caster->HasAura(SPELL_MAGE_COLD_WINDS))
            {
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode != AURA_REMOVE_BY_EXPIRE)
                    caster->CastSpell(caster, SPELL_MAGE_COLD_WINDS_PROC, true);
            }
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_barriers_aura::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectRemove += AuraEffectRemoveFn(spell_mage_barriers_aura::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
    }
};

// 1280024 - Blazing Barrier
class spell_mage_blazing_barrier : public spell_mage_incanters_absorbtion_base_AuraScript
{
    PrepareAuraScript(spell_mage_blazing_barrier);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MAGE_BLAZING_BARRIER_PROC
        });
    }

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(caster, SPELL_MAGE_BLAZING_BARRIER_PROC, aurEff);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_mage_blazing_barrier::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
        AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_blazing_barrier::Trigger, EFFECT_0);
    }
};

// 1290005 - Blizzard
class spell_mage_blizzard : public SpellScript
{
    PrepareSpellScript(spell_mage_blizzard);

    void HandleOnCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_MAGE_ICEFALL_PROC) && caster->HasAura(SPELL_MAGE_ICEFALL_PROC_DMG))
            {
                caster->RemoveAura(SPELL_MAGE_ICEFALL_PROC);
                int32 duration = sSpellMgr->GetSpellInfo(SPELL_MAGE_BLIZZARD)->GetDuration();
                caster->m_Events.AddEvent(new SpellMageRemoveAuraChargeEvent(caster, SPELL_MAGE_ICEFALL_PROC_DMG), caster->m_Events.CalculateTime(Milliseconds(duration + 10)));
            }

            if (caster->HasAura(SPELL_MAGE_BRAIN_CHILL))
            {
                int32 chance = sSpellMgr->GetSpellInfo(SPELL_MAGE_BRAIN_CHILL)->GetEffect(EFFECT_0).CalcValue();

                if (roll_chance_i(chance))
                    caster->CastSpell(caster, SPELL_MAGE_BRAIN_FREEZE_PROC, true);
            }

            if (caster->HasAura(SPELL_MAGE_SNOWSTORM_TALENT))
                caster->CastSpell(caster, SPELL_MAGE_SNOWSTORM_PROC, true);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_mage_blizzard::HandleOnCast);
    }
};

// 1280003 - Chilled
class spell_mage_chilled : public AuraScript
{
    PrepareAuraScript(spell_mage_chilled);

    void HandleDummyTick(AuraEffect const* aurEff)
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_CHILLING_SIPHON))
            {
                float spellPct = sSpellMgr->GetSpellInfo(SPELL_MAGE_CHILLED_ENERGIZE)->GetEffect(EFFECT_1).CalcValue() / 10;
                int32 amount = CalculatePct(caster->GetMaxPower(POWER_MANA), spellPct);
                CastSpellExtraArgs args(aurEff);
                args.AddSpellBP0(amount);
                caster->CastSpell(caster, SPELL_MAGE_CHILLED_ENERGIZE, args);
            }
    }

    void HandleDamageTick(AuraEffect const* aurEff)
    {
        if (Unit* caster = GetCaster())
            if (!caster->HasAura(SPELL_MAGE_BITTING_FROST))
                PreventDefaultAction();
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_chilled::HandleDummyTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_chilled::HandleDamageTick, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 1280014 - Cone of Cold
class spell_mage_cone_of_cold : public SpellScript
{
    PrepareSpellScript(spell_mage_cone_of_cold);

    void HandleOnCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_ICY_GALE))
            {
                caster->CastSpell(caster, SPELL_MAGE_FROST_MASTERY_ICICLE_AURA, true);

                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_MAGE_FROST_MASTERY_ICICLE, EFFECT_1))
                    if (irand(1, 100) <= aurEff->GetAmount())
                        caster->CastSpell(caster, SPELL_MAGE_FROST_MASTERY_ICICLE_AURA, true);
            }

    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mage_cone_of_cold::HandleOnCast);
    }
};

// 1280014, 1290061 - Cone of Cold, Galefury talent proc
class spell_mage_cone_of_cold_galefury : public SpellScript
{
    PrepareSpellScript(spell_mage_cone_of_cold_galefury);

    void HandleOnCast()
    {
        if (caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_GALEFURY))
                damage = GetHitDamage();
    }

    void HandleAfterCast()
    {
        if (caster && caster->HasAura(SPELL_MAGE_GALEFURY))
        {
            int32 chance = sSpellMgr->GetSpellInfo(SPELL_MAGE_GALEFURY)->GetEffect(EFFECT_0).CalcValue();
            if (roll_chance_i(chance))
            {
                damage *= sSpellMgr->GetSpellInfo(SPELL_MAGE_GALEFURY)->GetEffect(EFFECT_1).CalcValue() / 100;
                CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
                args.AddSpellBP0(damage);
                caster->CastSpell(caster, SPELL_MAGE_GALEFURY_CONE_OF_COLD, args);
            }
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mage_cone_of_cold_galefury::HandleOnCast);
        AfterCast += SpellCastFn(spell_mage_cone_of_cold_galefury::HandleAfterCast);
    }

private:
    int32 damage;
    Unit* caster;
};

// 1280070 - Displacement
class spell_mage_displacement : public AuraScript
{
    PrepareAuraScript(spell_mage_displacement);

    void HandleTeleport(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Player* player = GetTarget()->ToPlayer())
        {
            if (GameObject* circle = player->GetGameObject(SPELL_MAGE_DISPLACEMENT_SUMMON))
            {
                player->NearTeleportTo(circle->GetPositionX(), circle->GetPositionY(), circle->GetPositionZ(), circle->GetOrientation());
                player->RemoveMovementImpairingAuras(false);
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_mage_displacement::HandleTeleport, EFFECT_0, SPELL_AURA_MECHANIC_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 1280071 - Displacement: Summon
class spell_mage_displacement_summon : public AuraScript
{
    PrepareAuraScript(spell_mage_displacement_summon);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
    {
        if (!(mode & AURA_EFFECT_HANDLE_REAPPLY))
            GetTarget()->RemoveGameObject(GetId(), true);

        GetTarget()->RemoveAura(SPELL_MAGE_DISPLACEMENT_ALLOW_CAST);
    }

    void HandleDummyTick(AuraEffect const* /*aurEff*/)
    {
        if (GameObject* circle = GetTarget()->GetGameObject(GetId()))
        {
            SpellInfo const* spellInfo = sSpellMgr->AssertSpellInfo(SPELL_MAGE_DISPLACEMENT_TELEPORT);

            if (GetTarget()->IsWithinDist(circle, spellInfo->GetMaxRange(true)))
            {
                if (!GetTarget()->HasAura(SPELL_MAGE_DISPLACEMENT_ALLOW_CAST))
                    GetTarget()->CastSpell(GetTarget(), SPELL_MAGE_DISPLACEMENT_ALLOW_CAST, true);
            }
            else
                GetTarget()->RemoveAura(SPELL_MAGE_DISPLACEMENT_ALLOW_CAST);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectApplyFn(spell_mage_displacement_summon::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_displacement_summon::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 1280000 - Fireball
class spell_mage_fireball : public SpellScript
{
    PrepareSpellScript(spell_mage_fireball);

    void HandleOnHit()
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
                if (target->HasAura(SPELL_MAGE_SMOLDERING_PROC, caster->GetGUID()) && caster->HasAura(SPELL_MAGE_LIVING_MINEFIELD_TALENT))
                    caster->CastSpell(caster, SPELL_MAGE_LIVING_MINEFIELD_PROC, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_mage_fireball::HandleOnHit);
    }
};

// 1300007 - Fire Blast
class spell_mage_fire_blast : public SpellScript
{
    PrepareSpellScript(spell_mage_fire_blast);

    void HandleEffect(SpellEffIndex /*effindex*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->GetTypeId() == TYPEID_PLAYER && caster->HasAura(SPELL_MAGE_GREAT_INFERNO))
            {
                float crit = caster->ToPlayer()->GetRatingBonusValue(CombatRating(CR_CRIT_SPELL)) / 2;
                int32 damage = GetHitDamage();
                AddPct(damage, crit);
                SetHitDamage(damage);
            }

            if (caster->HasAura(SPELL_MAGE_BURNING_ADRENALINE))
            {
                int32 chance = sSpellMgr->GetSpellInfo(SPELL_MAGE_BURNING_ADRENALINE)->GetEffect(EFFECT_0).CalcValue();

                if (roll_chance_i(chance))
                    caster->CastSpell(caster, SPELL_MAGE_ELEMENTAL_HEART_PROC, true);
            }

            if (caster->HasAura(SPELL_MAGE_FEEL_THE_BURN_TALENT))
                caster->CastSpell(caster, SPELL_MAGE_FEEL_THE_BURN_PROC, true);
        }
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_mage_fire_blast::HandleEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 1290011 - Flurry
class spell_mage_flurry : public SpellScript
{
    PrepareSpellScript(spell_mage_flurry);

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();

        if (caster->HasAura(SPELL_MAGE_ICEFLURRY))
        {
            uint32 stacks = sSpellMgr->GetSpellInfo(SPELL_MAGE_ICEFLURRY)->GetEffect(EFFECT_0).CalcValue();

            for (uint32 i = 0; i < stacks; ++i)
                caster->CastSpell(caster, SPELL_MAGE_FROST_MASTERY_ICICLE_AURA, true);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_mage_flurry::HandleAfterCast);
    }
};

// 1290038 - Flurry
class spell_mage_flurry_tick : public SpellScript
{
    PrepareSpellScript(spell_mage_flurry_tick);

    void HandleAfterHit()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_BRAIN_FREEZE_PROC))
                caster->RemoveAura(SPELL_MAGE_BRAIN_FREEZE_PROC);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_mage_flurry_tick::HandleAfterHit);
    }
};

// 1280023 - Frost Barrier
class spell_mage_frost_barrier : public spell_mage_incanters_absorbtion_base_AuraScript
{
    PrepareAuraScript(spell_mage_frost_barrier);

    void Register() override
    {
        AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_frost_barrier::Trigger, EFFECT_0);
    }
};

// 1290033 - Frozen Orn
class spell_mage_frozen_orb : public SpellScript
{
    PrepareSpellScript(spell_mage_frozen_orb);

    void HandleOnCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_ICEFALL_TALENT))
            {
                caster->CastSpell(caster, SPELL_MAGE_ICEFALL_PROC, true);
                caster->CastSpell(caster, SPELL_MAGE_ICEFALL_PROC_DMG, true);
            }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mage_frozen_orb::HandleOnCast);
    }
};

// 1290035 - Frozen Orb
class spell_mage_frozen_orb_dot : public AuraScript
{
    PrepareAuraScript(spell_mage_frozen_orb_dot);

    void OnPeriodic(AuraEffect const* aurEff)
    {
        uint32 tickNumber = aurEff->GetTickNumber();
        uint32 maxTick = aurEff->GetTotalTicks();

        if (Unit* caster = GetCaster())
            if (tickNumber == maxTick)
                if (caster->HasAura(SPELL_MAGE_FROST_BOMB_TALENT))
                {
                    PreventDefaultAction();
                    caster->CastSpell(GetTarget(), SPELL_MAGE_FROST_BOMB_PROC, true);
                }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_frozen_orb_dot::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 1300044 - Hot Investment
class spell_mage_hot_investment : public AuraScript
{
    PrepareAuraScript(spell_mage_hot_investment);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGE_FIREBALL });
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        AuraEffect* counter = GetEffect(EFFECT_1);
        if (!counter)
            return;

        // Count spell criticals in a row in second aura
        if (eventInfo.GetHitMask() & PROC_HIT_CRITICAL)
        {
            counter->SetAmount(counter->GetAmount() + 25);
            if (counter->GetAmount() < 100) // not enough
                return;

            // roll chance
            if (!roll_chance_i(aurEff->GetAmount()))
                return;

            Unit* caster = eventInfo.GetActor();
            Unit* target = eventInfo.GetDamageInfo()->GetVictim();
            caster->CastSpell(target, SPELL_MAGE_FIREBALL, aurEff);
        }

        // reset counter
        counter->SetAmount(25);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_mage_hot_investment::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 1300001 - Hot Streak
class spell_mage_hot_streak_proc : public SpellScript
{
    PrepareSpellScript(spell_mage_hot_streak_proc);

    void HandleOnCast()
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_MAGE_DRAGON_HEART_TALENT))
            {
                int32 pctAmount = sSpellMgr->GetSpellInfo(SPELL_MAGE_DRAGON_HEART_TALENT)->GetEffect(EFFECT_0).CalcValue();
                int32 amount = CalculatePct(caster->GetMaxPower(POWER_MANA), pctAmount);
                CastSpellExtraArgs args(TRIGGERED_FULL_MASK);
                args.AddSpellBP0(amount);
                caster->CastSpell(caster, SPELL_MAGE_DRAGON_HEART_MANA_PROC, args);
                caster->CastSpell(caster, SPELL_MAGE_DRAGON_HEART_PROC, true);
            }

            if (caster->HasAura(SPELL_MAGE_ELEMENTAL_HEART_TALENT))
                caster->CastSpell(caster, SPELL_MAGE_ELEMENTAL_HEART_PROC, true);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mage_hot_streak_proc::HandleOnCast);
    }
};

// 1290000 - Ice Lance
class spell_mage_ice_lance : public SpellScript
{
    PrepareSpellScript(spell_mage_ice_lance);

    void HandleHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (caster && caster->HasAura(SPELL_MAGE_FROST_MASTERY_ICICLE_AURA))
        {
            Aura* icicleStack = caster->GetAura(SPELL_MAGE_FROST_MASTERY_ICICLE_AURA);
            uint32 stacks = icicleStack->GetStackAmount();
            if (target)
                for (uint32 i = 0; i < stacks; ++i)
                {
                    caster->RemoveAuraFromStack(SPELL_MAGE_FROST_MASTERY_ICICLE_AURA);
                    caster->m_Events.AddEvent(new SpellMageCastEvent(caster, target, SPELL_MAGE_FROST_MASTERY_ICICLE_SPELL), caster->m_Events.CalculateTime(Milliseconds(i * 200)));
                    caster->RemoveAura(SPELL_MAGE_FROST_MASTERY_ICICLE_VIS1 + i);
                }
        }
    }

    void HandleAfterHit()
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
                if (target->HasAuraState(AURA_STATE_FROZEN) || target->HasAura(SPELL_MAGE_FLURRY_BRITTLEFROST) || caster->HasAura(SPELL_MAGE_FINGERS_OF_FROST_PROC))
                    caster->CastSpell(caster, SPELL_MAGE_CHAIN_REACTION_PROC, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_mage_ice_lance::HandleHit);
        AfterHit += SpellHitFn(spell_mage_ice_lance::HandleAfterHit);
    }
};

// 1290064 - Ice Skating
class spell_mage_ice_skating : public AuraScript
{
    PrepareAuraScript(spell_mage_ice_skating);
    
    void OnPeriodic(AuraEffect const* aurEff)
    {
        if (Unit* target = GetTarget())
            if (!target->isMoving())
                PreventDefaultAction();
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_ice_skating::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

// 1300005 - Ignite
class spell_mage_ignite_proc : public SpellScript
{
    PrepareSpellScript(spell_mage_ignite_proc);

    void HandleOnHit()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_WORLD_IN_FLAMES_TALENT))
                caster->CastSpell(caster, SPELL_MAGE_WORLD_IN_FLAMES_PROC, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_mage_ignite_proc::HandleOnHit);
    }
};

// 1300011 - Living Bomb - AoE
class spell_mage_living_bomb_aoe : public SpellScript
{
    PrepareSpellScript(spell_mage_living_bomb_aoe);

    void HandleOnCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_BURN_IT_ALL_DOWN))
                caster->CastSpell(caster, SPELL_MAGE_HOT_STREAK_PROC, true);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mage_living_bomb_aoe::HandleOnCast);
    }
};

// 1300028 - Living Bomb - Direct Damage
class spell_mage_living_bomb_damage : public SpellScript
{
    PrepareSpellScript(spell_mage_living_bomb_damage);

    void HandleAfterHit()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_BURN_IT_ALL_DOWN))
                caster->CastSpell(caster, SPELL_MAGE_HOT_STREAK_PROC, true);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_mage_living_bomb_damage::HandleAfterHit);
    }
};

// 1300017 - Living Bomb - Living Bombardment
class spell_mage_living_bomb_dummy : public SpellScript
{
    PrepareSpellScript(spell_mage_living_bomb_dummy);

    void RemoveInvalidTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_MAGE_LIVING_BOMB_DUMMY_AURA));
    }

    void ApplyEffect()
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
                caster->CastSpell(target, SPELL_MAGE_LIVING_BOMB_LB, true);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_living_bomb_dummy::RemoveInvalidTargets, EFFECT_ALL, TARGET_UNIT_DEST_AREA_ENEMY);
        AfterHit += SpellHitFn(spell_mage_living_bomb_dummy::ApplyEffect);
    }
};

// 1280001 - Mage Armor
class spell_mage_mage_armor : public AuraScript
{
    PrepareAuraScript(spell_mage_mage_armor);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MAGE_FROST_ARMOR_AURA,
            SPELL_MAGE_FROST_ARMOR_TALENT,
            SPELL_MAGE_MOLTEN_ARMOR_AURA,
            SPELL_MAGE_MOLTEN_ARMOR_TALENT
        });
    }

    void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_MAGE_FROST_ARMOR_TALENT))
                caster->CastSpell(caster, SPELL_MAGE_FROST_ARMOR_AURA, true);

            if (caster->HasAura(SPELL_MAGE_MOLTEN_ARMOR_TALENT))
                caster->CastSpell(caster, SPELL_MAGE_MOLTEN_ARMOR_AURA, true);
        }
    }

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->HasAura(SPELL_MAGE_FROST_ARMOR_AURA))
                caster->RemoveAura(SPELL_MAGE_FROST_ARMOR_AURA);

            if (caster->HasAura(SPELL_MAGE_MOLTEN_ARMOR_AURA))
                caster->RemoveAura(SPELL_MAGE_MOLTEN_ARMOR_AURA);
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_mage_mage_armor::OnApply, EFFECT_0, SPELL_AURA_MOD_RESISTANCE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        AfterEffectRemove += AuraEffectRemoveFn(spell_mage_mage_armor::OnRemove, EFFECT_0, SPELL_AURA_MOD_RESISTANCE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 1280013 - Mana Gem
class spell_mage_mana_gem : public SpellScript
{
    PrepareSpellScript(spell_mage_mana_gem);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MAGE_MANA_GEM,
            SPELL_MAGE_MANA_GEM_ENERGIZE,
            SPELL_MAGE_PRISTINE_MANA_GEM
        });
    }

    void HandleEffect(SpellEffIndex /*effindex*/)
    {
        Unit* caster = GetCaster();
        int32 amount = 0;
        int32 pctAmount = sSpellMgr->GetSpellInfo(SPELL_MAGE_MANA_GEM)->GetEffect(EFFECT_0).CalcValue();

        if (caster->HasAura(SPELL_MAGE_PRISTINE_MANA_GEM))
            pctAmount += sSpellMgr->GetSpellInfo(SPELL_MAGE_PRISTINE_MANA_GEM)->GetEffect(EFFECT_0).CalcValue();

        amount = CalculatePct(caster->GetMaxPower(POWER_MANA), pctAmount);

        caster->CastSpell(caster, SPELL_MAGE_MANA_GEM_ENERGIZE, true);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_mage_mana_gem::HandleEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 1290021 - Mastery: Icicle
class spell_mage_mastery_icicle_aura : public SpellScript
{
    PrepareSpellScript(spell_mage_mastery_icicle_aura);

    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        uint32 stacks = 0;

        if (!caster->HasAura(SPELL_MAGE_FROST_MASTERY_ICICLE_AURA))
            caster->CastSpell(caster, SPELL_MAGE_FROST_MASTERY_ICICLE_VIS1, true);
        else
        {
            stacks = caster->GetAura(SPELL_MAGE_FROST_MASTERY_ICICLE_AURA)->GetStackAmount();

            if (stacks < 5)
                caster->CastSpell(caster, SPELL_MAGE_FROST_MASTERY_ICICLE_VIS1 + stacks, true);
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_mage_mastery_icicle_aura::HandleOnHit);
    }
};

// 1280026 - Prismatic Barrier
class spell_mage_prismatic_barrier : public spell_mage_incanters_absorbtion_base_AuraScript
{
    PrepareAuraScript(spell_mage_prismatic_barrier);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!damageInfo)
            return false;
        else
            absorbed = CalculatePct(eventInfo.GetDamageInfo()->GetAbsorb(), GetEffectInfo(EFFECT_1).CalcValue());

        return true;
    }

    void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (absorbed > 0)
        {
            Unit* caster = GetCaster();
            CastSpellExtraArgs args(aurEff);
            args.AddSpellBP0(absorbed);
            caster->CastSpell(caster, GetEffectInfo(EFFECT_1).TriggerSpell, args);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_prismatic_barrier::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_mage_prismatic_barrier::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_prismatic_barrier::Trigger, EFFECT_0);
    }

private:
    int32 absorbed = 0;
};

// 1300006 - Pyroblast
class spell_mage_pyroblast : public SpellScript
{
    PrepareSpellScript(spell_mage_pyroblast);

    void HandleOnHit()
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
                if (target->HasAura(SPELL_MAGE_SMOLDERING_PROC, caster->GetGUID()) && caster->HasAura(SPELL_MAGE_LIVING_MINEFIELD_TALENT))
                    caster->CastSpell(caster, SPELL_MAGE_LIVING_MINEFIELD_PROC, true);   
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_mage_pyroblast::HandleOnHit);
    }
};

// 1290029 - Slice and Ice
class spell_mage_slice_and_ice : public SpellScript
{
    PrepareSpellScript(spell_mage_slice_and_ice);

    void HandleOnHit()
    {
        target = GetHitUnit();

        if (target && target->HasAura(SPELL_MAGE_SLICE_AND_ICE_BUFF))
            duration = target->GetAura(SPELL_MAGE_SLICE_AND_ICE_BUFF)->GetDuration();
    }

    void HandleAfterHit()
    {
        if (target && target->HasAura(SPELL_MAGE_SLICE_AND_ICE_BUFF))
        {
            Aura* aura = target->GetAura(SPELL_MAGE_SLICE_AND_ICE_BUFF);

            if (duration && aura->GetStackAmount() > 1)
                aura->SetDuration(duration);
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_mage_slice_and_ice::HandleOnHit);
        AfterHit += SpellHitFn(spell_mage_slice_and_ice::HandleAfterHit);
    }

private:
    Unit* target;
    float duration = 0;
};

// 1290068 - Snowball
class spell_mage_snowball : public SpellScript
{
    PrepareSpellScript(spell_mage_snowball);

    void HandleOnCast()
    {
        if (Unit* caster = GetCaster())
            if (caster->HasAura(SPELL_MAGE_SNOWCONE))
                caster->GetSpellHistory()->ResetCooldowns([](SpellHistory::CooldownStorageType::iterator itr) -> bool
                    {
                        SpellInfo const* spellInfo = sSpellMgr->AssertSpellInfo(itr->first);
                        return spellInfo->SpellFamilyName == SPELLFAMILY_MAGE && (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_FROST) &&
                            spellInfo->SpellFamilyFlags[0] & 0x400 && spellInfo->GetRecoveryTime() > 0;
                    }, true);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_mage_snowball::HandleOnCast);
    }
};

// 1290030 - Splitting Ice
class spell_mage_splitting_ice : public AuraScript
{
    PrepareAuraScript(spell_mage_splitting_ice);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        float range = sSpellMgr->GetSpellInfo(SPELL_MAGE_SPLITTING_ICE)->GetEffect(EFFECT_2).CalcValue();
        _procTarget = eventInfo.GetActor()->SelectNearbyTarget(eventInfo.GetProcTarget(), range);
        return _procTarget != nullptr;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        uint32 spellId = damageInfo->GetSpellInfo()->Id;
        CastSpellExtraArgs args(aurEff);
        args.SetOriginalCaster(GetCasterGUID());

        if (spellId == SPELL_MAGE_ICE_LANCE)
            _procTarget->CastSpell(_procTarget, SPELL_MAGE_SPLITTING_ICE_ICE_LANCE, args);
        else if (spellId == SPELL_MAGE_FROST_MASTERY_ICICLE_SPELL)
            _procTarget->CastSpell(_procTarget, SPELL_MAGE_SPLITTING_ICE_ICICLE, args);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_mage_splitting_ice::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_mage_splitting_ice::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }

private:
    Unit* _procTarget = nullptr;
};

// 1290031, 1290032 - Splitting Ice - Icicle, Ice Lance
class spell_mage_splitting_ice_damage : public SpellScript
{
    PrepareSpellScript(spell_mage_splitting_ice_damage);

    void RecalculateDamage()
    {
        int32 damage = GetHitDamage() * (sSpellMgr->GetSpellInfo(SPELL_MAGE_SPLITTING_ICE)->GetEffect(EFFECT_0).CalcValue()/100);

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_mage_splitting_ice_damage::RecalculateDamage);
    }
};

// 1280020 - Time Warp
class spell_mage_time_warp : public SpellScript
{
    PrepareSpellScript(spell_mage_time_warp);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
        {
            SPELL_MAGE_TEMPORAL_DISPLACEMENT,
            SPELL_SHAMAN_EXHAUSTION,
            SPELL_SHAMAN_SATED,
        });
    }

    void RemoveInvalidTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_MAGE_TEMPORAL_DISPLACEMENT));
        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SHAMAN_EXHAUSTION));
        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_SHAMAN_SATED));
    }

    void ApplyDebuff()
    {
        if (Unit* target = GetHitUnit())
            target->CastSpell(target, SPELL_SHAMAN_SATED, true);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_time_warp::RemoveInvalidTargets, EFFECT_ALL, TARGET_UNIT_CASTER_AREA_RAID);

        AfterHit += SpellHitFn(spell_mage_time_warp::ApplyDebuff);
    }
};

void AddSC_mage_spell_scripts()
{
    RegisterSpellScript(spell_mage_arcane_potency);
    RegisterSpellScript(spell_mage_arcane_missiles);
    RegisterSpellScript(spell_mage_blast_wave);
    RegisterSpellScript(spell_mage_blazing_speed);
    RegisterSpellScript(spell_mage_burning_determination);
    RegisterSpellScript(spell_mage_burnout);
    RegisterSpellScript(spell_mage_cold_snap);
    RegisterSpellScript(spell_mage_combustion);
    RegisterSpellScript(spell_mage_combustion_proc);
    RegisterSpellScript(spell_mage_dragon_breath);
    RegisterSpellScript(spell_mage_imp_blizzard);
    RegisterSpellScript(spell_mage_imp_mana_gems);
    RegisterSpellScript(spell_mage_empowered_fire);
    RegisterSpellScript(spell_mage_fingers_of_frost);
    RegisterSpellScript(spell_mage_fire_frost_ward);
    RegisterSpellScript(spell_mage_frostfire_bolt);
    RegisterSpellScript(spell_mage_focus_magic);
    RegisterSpellScript(spell_mage_gen_extra_effects);
    RegisterSpellScript(spell_mage_glyph_of_polymorph);
    RegisterSpellScript(spell_mage_glyph_of_icy_veins);
    RegisterSpellScript(spell_mage_glyph_of_ice_block);
    RegisterSpellScript(spell_mage_hot_streak);
    RegisterSpellScript(spell_mage_ice_barrier);
    RegisterSpellScript(spell_mage_ice_block);
    RegisterSpellScript(spell_mage_ignite);
    RegisterSpellScript(spell_mage_living_bomb);
    RegisterSpellScript(spell_mage_magic_absorption);
    RegisterSpellScript(spell_mage_mana_shield);
    RegisterSpellScript(spell_mage_master_of_elements);
    RegisterSpellScript(spell_mage_mirror_image);
    RegisterSpellScript(spell_mage_missile_barrage);
    RegisterSpellScript(spell_mage_missile_barrage_proc);
    new spell_mage_polymorph_cast_visual();
    RegisterSpellScript(spell_mage_summon_water_elemental);
    // Duskhaven
    RegisterSpellScript(spell_mage_blink);
    RegisterSpellScript(spell_mage_barriers_aura);
    RegisterSpellScript(spell_mage_blazing_barrier);
    RegisterSpellScript(spell_mage_chilled);
    RegisterSpellScript(spell_mage_displacement);
    RegisterSpellScript(spell_mage_displacement_summon);
    RegisterSpellScript(spell_mage_frost_barrier);
    RegisterSpellScript(spell_mage_mage_armor);
    RegisterSpellScript(spell_mage_mana_gem);
    RegisterSpellScript(spell_mage_prismatic_barrier);
    RegisterSpellScript(spell_mage_time_warp);
}
