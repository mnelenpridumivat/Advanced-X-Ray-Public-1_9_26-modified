////////////////////////////////////////////////////////////////////////////
//	Module 		: script_sound_action_script.cpp
//	Created 	: 30.09.2003
//  Modified 	: 29.06.2004
//	Author		: Dmitriy Iassenev
//	Description : Script sound action class script export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "script_sound_action.h"

using namespace luabind;

#pragma optimize("s",on)
void CScriptSoundAction::script_register(lua_State *L)
{
	module(L)
	[
		class_<CScriptSoundAction>("sound")
			.enum_("type")
			[
				value("idle",					static_cast<int>(MonsterSound::eMonsterSoundIdle)),
				value("eat",					static_cast<int>(MonsterSound::eMonsterSoundEat)),
				value("attack",					static_cast<int>(MonsterSound::eMonsterSoundAggressive)),
				value("attack_hit",				static_cast<int>(MonsterSound::eMonsterSoundAttackHit)),
				value("take_damage",			static_cast<int>(MonsterSound::eMonsterSoundTakeDamage)),
				value("die",					static_cast<int>(MonsterSound::eMonsterSoundDie)),
				value("threaten",				static_cast<int>(MonsterSound::eMonsterSoundThreaten)),
				value("steal",					static_cast<int>(MonsterSound::eMonsterSoundSteal)),
				value("panic",					static_cast<int>(MonsterSound::eMonsterSoundPanic))
			]

			.def(								constructor<>())
			.def(								constructor<LPCSTR,LPCSTR>())
			.def(								constructor<LPCSTR,LPCSTR,const Fvector &>())
			.def(								constructor<LPCSTR,LPCSTR,const Fvector &,const Fvector &>())
			.def(								constructor<LPCSTR,LPCSTR,const Fvector &,const Fvector &,bool>())
			.def(								constructor<LPCSTR,Fvector *>())
			.def(								constructor<LPCSTR,Fvector *,const Fvector &>())
			.def(								constructor<LPCSTR,Fvector *,const Fvector &,bool>())
			.def(								constructor<CScriptSound*,LPCSTR,const Fvector &>())
			.def(								constructor<CScriptSound*,LPCSTR,const Fvector &,const Fvector &>())
			.def(								constructor<CScriptSound*,LPCSTR,const Fvector &,const Fvector &,bool>())
			.def(								constructor<CScriptSound*,Fvector *>())
			.def(								constructor<CScriptSound*,Fvector *,const Fvector &>())
			.def(								constructor<CScriptSound*,Fvector *,const Fvector &,bool>())
			// monster specific
			.def(								constructor<MonsterSound::EType>())
			.def(								constructor<MonsterSound::EType,int>())
			// trader specific
			.def(								constructor<LPCSTR,LPCSTR,MonsterSpace::EMonsterHeadAnimType>())

			.def("set_sound",					static_cast<void (CScriptSoundAction::*)(LPCSTR)>(&CScriptSoundAction::SetSound))
			.def("set_sound",					static_cast<void (CScriptSoundAction::*)(const CScriptSound&)>(&CScriptSoundAction::SetSound))
			.def("set_sound_type",				&CScriptSoundAction::SetSoundType)
			.def("set_bone",					&CScriptSoundAction::SetBone)
			.def("set_position",				&CScriptSoundAction::SetPosition)
			.def("set_angles",					&CScriptSoundAction::SetAngles)
			.def("completed",					static_cast<bool (CScriptSoundAction::*)()>(&CScriptSoundAction::completed))
	];
}
