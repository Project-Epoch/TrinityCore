#include "TSCustomInstance.h"

/**
 * Real loading in respective function
*/
TSCustomInstance::TSCustomInstance(InstanceMap* map) : InstanceScript(map) {
    SetBossNumber(0);
    LoadBossBoundaries({});
    LoadDoorData(nullptr);
}