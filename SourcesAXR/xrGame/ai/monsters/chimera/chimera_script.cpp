#include "pch_script.h"
#include "chimera.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CChimera::script_register(lua_State *L)
{
	module(L)
	[
		class_<CChimera,CGameObject>("CChimera")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CChimera, CObjectScript);
