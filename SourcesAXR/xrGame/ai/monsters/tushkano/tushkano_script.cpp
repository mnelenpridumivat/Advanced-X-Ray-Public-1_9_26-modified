#include "pch_script.h"
#include "tushkano.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CTushkano::script_register(lua_State *L)
{
	module(L)
		[
			class_<CTushkano,CGameObject>("CTushkano")
			.def(constructor<>())
		];
}

SCRIPT_EXPORT2(CTushkano, CObjectScript);
