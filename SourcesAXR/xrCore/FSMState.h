#pragma once
#include "xr_smart_pointers.h"
#include "_stl_extensions.h"
#include "StructDefines.h"

namespace FSM {
	class Transition;
	class Builder;

	class XRCORE_API State
	{
		friend Builder;

		DEFINE_VECTOR(Transition*, TransVec, TransVecIt);

		TransVec OutputTransitions;

	public:
		virtual void Reset() = 0;
		virtual void Update(float DeltaTime) = 0;
		void TryToTransit(State*& CurrentState);
	};
}
