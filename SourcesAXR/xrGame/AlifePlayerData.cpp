#include "stdafx.h"
#include "AlifePlayerData.h"

#include "ai_space.h"
#include "script_engine.h"
#include <luabind/luabind.hpp>
#include <luabind/functor.hpp>

void CAlifePlayerData::save()
{
    luabind::functor<void> funct;
    if (ai().script_engine().functor("mod_scripts.data_save", funct)) {
        funct();
    }
}

void CAlifePlayerData::load()
{
    luabind::functor<void> funct;
    if (ai().script_engine().functor("mod_scripts.data_load", funct)) {
        funct();
    }
}

void CAlifePlayerData::read(IReader* reader)
{
    
}

void CAlifePlayerData::write(IWriter* reader)
{

}
