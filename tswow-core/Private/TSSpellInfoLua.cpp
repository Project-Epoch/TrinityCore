#include "TSLua.h"
#include "TSSpellInfo.h"

void TSLua::load_spell_info_methods(sol::state& state)
{
    auto ts_spelleffectinfo = state.new_usertype<TSSpellEffectInfo>("TSSpellEffectInfo");
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetEffectIndex);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetType);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetAura);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetAmplitude);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetDieSides);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetRealPointsPerLevel);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetBasePoints);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetPointsPerComboPoint);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetValueMultiplier);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetDamageMultiplier);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetBonusMultiplier);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetMiscValue);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetMiscValueB);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetMechanic);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetChainTarget);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetItemType);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, GetTriggerSpell);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, IsEffect);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, IsAura);
    LUA_FIELD(ts_spelleffectinfo, TSSpellEffectInfo, CalcValue);

    auto ts_spellinfo = state.new_usertype<TSSpellInfo>("TSSpellInfo");
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetEntry);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetSchool);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetBaseLevel);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetDmgClass);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetActiveIconID);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetAreaGroupID);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetAttributes);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetAttributesCu);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetAttributesEx);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetAttributesEx2);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetAttributesEx3);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetAttributesEx4);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetAttributesEx5);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetAttributesEx6);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetAttributesEx7);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetAuraInterruptFlags);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetCasterAuraSpell);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetCasterAuraState);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetCasterAuraStateNot);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetCategoryRecoveryTime);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetChannelInterruptFlags);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetDispel);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetEquippedItemClass);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetEquippedItemInventoryTypeMask);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetExcludeCasterAuraSpell);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetExcludeTargetAuraSpell);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetExplicitTargetMask);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetFacingCasterFlags);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetInterruptFlags);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetManaCost);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetManaCostPercentage);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetManaCostPerlevel);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetManaPerSecond);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetManaPerSecondPerLevel);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetMaxAffectedTargets);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetMaxLevel);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetMaxTargetLevel);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetMechanic);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetPowerType);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetPreventionType);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetPriority);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetProcChance);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetProcCharges);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetProcFlags);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetRecoveryTime);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetRequiresSpellFocus);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetRuneCostID);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetSchoolMask);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetSpeed);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetSpellFamilyFlags);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetSpellFamilyName);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetSpellIconID);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetSpellLevel);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetStackAmount);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetStances);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetStancesNot);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetStartRecoveryCategory);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetTargetAuraSpell);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetTargetAuraState);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetTargetAuraStateNot);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetTargetCreatureType);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetTargets);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetEffect);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetTotem);
    LUA_FIELD(ts_spellinfo, TSSpellInfo, GetTalentCost);
    state.set_function("GetSpellInfo", &GetSpellInfo);
    state.set_function("GetTalentSpellCost", &GetTalentSpellCost);
}