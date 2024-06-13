#include "pch_script.h"
#include "helicopter.h"
#include "script_game_object.h"

int CHelicopter::GetMovementState()
{
	return m_movement.type;
}

int CHelicopter::GetHuntState()
{
	return m_enemy.type;
}

int CHelicopter::GetBodyState()
{
	return	m_body.type;
}

using namespace luabind;

#pragma optimize("s",on)
void CHelicopter::script_register(lua_State *L)
{
	module(L)
	[
		class_<CHelicopter, CGameObject>("CHelicopter")
			.def(constructor<>())
			.enum_("state")
			[
				value("eAlive", static_cast<int>(CHelicopter::eAlive)),
					value("eDead", static_cast<int>(CHelicopter::eDead))
			]
			.enum_("movement_state")
			[
				value("eMovNone", static_cast<int>(eMovNone)),
					value("eMovToPoint", static_cast<int>(eMovToPoint)),
					value("eMovPatrolPath", static_cast<int>(eMovPatrolPath)),
					value("eMovRoundPath", static_cast<int>(eMovRoundPath)),
					value("eMovLanding", static_cast<int>(eMovLanding)),
					value("eMovTakeOff", static_cast<int>(eMovTakeOff))
			]
			.enum_("hunt_state")
			[
				value("eEnemyNone", static_cast<int>(eEnemyNone)),
					value("eEnemyPoint", static_cast<int>(eEnemyPoint)),
					value("eEnemyEntity", static_cast<int>(eEnemyEntity))
			]
			.enum_("body_state")
			[
				value("eBodyByPath", static_cast<int>(eBodyByPath)),
					value("eBodyToPoint", static_cast<int>(eBodyToPoint))
			]

			.def("GetState", &CHelicopter::state_script)
			.def("GetMovementState", &CHelicopter::GetMovementState)
			.def("GetHuntState", &CHelicopter::GetHuntState)
			.def("GetBodyState", &CHelicopter::GetBodyState)

			.def("GetCurrVelocity", &CHelicopter::GetCurrVelocity)
			.def("GetMaxVelocity", &CHelicopter::GetMaxVelocity)
			.def("SetMaxVelocity", &CHelicopter::SetMaxVelocity)
			.def("GetCurrVelocityVec", &CHelicopter::GetCurrVelocityVec)
			.def("GetfHealth", &CHelicopter::GetHeliHealth)
			.def("SetfHealth", &CHelicopter::SetHeliHealth)

			.def("SetSpeedInDestPoint", &CHelicopter::SetSpeedInDestPoint)
			.def("GetSpeedInDestPoint", &CHelicopter::GetSpeedInDestPoint)
			//////////////////////Start By JoHnY///////////////////////
			.def("SetLinearAcc", &CHelicopter::SetLinearAcc)
			//////////////////////End By JoHnY/////////////////////////

			.def("SetOnPointRangeDist", &CHelicopter::SetOnPointRangeDist)
			.def("GetOnPointRangeDist", &CHelicopter::GetOnPointRangeDist)

			.def("GetDistanceToDestPosition", &CHelicopter::GetDistanceToDestPosition)

			.def("ClearEnemy", &CHelicopter::UnSetEnemy)
			.def("SetEnemy", static_cast<void (CHelicopter::*)(CScriptGameObject*)>(&CHelicopter::SetEnemy))
			.def("SetEnemy", static_cast<void (CHelicopter::*)(Fvector*)>(&CHelicopter::SetEnemy))
			.def("GoPatrolByPatrolPath", &CHelicopter::goPatrolByPatrolPath)
			.def("GoPatrolByRoundPath", &CHelicopter::goByRoundPath)
			.def("SetDestPosition", &CHelicopter::SetDestPosition)
			.def("LookAtPoint", &CHelicopter::LookAtPoint)
			.def("SetFireTrailLength", &CHelicopter::SetFireTrailLength)
			.def("SetBarrelDirTolerance", &CHelicopter::SetBarrelDirTolerance)

			.def("UseFireTrail", static_cast<bool (CHelicopter::*)(void)>(&CHelicopter::UseFireTrail))
			.def("UseFireTrail", static_cast<void (CHelicopter::*)(bool)>(&CHelicopter::UseFireTrail))

			.def("Die", &CHelicopter::DieHelicopter)
			.def("StartFlame", &CHelicopter::StartFlame)
			.def("Explode", &CHelicopter::ExplodeHelicopter)

			.def("isVisible", &CHelicopter::isVisible)

			.def("GetRealAltitude", &CHelicopter::GetRealAltitude)
			.def("GetSafeAltitude", &CHelicopter::GetSafeAltitude)
			.def("TurnLighting", &CHelicopter::TurnLighting)
			.def("TurnEngineSound", &CHelicopter::TurnEngineSound)
			.def("DropFlares", &CHelicopter::DropFlares)
			.def_readwrite("m_use_rocket_on_attack",	&CHelicopter::m_use_rocket_on_attack)
			.def_readwrite("m_use_mgun_on_attack",		&CHelicopter::m_use_mgun_on_attack)
			.def_readwrite("m_min_rocket_dist",			&CHelicopter::m_min_rocket_dist)
			.def_readwrite("m_max_rocket_dist",			&CHelicopter::m_max_rocket_dist)
			.def_readwrite("m_min_mgun_dist",			&CHelicopter::m_min_mgun_dist)
			.def_readwrite("m_max_mgun_dist",			&CHelicopter::m_max_mgun_dist)
			.def_readwrite("m_time_between_rocket_attack", &CHelicopter::m_time_between_rocket_attack)
			.def_readwrite("m_syncronize_rocket",		&CHelicopter::m_syncronize_rocket)
			.def_readonly ("m_flame_started",			&CHelicopter::m_flame_started)
			.def_readonly ("m_light_started",			&CHelicopter::m_light_started)
			.def_readonly ("m_exploded",				&CHelicopter::m_exploded)
			.def_readonly ("m_dead",					&CHelicopter::m_dead)

//			.def_readwrite("", &CHelicopter::)

		];
}