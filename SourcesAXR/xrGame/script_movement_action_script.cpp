////////////////////////////////////////////////////////////////////////////
//	Module 		: script_movement_action_script.cpp
//	Created 	: 30.09.2003
//  Modified 	: 29.06.2004
//	Author		: Dmitriy Iassenev
//	Description : Script movement action class script export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "script_movement_action.h"
#include "script_game_object.h"
#include "patrol_path_manager_space.h"
#include "detail_path_manager_space.h"
#include "ai_monster_space.h"
#include "patrol_path_params.h"
#include "patrol_path.h"

using namespace luabind;

#pragma optimize("s",on)
void CScriptMovementAction::script_register(lua_State *L)
{
	module(L)
	[
		class_<CScriptMovementAction>("move")
			.enum_("body")
			[
				value("crouch",					static_cast<int>(MonsterSpace::eBodyStateCrouch)),
				value("standing",				static_cast<int>(MonsterSpace::eBodyStateStand))
			]
			.enum_("move")
			[
				value("walk",					static_cast<int>(MonsterSpace::eMovementTypeWalk)),
				value("run",					static_cast<int>(MonsterSpace::eMovementTypeRun)),
				value("stand",					static_cast<int>(MonsterSpace::eMovementTypeStand))
			]
			.enum_("path")
			[
				value("line",					static_cast<int>(DetailPathManager::eDetailPathTypeSmooth)),
				value("dodge",					static_cast<int>(DetailPathManager::eDetailPathTypeSmoothDodge)),
				value("criteria",				static_cast<int>(DetailPathManager::eDetailPathTypeSmoothCriteria)),
				value("curve",					static_cast<int>(DetailPathManager::eDetailPathTypeSmooth)),
				value("curve_criteria",			static_cast<int>(DetailPathManager::eDetailPathTypeSmoothCriteria))
			]
			.enum_("input")
			[
				value("none",					static_cast<int>(CScriptMovementAction::eInputKeyNone)),
				value("fwd",					static_cast<int>(CScriptMovementAction::eInputKeyForward)),
				value("back",					static_cast<int>(CScriptMovementAction::eInputKeyBack)),
				value("left",					static_cast<int>(CScriptMovementAction::eInputKeyLeft)),
				value("right",					static_cast<int>(CScriptMovementAction::eInputKeyRight)),
				value("up",						static_cast<int>(CScriptMovementAction::eInputKeyShiftUp)),
				value("down",					static_cast<int>(CScriptMovementAction::eInputKeyShiftDown)),
				value("handbrake",				static_cast<int>(CScriptMovementAction::eInputKeyBreaks)),
				value("on",						static_cast<int>(CScriptMovementAction::eInputKeyEngineOn)),
				value("off",					static_cast<int>(CScriptMovementAction::eInputKeyEngineOff))
			]
			.enum_("monster")
			[

				value("walk_fwd",					static_cast<int>(MonsterSpace::eMA_WalkFwd)),
				value("walk_bkwd",					static_cast<int>(MonsterSpace::eMA_WalkBkwd)),
				value("run_fwd",					static_cast<int>(MonsterSpace::eMA_Run)),
				value("drag",						static_cast<int>(MonsterSpace::eMA_Drag)),
				value("jump",						static_cast<int>(MonsterSpace::eMA_Jump)),
				value("steal",						static_cast<int>(MonsterSpace::eMA_Steal)),
				value("walk_with_leader",			static_cast<int>(MonsterSpace::eMA_WalkWithLeader)),
				value("run_with_leader",			static_cast<int>(MonsterSpace::eMA_RunWithLeader))
			]
			.enum_("monster_speed_param")
			[
				value("default",					static_cast<int>(MonsterSpace::eSP_Default)),
				value("force",						static_cast<int>(MonsterSpace::eSP_ForceSpeed))
			]

			.def(								constructor<>())
			.def(								constructor<const CScriptMovementAction::EInputKeys>())
			.def(								constructor<const CScriptMovementAction::EInputKeys, float>())
			.def(								constructor<MonsterSpace::EBodyState,MonsterSpace::EMovementType,DetailPathManager::EDetailPathType,CScriptGameObject*>())
			.def(								constructor<MonsterSpace::EBodyState,MonsterSpace::EMovementType,DetailPathManager::EDetailPathType,CScriptGameObject*,float>())
			.def(								constructor<MonsterSpace::EBodyState,MonsterSpace::EMovementType,DetailPathManager::EDetailPathType,CPatrolPathParams*>())
			.def(								constructor<MonsterSpace::EBodyState,MonsterSpace::EMovementType,DetailPathManager::EDetailPathType,CPatrolPathParams*,float>())
			.def(								constructor<MonsterSpace::EBodyState,MonsterSpace::EMovementType,DetailPathManager::EDetailPathType,Fvector*>())
			.def(								constructor<MonsterSpace::EBodyState,MonsterSpace::EMovementType,DetailPathManager::EDetailPathType,Fvector*,float>())
			.def(								constructor<Fvector *,float>())
			
			// Monsters 
			.def(								constructor<MonsterSpace::EScriptMonsterMoveAction,Fvector *>())
			.def(								constructor<MonsterSpace::EScriptMonsterMoveAction,CPatrolPathParams *>())
			.def(								constructor<MonsterSpace::EScriptMonsterMoveAction,CScriptGameObject*>())
			.def(								constructor<MonsterSpace::EScriptMonsterMoveAction,Fvector *, float>())
			.def(								constructor<MonsterSpace::EScriptMonsterMoveAction,u32, Fvector *>())
			.def(								constructor<MonsterSpace::EScriptMonsterMoveAction,u32, Fvector *, float>())
			.def(								constructor<MonsterSpace::EScriptMonsterMoveAction,CPatrolPathParams *, float>())
			.def(								constructor<MonsterSpace::EScriptMonsterMoveAction,CScriptGameObject*, float>())
			.def(								constructor<MonsterSpace::EScriptMonsterMoveAction,Fvector*,			float,	MonsterSpace::EScriptMonsterSpeedParam>())
			.def(								constructor<MonsterSpace::EScriptMonsterMoveAction,CPatrolPathParams*,	float,	MonsterSpace::EScriptMonsterSpeedParam>())
			.def(								constructor<MonsterSpace::EScriptMonsterMoveAction,CScriptGameObject*,	float,	MonsterSpace::EScriptMonsterSpeedParam>())

			.def("body",						&CScriptMovementAction::SetBodyState)
			.def("move",						&CScriptMovementAction::SetMovementType)
			.def("path",						&CScriptMovementAction::SetPathType)
			.def("object",						&CScriptMovementAction::SetObjectToGo)
			.def("patrol",						&CScriptMovementAction::SetPatrolPath)
			.def("position",					&CScriptMovementAction::SetPosition)
			.def("input",						&CScriptMovementAction::SetInputKeys)
			.def("completed",					static_cast<bool (CScriptMovementAction::*)()>(&CScriptMovementAction::completed))
	];
}