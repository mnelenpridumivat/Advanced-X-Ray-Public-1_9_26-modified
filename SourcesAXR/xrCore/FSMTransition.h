#pragma once
#include "fastdelegate.h"


namespace FSM {
	class Builder;
	class State;

	class XRCORE_API Transition
	{
		friend Builder;
		fastdelegate::FastDelegate<bool()> Condition;
		State* NextState = nullptr;
	public:
		bool VerifyCondition();
		IC State* GetNextState() { return NextState; };
	};
}
