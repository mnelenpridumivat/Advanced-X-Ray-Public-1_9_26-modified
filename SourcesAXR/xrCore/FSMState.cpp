#include "stdafx.h"
#include "FSMState.h"

#include "FSMTransition.h"

void FSM::State::TryToTransit(FSM::State*& CurrentState)
{
	for(auto& elem : OutputTransitions)
	{
		if(elem->VerifyCondition())
		{
			CurrentState = elem->GetNextState();
		}
	}
}
