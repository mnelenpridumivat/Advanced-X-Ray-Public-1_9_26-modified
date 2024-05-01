#pragma once
#include "xr_smart_pointers.h"
#include "_stl_extensions.h"

namespace FSM {
	class Builder;
	class Memory;
	class State;
	class Transition;

	class XRCORE_API FSM: public std::enable_shared_from_this<FSM>
	{
		friend Builder;

	public:

		~FSM();

		//using StatesVec = std::vector<xr_unique_ptr<State>>;
		//using TransVec = std::vector<xr_unique_ptr<Transition>>;

		DEFINE_VECTOR(State*, StatesVec, StatesVecIt);
		DEFINE_VECTOR(Transition*, TransVec, TransVecIt);

		void Start();
		void Reset();
		void Update(float DeltaTime);
		void Stop();

	protected:

	private:

		bool IsActive = false;
		StatesVec States;
		TransVec Transitions;
		State* CurrentState = nullptr;

	};
}
