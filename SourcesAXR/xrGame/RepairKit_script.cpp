
#include "StdAfx.h"

#include "pch_script.h"

#include "RepairKit.h"

using namespace luabind;

#pragma optimize("s",on)
void CRepairKit::script_register(lua_State* L)
{
	module(L)
		[
			class_<CRepairKit, CEatableItemObject>("CRepairKit")
				.def(constructor<>())
		];
}
