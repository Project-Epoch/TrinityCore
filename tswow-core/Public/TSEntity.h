/*
 * This file is part of tswow (https://github.com/tswow/).
 * Copyright (C) 2020 tswow <https://github.com/tswow/>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include "TSString.h"
#include "TSJson.h"

#include "sol/sol.hpp"

#include <map>
#include <string>
#include <memory>
#include <cstdint>
#include <functional>
#include <set>
#include <mutex>

#define GetDBObject GetObject

struct TC_GAME_API TSCompiledClass {
    uint32_t modid;
    std::shared_ptr<void> ptr;
    TSCompiledClass(uint32_t modid, std::shared_ptr<void> ptr);
    TSCompiledClass();
};

class TC_GAME_API TSCompiledClasses {
    std::map<std::string, TSCompiledClass> m_map;
public:
    bool HasObject(uint32_t modid, TSString key);
    void clear();

    template <typename T>
    std::shared_ptr<T> SetObject(uint32_t modid, TSString key, std::shared_ptr<T> item)
    {
        m_map[key.std_str()] = TSCompiledClass(modid, std::static_pointer_cast<void>(item));
        return item;
    }

    template <typename T>
    std::shared_ptr<T> GetObject(uint32_t modid, TSString key, std::function<std::shared_ptr<T>()> defaultValue = nullptr)
    {
        auto itr = m_map.find(key);
        if(itr == m_map.end())
        {
            return SetObject(modid,key,defaultValue());
        }
        else
        {
            return std::static_pointer_cast<T>(itr->second.ptr);
        }
    }
};

// The class stored on core entities (Object/Map)
struct ModTable
{
    uint32_t modid;
    sol::table table;
};

class TC_GAME_API TSEntity {
public:
    TSCompiledClasses m_compiledClasses;
    TSJsonObject m_json;
    std::map<std::string, ModTable> m_lua_tables;
    uint8_t m_raw[128];
    TSEntity * operator->(){return this;}
};

// The class extended by TSObject/TSMap
class TSEntityProvider {
    TSEntity * m_entity;
    TSEntity * getData() { return m_entity; }
public:
    TSEntityProvider(TSEntity * entity)
        : m_entity(entity)
    {}

    template <typename T>
    std::shared_ptr<T> SetObject(uint32_t modid, TSString key, std::shared_ptr<T> item)
    {
        return getData()->m_compiledClasses.SetObject(modid, key, item);
    }

    template <typename T>
    std::shared_ptr<T> GetObject(uint32_t modid, TSString key, std::function<std::shared_ptr<T>()> defaultValue = nullptr)
    {
        return getData()->m_compiledClasses.GetObject(modid,key,defaultValue);
    }

    bool HasObject(uint32_t modid, TSString key)
    {
        return getData()->m_compiledClasses.HasObject(modid, key);
    }

    void SetRawUInt8(uint8 index, uint8 value)
    {
        *(uint8_t*)(m_entity->m_raw + index) = value;
    }

    uint8 GetRawUInt8(uint8 index)
    {
        return *(uint8*)(m_entity->m_raw + index);
    }

    void SetRawInt8(uint8 index, int8 value)
    {
        *(int8_t*)(m_entity->m_raw + index) = value;
    }

    uint8 GetRawInt8(uint8 index)
    {
        return *(int8*)(m_entity->m_raw + index);
    }

    void SetRawUInt16(uint8 index, uint16 value)
    {
        *(uint16_t*)(m_entity->m_raw + index) = value;
    }

    uint16 GetRawUInt16(uint8 index)
    {
        return *(uint16*)(m_entity->m_raw + index);
    }

    void SetRawInt16(uint8 index, int16 value)
    {
        *(int16_t*)(m_entity->m_raw + index) = value;
    }

    int16 GetRawInt16(uint8 index)
    {
        return *(int16*)(m_entity->m_raw + index);
    }

    void SetRawUInt32(uint8 index, uint32 value)
    {
        *(uint32_t*)(m_entity->m_raw + index) = value;
    }

    uint32 GetRawUInt32(uint8 index)
    {
        return *(uint32*)(m_entity->m_raw + index);
    }

    void SetRawInt32(uint8 index, int32 value)
    {
        *(int32_t*)(m_entity->m_raw + index) = value;
    }

    int32 GetRawInt32(uint8 index)
    {
        return *(int32*)(m_entity->m_raw + index);
    }

    void SetRawUInt64(uint8 index, uint64 value)
    {
        *(uint64_t*)(m_entity->m_raw + index) = value;
    }

    uint64 GetRawUInt64(uint8 index)
    {
        return *(uint64*)(m_entity->m_raw + index);
    }

    void SetRawInt64(uint8 index, int64 value)
    {
        *(int64_t*)(m_entity->m_raw + index) = value;
    }

    int64 GetRawInt64(uint8 index)
    {
        return *(int64*)(m_entity->m_raw + index);
    }

    void SetRawFloat(uint8 index, float value)
    {
        *(float*)(m_entity->m_raw + index) = value;
    }

    float GetRawFloat(uint8 index)
    {
        return *(float*)(m_entity->m_raw + index);
    }

    void SetRawDouble(uint8 index, double value)
    {
        *(double*)(m_entity->m_raw + index) = value;
    }

    double GetRawDouble(uint8 index)
    {
        return *(double*)(m_entity->m_raw + index);
    }

    void SetNumber(TSString key, double value) { getData()->m_json.SetNumber(key, value); }
    bool HasNumber(TSString key) { return getData()->m_json.HasNumber(key); }
    double GetNumber(TSString key, double def = 0) { return getData()->m_json.GetNumber(key, def); }

    void SetBool(TSString key, bool value) { getData()->m_json.SetBool(key, value); }
    bool HasBool(TSString key) { return getData()->m_json.HasBool(key); }
    bool GetBool(TSString key, bool def = false) { return getData()->m_json.GetBool(key, def); }

    void SetString(TSString key, TSString value) { getData()->m_json.SetString(key, value); }
    bool HasString(TSString key) { return getData()->m_json.HasString(key); }
    TSString GetString(TSString key, TSString def = JSTR("")) { return getData()->m_json.GetString(key, def); }

    void SetJsonObject(TSString key, TSJsonObject value) { getData()->m_json.SetJsonObject(key, value); }
    bool HasJsonObject(TSString key) { return getData()->m_json.HasJsonObject(key); }
    TSJsonObject GetJsonObject(TSString key, TSJsonObject def = TSJsonObject()) { return getData()->m_json.GetJsonObject(key, def); }

    void SetJsonArray(TSString key, TSJsonArray value) { getData()->m_json.SetJsonArray(key, value); }
    bool HasJsonArray(TSString key) { return getData()->m_json.HasJsonArray(key); }
    TSJsonArray GetJsonArray(TSString key, TSJsonArray def = TSJsonArray()) { return getData()->m_json.GetJsonArray(key, def); }

    // backwards compatibility
    void SetUInt(TSString key, uint32_t value) { getData()->m_json.SetNumber(key, value); }
    bool HasUInt(TSString key) { return getData()->m_json.HasNumber(key); }
    uint32_t GetUInt(TSString key, uint32_t def = 0) { return uint32_t(getData()->m_json.GetNumber(key, def)); }

    void SetInt(TSString key, int32_t value) { getData()->m_json.SetNumber(key, value); }
    bool HasInt(TSString key) { return getData()->m_json.HasNumber(key); }
    int32_t GetInt(TSString key, int32_t def = 0) { return int32_t(getData()->m_json.GetNumber(key, def)); }

    void SetFloat(TSString key, float value) { getData()->m_json.SetNumber(key, value); }
    bool HasFloat(TSString key) { return getData()->m_json.HasNumber(key); }
    float GetFloat(TSString key, float def = 0) { return float(getData()->m_json.GetNumber(key, def)); }

    void Remove(TSString key) { getData()->m_json.Remove(key); }

private:
    void LSetNumber(std::string const& key, double value) { getData()->m_json.SetNumber(key, value); }
    bool LHasNumber(std::string const& key) { return getData()->m_json.HasNumber(key); }
    double LGetNumber0(std::string const& key, double def) { return getData()->m_json.GetNumber(key, def); }
    double LGetNumber1(std::string const& key) { return getData()->m_json.GetNumber(key); }

    void LSetBool(std::string const& key, bool value) { getData()->m_json.SetBool(key, value); }
    bool LHasBool(std::string const& key) { return getData()->m_json.HasBool(key); }
    bool LGetBool0(std::string const& key, bool def) { return getData()->m_json.GetBool(key, def); }
    bool LGetBool1(std::string const& key) { return getData()->m_json.GetBool(key); }

    void LSetString(std::string const& key, std::string const& value) { getData()->m_json.SetString(key, value); }
    bool LHasString(std::string const& key) { return getData()->m_json.HasString(key); }
    std::string LGetString0(std::string const& key, std::string const& def) { return getData()->m_json.GetString(key, def); }
    std::string LGetString1(std::string const& key) { return getData()->m_json.GetString(key); }

    void LSetJsonObject(std::string const& key, TSJsonObject value) { getData()->m_json.SetJsonObject(key, value); }
    bool LHasJsonObject(std::string const& key) { return getData()->m_json.HasJsonObject(key); }
    TSJsonObject LGetJsonObject0(std::string const& key, TSJsonObject def) { return getData()->m_json.GetJsonObject(key, def); }
    TSJsonObject LGetJsonObject1(std::string const& key) { return getData()->m_json.GetJsonObject(key); }

    void LSetJsonArray(std::string const& key, TSJsonArray value) { getData()->m_json.SetJsonArray(key, value); }
    bool LHasJsonArray(std::string const& key) { return getData()->m_json.HasJsonArray(key); }
    TSJsonArray LGetJsonArray0(std::string const& key, TSJsonArray def) { return getData()->m_json.GetJsonArray(key, def); }
    TSJsonArray LGetJsonArray1(std::string const& key) { return GetJsonArray(key); }

    // backwards compatibility
    void LSetUInt(std::string const& key, uint32_t value) { getData()->m_json.SetNumber(key, value); }
    bool LHasUInt(std::string const& key) { return getData()->m_json.HasNumber(key); }
    uint32_t LGetUInt0(std::string const& key, uint32_t def) { return uint32_t(getData()->m_json.GetNumber(key, def)); }
    uint32_t LGetUInt1(std::string const& key) { return uint32_t(getData()->m_json.GetNumber(key)); }

    void LSetInt(std::string const& key, int32_t value) { getData()->m_json.SetNumber(key, value); }
    bool LHasInt(std::string const& key) { return getData()->m_json.HasNumber(key); }
    int32_t LGetInt0(std::string const& key, int32_t def) { return int32_t(getData()->m_json.GetNumber(key, def)); }
    int32_t LGetInt1(std::string const& key) { return int32_t(getData()->m_json.GetNumber(key)); }

    void LSetFloat(std::string const& key, float value) { getData()->m_json.SetNumber(key, value); }
    bool LHasFloat(std::string const& key) { return getData()->m_json.HasNumber(key); }
    float LGetFloat0(std::string const& key, float def) { return float(getData()->m_json.GetNumber(key, def)); }
    float LGetFloat1(std::string const& key) { return float(getData()->m_json.GetNumber(key)); }

    void LRemove(std::string const& key) { getData()->m_json.Remove(key); }

    void LRemoveObject(std::string const& key) { getData()->m_lua_tables.erase(key); }
    void LSetObject(uint32_t modid, std::string const& key, sol::table table) { getData()->m_lua_tables[key] = { modid, table }; }
    bool LHasObject(std::string const& key) {
        auto const& classes = getData()->m_lua_tables;
        return classes.find(key) != classes.end();
    }
    sol::table LGetObject(uint32_t modid, std::string const& key, sol::table def)
    {
        auto & classes = getData()->m_lua_tables;
        auto const& itr = classes.find(key);
        if (itr != classes.end())
        {
            return itr->second.table;
        }
        else
        {
            classes[key] = { modid, def };
            return def;
        }
    }

    friend class TSLuaState;
};