////////////////////////////////////////////////////////////////////////////
//	Module 		: script_action_condition_script.cpp
//	Created 	: 30.09.2003
//  Modified 	: 29.06.2004
//	Author		: Dmitriy Iassenev
//	Description : Script action condition class script export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "script_action_condition.h"

using namespace luabind;

#pragma optimize("s",on)
void CScriptActionCondition::script_register(lua_State *L)
{
	module(L)
	[
		class_<CScriptActionCondition>("cond")
			.enum_("cond")
			[
				value("move_end",	static_cast<int>(CScriptActionCondition::MOVEMENT_FLAG)),
				value("look_end",	static_cast<int>(CScriptActionCondition::WATCH_FLAG)),
				value("anim_end",	static_cast<int>(CScriptActionCondition::ANIMATION_FLAG)),
				value("sound_end",	static_cast<int>(CScriptActionCondition::SOUND_FLAG)),
				value("object_end",	static_cast<int>(CScriptActionCondition::OBJECT_FLAG)),
				value("time_end",	static_cast<int>(CScriptActionCondition::TIME_FLAG)),
				value("act_end",	static_cast<int>(CScriptActionCondition::ACT_FLAG))
			]
			.def(					constructor<>())
			.def(					constructor<u32>())
			.def(					constructor<u32,double>())
	];
}

SCRIPT_EXPORT1(CScriptActionCondition);
