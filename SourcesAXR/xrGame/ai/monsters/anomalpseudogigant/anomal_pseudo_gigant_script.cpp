#include "stdafx.h"
#include "pch_script.h"
#include "anomal_pseudo_gigant.h"

using namespace luabind;

#pragma optimize("s",on)
void CAnomalPseudoGigant::script_register(lua_State *L)
{
	module(L)
	[
		class_<CAnomalPseudoGigant,CGameObject>("CAnomalPseudoGigant")
			.def(constructor<>())
	];
}
