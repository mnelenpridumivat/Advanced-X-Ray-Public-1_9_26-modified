#include "pch_script.h"
#include "pseudo_gigant_orig.h"

using namespace luabind;

#pragma optimize("s",on)
void CPseudoGigant_orig::script_register(lua_State *L)
{
	module(L)
	[
		class_<CPseudoGigant_orig,CGameObject>("CPseudoGigant")
			.def(constructor<>())
	];
}
