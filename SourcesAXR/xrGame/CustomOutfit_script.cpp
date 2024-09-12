#include "stdafx.h"
#include "CustomOutfit.h"
#include "ActorHelmet.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CCustomOutfit::script_register(lua_State* L)
{
    module(L)
    [
        class_<CCustomOutfit, CGameObject>("CCustomOutfit")
            .def(constructor<>())
    ];
};

SCRIPT_EXPORT2(CCustomOutfit, CObjectScript);