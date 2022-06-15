#include "ScriptMgr.h"
#include "Player.h"

class at_booty_bay_to_gnomeregan : public AreaTriggerScript
{
    public:
        at_booty_bay_to_gnomeregan() : AreaTriggerScript("at_booty_bay_to_gnomeregan") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/) override
        {
            if (! player)
                return true;

            /** Alliance Can't Use. */
            if (player->GetTeam() != HORDE && !player->IsGameMaster())
                return true;

            /** Has Item. */
            if (! player->HasItemCount(9173, 1, false))
                return true;

            /** Success, allow teleport. */
            return false;
        };
};

void AddSC_stranglethorn()
{
    new at_booty_bay_to_gnomeregan();
}
