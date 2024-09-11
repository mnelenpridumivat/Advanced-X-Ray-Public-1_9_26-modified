#include "pch_script.h"

#include "PHSimpleCalls.h"
#include "../xrphysics/PhysicsShell.h"


using namespace luabind;


#pragma optimize("s",on)
void CPHCallOnStepCondition::script_register(lua_State *L)
{
	module(L)
		[
			class_<CPHCallOnStepCondition>("phcondition_callonstep")
			.def("set_step",				&CPHCallOnStepCondition::set_step)
			.def("set_steps_interval",		&CPHCallOnStepCondition::set_steps_interval)
			.def("set_global_time_ms",		static_cast<void(CPHCallOnStepCondition::*)(u32)>(&CPHCallOnStepCondition::set_global_time))
			.def("set_global_time_s",		static_cast<void(CPHCallOnStepCondition::*)(float)>(&CPHCallOnStepCondition::set_global_time))
			.def("set_time_interval_ms",	static_cast<void(CPHCallOnStepCondition::*)(u32)>(&CPHCallOnStepCondition::set_time_interval))
			.def("set_time_interval_s",		static_cast<void(CPHCallOnStepCondition::*)(float)>(&CPHCallOnStepCondition::set_time_interval))
			.def(constructor<>())
		];
}

SCRIPT_EXPORT(CPHCallOnStepCondition);

void CPHExpireOnStepCondition::script_register(lua_State *L)
{
	module(L)
		[
			class_<CPHExpireOnStepCondition,CPHCallOnStepCondition>("phcondition_expireonstep")
			.def(constructor<>())
		];
}

SCRIPT_EXPORT(CPHExpireOnStepCondition);

void CPHConstForceAction::script_register(lua_State *L)
{
	module(L)
		[
			class_<CPHConstForceAction>("phaction_constforce")
			.def(constructor<CPhysicsShell*,const Fvector&>())
		];
}

SCRIPT_EXPORT(CPHConstForceAction);

//(CPhysicsJoint*(CPhysicsShell::*)(u16))(&CPhysicsShell::get_Joint))
//.def("set_gravity",					&CPHWorld::SetGravity),
//.def("add_call",					&CPHWorld::AddCall)