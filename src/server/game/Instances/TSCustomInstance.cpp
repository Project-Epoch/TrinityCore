#include "TSCustomInstance.h"

TSCustomInstance::TSCustomInstance(InstanceMap* map) : InstanceScript(map) {
    // Real loading in respective functions.
    SetHeaders(DataHeader);
    SetBossNumber(0);
    LoadBossBoundaries({});
    LoadDoorData(nullptr);
}

void TSCustomInstance::WriteSaveDataMore(std::ostringstream& data)
{
    TSArray<uint32> _data;

    FIRE_ID(
          instance->GetEntry()->ID
        , Instance,OnWriteSaveDataMore
        , TSInstance(instance, this)
        , TSMutable<TSArray<uint32>, TSArray<uint32>>(&_data)
    );

    _data.forEach([&data](uint32 v, size_t i, TSArray<uint32>& arr) {
        if (i == 0)
            data << static_cast<uint32>(v);
        else
            data << ' ' << static_cast<uint32>(v);
    });
}

void TSCustomInstance::ReadSaveDataMore(std::istringstream& data)
{
    uint8 length = 0;

    FIRE_ID(
          instance->GetEntry()->ID
        , Instance,OnBeforeReadSaveDataMore
        , TSInstance(instance, this)
        , TSMutable<uint8, uint8>(&length)
    );

    if (length == 0)
        return;

    TSArray<uint32> _data;

    for (uint8 i = 0; i < length; i++) {
        uint32 value;

        data >> value;

        _data.insert(i, value);
    }

    FIRE_ID(
          instance->GetEntry()->ID
        , Instance,OnReadSaveDataMore
        , TSInstance(instance, this)
        , _data
    );
}

uint32 TSCustomInstance::GetData(uint32 type) const
{
    uint32 result = 0;

    FIRE_ID(
          instance->GetEntry()->ID
        , Instance,OnDataGet
        , TSInstance(instance, const_cast<TSCustomInstance*>(this))
        , type
        , TSMutableNumber<uint32>(&result)
    );

    return result;
}

void TSCustomInstance::SetData(uint32 type, uint32 data)
{
    FIRE_ID(
          instance->GetEntry()->ID
        , Instance,OnDataSet
        , TSInstance(instance, this)
        , type
        , data
    );
}