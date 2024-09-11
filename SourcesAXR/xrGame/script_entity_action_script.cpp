////////////////////////////////////////////////////////////////////////////
//	Module 		: script_entity_action.h
//	Created 	: 30.09.2003
//  Modified 	: 29.06.2004
//	Author		: Dmitriy Iassenev
//	Description : Script entity action class
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "script_entity_action.h"

using namespace luabind;

#pragma optimize("s",on)
void CScriptEntityAction::script_register(lua_State *L)
{
	module(L)
	[
		class_<CScriptEntityAction>("entity_action")
			.def(								constructor<>())
			.def(								constructor<const CScriptEntityAction *>())
			.def("set_action",					static_cast<void (CScriptEntityAction::*)(CScriptMovementAction&)>(&CScriptEntityAction::SetAction))
			.def("set_action",					static_cast<void (CScriptEntityAction::*)(CScriptWatchAction&)>(&CScriptEntityAction::SetAction))
			.def("set_action",					static_cast<void (CScriptEntityAction::*)(CScriptAnimationAction&)>(&CScriptEntityAction::SetAction))
			.def("set_action",					static_cast<void (CScriptEntityAction::*)(CScriptSoundAction&)>(&CScriptEntityAction::SetAction))
			.def("set_action",					static_cast<void (CScriptEntityAction::*)(CScriptParticleAction&)>(&CScriptEntityAction::SetAction))
			.def("set_action",					static_cast<void (CScriptEntityAction::*)(CScriptObjectAction&)>(&CScriptEntityAction::SetAction))
			.def("set_action",					static_cast<void (CScriptEntityAction::*)(CScriptActionCondition&)>(&CScriptEntityAction::SetAction))
			.def("set_action",					static_cast<void (CScriptEntityAction::*)(CScriptMonsterAction&)>(&CScriptEntityAction::SetAction))
			.def("move",						&CScriptEntityAction::CheckIfMovementCompleted)
			.def("look",						&CScriptEntityAction::CheckIfWatchCompleted)
			.def("anim",						&CScriptEntityAction::CheckIfAnimationCompleted)
			.def("sound",						&CScriptEntityAction::CheckIfSoundCompleted)
			.def("particle",					&CScriptEntityAction::CheckIfParticleCompleted)
			.def("object",						&CScriptEntityAction::CheckIfObjectCompleted)
			.def("time",						&CScriptEntityAction::CheckIfTimeOver)
			.def("all",							static_cast<bool (CScriptEntityAction::*)()>(&CScriptEntityAction::CheckIfActionCompleted))
			.def("completed",					static_cast<bool (CScriptEntityAction::*)()>(&CScriptEntityAction::CheckIfActionCompleted))
	];
}

SCRIPT_EXPORT(CScriptEntityAction);
