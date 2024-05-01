#pragma once
#include "../xrCore/FSMBuilder.h"
#include "../xrCore/FSMState.h"

namespace FSM
{
	namespace Flamethrower
	{
		class State_Idle: public State
		{
			virtual void Reset() override{};
			virtual void Update(float DeltaTime) override {};
		};

		class State_ActiveAir : public State
		{
			virtual void Reset() override {};
			virtual void Update(float DeltaTime) override {};
		};

		class State_Transition_AirGround : public State
		{
			virtual void Reset() override {};
			virtual void Update(float DeltaTime) override {};
		};

		class State_ActiveGround : public State
		{
			virtual void Reset() override {};
			virtual void Update(float DeltaTime) override {};
		};

		class State_FinishingAir : public State
		{
			virtual void Reset() override {};
			virtual void Update(float DeltaTime) override {};
		};

		class State_FinishingGround : public State
		{
			virtual void Reset() override {};
			virtual void Update(float DeltaTime) override {};
		};

		class Builder_FlamethrowerTrace : public Builder
		{
		public:
			virtual std::weak_ptr<FSM> CreateInstance() override;
		};
	}
}
