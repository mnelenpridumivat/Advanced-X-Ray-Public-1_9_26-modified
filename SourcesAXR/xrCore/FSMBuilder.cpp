#include "stdafx.h"
#include "FSMBuilder.h"

#include "FSM.h"
#include "FSMController.h"
#include "FSMState.h"
#include "FSMTransition.h"

void FSM::Builder::Reset()
{
	if(instance)
	{
		instance.reset();
	}
	instance = nullptr;
}

FSM::State* FSM::Builder::AddState(State* NewState) const
{
	instance->States.emplace_back(NewState);
	return NewState;
}

FSM::Transition* FSM::Builder::AddTransition(State* From, State* To, fastdelegate::FastDelegate<bool()> Condition)
{
	instance->Transitions.emplace_back(xr_new<Transition>());
	auto pushed = instance->Transitions.back();
	pushed->Condition = Condition;
	pushed->NextState = To;
	From->OutputTransitions.push_back(pushed);
	return pushed;
}

void FSM::Builder::SetStartState(State* State)
{
	instance->CurrentState = State;
}

std::weak_ptr<FSM::FSM> FSM::Builder::CreateInstance()
{
	instance = xr_make_shared<FSM>();
	Controller::GetInstance()->AddFSM(instance);
	return instance;
}
