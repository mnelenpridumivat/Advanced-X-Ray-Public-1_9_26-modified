
#include "StdAfx.h"

#include "pch_script.h"

#include "AntigasFilter.h"

using namespace luabind;

#pragma optimize("s",on)
void CAntigasFilter::script_register(lua_State* L)
{
	module(L)
		[
			class_<CAntigasFilter, CEatableItemObject>("CAntigasFilter")
				.def(constructor<>())
		];
}