////////////////////////////////////////////////////////////////////////////
//	Module 		: script_animation_action_script.cpp
//	Created 	: 30.09.2003
//  Modified 	: 29.06.2004
//	Author		: Dmitriy Iassenev
//	Description : Script animation action class script export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "script_animation_action.h"

using namespace luabind;

#pragma optimize("s",on)
void CScriptAnimationAction::script_register(lua_State *L)
{
	module(L)
	[
		class_<CScriptAnimationAction>("anim")
			.enum_("type")
			[
				value("free",					static_cast<int>(MonsterSpace::eMentalStateFree)),
				value("danger",					static_cast<int>(MonsterSpace::eMentalStateDanger)),
				value("panic",					static_cast<int>(MonsterSpace::eMentalStatePanic))
			]
			.enum_("monster")
			[
				value("stand_idle",				static_cast<int>(MonsterSpace::eAA_StandIdle)),
				value("capture_prepare",		static_cast<int>(MonsterSpace::eAA_CapturePrepare)),
				value("sit_idle",				static_cast<int>(MonsterSpace::eAA_SitIdle)),
				value("lie_idle",				static_cast<int>(MonsterSpace::eAA_LieIdle)),
				value("eat",					static_cast<int>(MonsterSpace::eAA_Eat)),
				value("sleep",					static_cast<int>(MonsterSpace::eAA_Sleep)),
				value("rest",					static_cast<int>(MonsterSpace::eAA_Rest)),
				value("attack",					static_cast<int>(MonsterSpace::eAA_Attack)),
				value("look_around",			static_cast<int>(MonsterSpace::eAA_LookAround)),
				value("turn",					static_cast<int>(MonsterSpace::eAA_Turn))
			]

			.def(								constructor<>())
			.def(								constructor<LPCSTR>())
			.def(								constructor<LPCSTR,bool>())
			.def(								constructor<MonsterSpace::EMentalState>())
			
			// Monster specific
			.def(								constructor<MonsterSpace::EScriptMonsterAnimAction, int>())
			
			.def("anim",						&CScriptAnimationAction::SetAnimation)
			.def("type",						&CScriptAnimationAction::SetMentalState)
			.def("completed",					static_cast<bool (CScriptAnimationAction::*)()>(&CScriptAnimationAction::completed))
	];
}