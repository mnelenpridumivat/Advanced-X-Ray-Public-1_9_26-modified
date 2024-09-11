#include "stdafx.h"
#include "AlifePlayerData.h"

#include "ai_space.h"
#include "script_engine.h"
#include <luabind/luabind.hpp>
#include <luabind/functor.hpp>
#include "script_read_write.h"
#include <CustomTimer.h>

void CAlifePlayerData::save()
{
    auto writer = CMemoryWriter();
    CTimerManager::GetInstance().save(writer);
    CBinderManager::GetInstance().save(writer);
    luabind::functor<void> funct;
    if (ai().script_engine().functor("mod_scripts.data_save", funct)) {
        funct(CWriterScriptWrapper(&writer));
    }
    writer.CopyTo(data);
}

void CAlifePlayerData::load()
{
    auto reader = IReader(&*data.begin(), data.size());
    CTimerManager::GetInstance().load(reader);
    CBinderManager::GetInstance().load(reader);
    luabind::functor<void> funct;
    if (ai().script_engine().functor("mod_scripts.data_load", funct)) {
        funct(CReaderScriptWrapper(&reader));
    }
}

void CAlifePlayerData::read(IReader& reader)
{
    data.resize(reader.r_u32());
    reader.r(&*data.begin(), data.size());
}

void CAlifePlayerData::write(IWriter& writer)
{
    writer.w_u32(data.size());
    writer.w(&*data.begin(), data.size());
}
