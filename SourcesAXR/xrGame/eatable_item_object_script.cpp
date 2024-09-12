
#include "StdAfx.h"

#include "pch_script.h"

#include "Battery.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CEatableItemObject::script_register(lua_State* L)
{
	module(L)
		[
			class_<CEatableItemObject, CGameObject>("CEatableItemObject")
			.def(constructor<>())
		];
}

SCRIPT_EXPORT2(CEatableItemObject, CObjectScript);