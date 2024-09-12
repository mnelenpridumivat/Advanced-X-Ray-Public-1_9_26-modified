#include "pch_script.h"
#include "pseudo_gigant_orig.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CPseudoGigant::script_register(lua_State *L)
{
	module(L)
	[
		class_<CPseudoGigant,CGameObject>("CPseudoGigant")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CPseudoGigant, CObjectScript);
