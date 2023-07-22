
#include "StdAfx.h"

#include "pch_script.h"

#include "Battery.h"

using namespace luabind;

#pragma optimize("s",on)
void CBattery::script_register(lua_State* L)
{
	module(L)
		[
			class_<CBattery, CEatableItemObject>("CBattery")
				.def(constructor<>())
		];
}