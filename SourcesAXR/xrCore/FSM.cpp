#include "stdafx.h"
#include "FSM.h"

#include "FSMController.h"
#include "FSMState.h"

FSM::FSM::~FSM()
{
}

void FSM::FSM::Start()
{
#ifdef DEBUG
	VERIFY3(CurrentState, "FSM has missing start state: ", typeid(this).name());
#else
	VERIFY2(CurrentState, "Some FSM has missing start state!");
#endif
	Controller::GetInstance()->ActivateFSM(shared_from_this());
}

void FSM::FSM::FSM::Reset()
{
	for(auto& elem : States)
	{
		elem->Reset();
	}
}

void FSM::FSM::Update(float DeltaTime)
{
#ifdef DEBUG
	VERIFY3(CurrentState, "Invalid current state in FSM: ", typeid(this).name());
#else
	VERIFY2(CurrentState, "Invalid current state in FSM!");
#endif
	CurrentState->Update(DeltaTime);
	CurrentState->TryToTransit(CurrentState);
}

void FSM::FSM::Stop()
{
	Controller::GetInstance()->DeactivateFSM(shared_from_this());
}
