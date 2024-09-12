////////////////////////////////////////////////////////////////////////////
//	Module 		: script_object_action_script.cpp
//	Created 	: 30.09.2003
//  Modified 	: 29.06.2004
//	Author		: Dmitriy Iassenev
//	Description : Script object action class script export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "script_object_action.h"
#include "script_game_object.h"

using namespace luabind;

#pragma optimize("s",on)
void CScriptObjectAction::script_register(lua_State *L)
{
	module(L)
	[
		class_<CScriptObjectAction>("object")
			.enum_("state")
			[
				value("idle",					static_cast<int>(MonsterSpace::eObjectActionIdle)),
				value("show",					static_cast<int>(MonsterSpace::eObjectActionShow)),		
				value("hide",					static_cast<int>(MonsterSpace::eObjectActionHide)),		
				value("take",					static_cast<int>(MonsterSpace::eObjectActionTake)),		
				value("drop",					static_cast<int>(MonsterSpace::eObjectActionDrop)),		
				value("strap",					static_cast<int>(MonsterSpace::eObjectActionStrapped)),		
				value("aim1",					static_cast<int>(MonsterSpace::eObjectActionAim1)),		
				value("aim2",					static_cast<int>(MonsterSpace::eObjectActionAim2)),		
				value("reload",					static_cast<int>(MonsterSpace::eObjectActionReload1)),	
				value("reload1",				static_cast<int>(MonsterSpace::eObjectActionReload1)),	
				value("reload2",				static_cast<int>(MonsterSpace::eObjectActionReload2)),	
				value("fire1",					static_cast<int>(MonsterSpace::eObjectActionFire1)),		
				value("fire2",					static_cast<int>(MonsterSpace::eObjectActionFire2)),		
				value("switch1",				static_cast<int>(MonsterSpace::eObjectActionSwitch1)),	
				value("switch2",				static_cast<int>(MonsterSpace::eObjectActionSwitch2)),	
				value("activate",				static_cast<int>(MonsterSpace::eObjectActionActivate)),
				value("deactivate",				static_cast<int>(MonsterSpace::eObjectActionDeactivate)),
				value("use",					static_cast<int>(MonsterSpace::eObjectActionUse)),
				value("turn_on",				static_cast<int>(MonsterSpace::eObjectActionTurnOn)),
				value("turn_off",				static_cast<int>(MonsterSpace::eObjectActionTurnOff)),
				value("dummy",					static_cast<int>(MonsterSpace::eObjectActionDummy))
			]
			.def(								constructor<>())
			.def(								constructor<CScriptGameObject*,MonsterSpace::EObjectAction>())
			.def(								constructor<CScriptGameObject*,MonsterSpace::EObjectAction,u32>())
			.def(								constructor<MonsterSpace::EObjectAction>())
			.def(								constructor<LPCSTR,MonsterSpace::EObjectAction>())
			.def("action",						&CScriptObjectAction::SetObjectAction)
			.def("object",						static_cast<void (CScriptObjectAction::*)(LPCSTR)>(&CScriptObjectAction::SetObject))
			.def("object",						static_cast<void (CScriptObjectAction::*)(CScriptGameObject*)>(&CScriptObjectAction::SetObject))
			.def("completed",					static_cast<bool (CScriptObjectAction::*)()>(&CScriptObjectAction::completed))
	];
}

SCRIPT_EXPORT1(CScriptObjectAction);
