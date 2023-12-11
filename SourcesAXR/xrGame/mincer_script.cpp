#include "pch_script.h"

#include "EmiZone.h"
#include "MagnetZone.h"
#include "mincer.h"
#include "RadioactiveZone.h"

using namespace luabind;

#pragma optimize("s",on)
void CMincer::script_register	(lua_State *L)
{
	module(L)
	[
		class_<CMincer,CGameObject>("CMincer")
			.def(constructor<>()),
		class_<CRadioactiveZone,CGameObject>("CRadioactiveZone")
			.def(constructor<>()),
		class_<CMagnetZone, CGameObject>("CMagnetZone")
			.def(constructor<>()),
		class_<CEmiZone, CGameObject>("CEmiZone")
			.def(constructor<>())
	];
}
