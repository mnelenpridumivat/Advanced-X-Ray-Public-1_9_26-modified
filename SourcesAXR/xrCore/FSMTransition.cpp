#include "stdafx.h"
#include "FSMTransition.h"

bool FSM::Transition::VerifyCondition()
{
	return Condition();
}
