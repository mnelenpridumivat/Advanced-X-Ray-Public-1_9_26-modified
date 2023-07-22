
#include "StdAfx.h"

#include "pch_script.h"

#include "Battery.h"

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