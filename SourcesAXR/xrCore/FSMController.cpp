#include "stdafx.h"
#include "FSMController.h"

#include "FSM.h"

FSM::Controller* FSM::Controller::pinstance_{ nullptr };
std::mutex FSM::Controller::mutex_;

void FSM::Controller::AddFSM(const xr_shared_ptr<FSM>& SM)
{
	InactiveFSM.emplace(SM);
}

FSM::Controller* FSM::Controller::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);
	if(!pinstance_)
	{
		pinstance_ = xr_new<Controller>();
	}
	return pinstance_;
}

void FSM::Controller::ActivateFSM(const std::weak_ptr<FSM>& SM)
{
	if(IsActive(SM))
	{
		return;
	}
	ActiveFSM.emplace(SM.lock());
	InactiveFSM.erase(SM.lock());
}

void FSM::Controller::DeactivateFSM(const std::weak_ptr<FSM>& SM)
{
	if (SM.expired())
	{
		return;
	}
	if (!IsActive(SM)) {
		InactiveFSM.emplace(SM.lock());
		ActiveFSM.erase(SM.lock());
	}
}

void FSM::Controller::UpdateFSM(float DeltaTime) const
{
	for(auto& elem : ActiveFSM)
	{
		elem->Update(DeltaTime);
	}
}

bool FSM::Controller::IsActive(const std::weak_ptr<FSM>& SM)
{
	if(SM.expired())
	{
		return false;
	}
	return ActiveFSM.find(SM.lock()) != ActiveFSM.end();
}

void FSM::Controller::RemoveFSM(const std::weak_ptr<FSM>& SM)
{
	if(SM.expired())
	{
		return;
	}
	InactiveFSM.erase(SM.lock());
	ActiveFSM.erase(SM.lock());
}
