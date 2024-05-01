#pragma once
#include "fastdelegate.h"
#include "xr_smart_pointers.h"


namespace FSM {
	class Controller;
	class FSM;
	class Transition;
	class State;

	class XRCORE_API Builder
	{
	protected:

		xr_shared_ptr<FSM> instance = nullptr;

		void Reset();
		State* AddState(State* State) const;
		Transition* AddTransition(State* From, State* To, fastdelegate::FastDelegate<bool()> Condition);
		void SetStartState(State* State);

	public:
		virtual std::weak_ptr<FSM> CreateInstance();
	};
}
