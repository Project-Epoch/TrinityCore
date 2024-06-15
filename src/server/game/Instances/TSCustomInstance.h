#ifndef TSCUSTOMINSTANCE_H
#define TSCUSTOMINSTANCE_H

#include "TSMutable.h"
#include "Map.h"
#include "InstanceScript.h"

#define DataHeader "TS"

class TC_GAME_API TSCustomInstance : public InstanceScript {
public:
    TSCustomInstance(InstanceMap* map);

    void WriteSaveDataMore(std::ostringstream& /*data*/) override;
    void ReadSaveDataMore(std::istringstream& /*data*/) override;
    void SetData(uint32 /*type*/, uint32 /*data*/) override;
    uint32 GetData(uint32 /*type*/) const override;
};

#endif