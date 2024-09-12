#include "pch_script.h"
#include "dog.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CAI_Dog::script_register(lua_State *L)
{
	module(L)
	[
		class_<CAI_Dog,CGameObject>("CAI_Dog")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CAI_Dog, CObjectScript);
