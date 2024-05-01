#include "StdAfx.h"
#include "FlamethrowerTraceCollisionFSM.h"

std::weak_ptr<FSM::FSM> FSM::Flamethrower::Builder_FlamethrowerTrace::CreateInstance()
{
	Reset();
	auto instance = Builder::CreateInstance();
	auto inst_ptr = instance.lock().get();
	auto i_State_Idle = AddState(xr_new<State_Idle>());
	auto i_ActiveAir = AddState(xr_new <State_ActiveAir>());
	auto i_Transition_AirGround = AddState(xr_new <State_Transition_AirGround>());
	auto i_ActiveGround = AddState(xr_new <State_ActiveGround>());
	auto i_FinishingAir = AddState(xr_new <State_FinishingAir>());
	auto i_FinishingGround = AddState(xr_new <State_FinishingGround>());
	return instance;
}
