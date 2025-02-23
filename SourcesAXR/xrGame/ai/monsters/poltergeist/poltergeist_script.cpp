#include "pch_script.h"
#include "poltergeist.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CPoltergeist::script_register(lua_State *L)
{
	module(L)
	[
		class_<CPoltergeist,CGameObject>("CPoltergeist")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CPoltergeist, CObjectScript);
