////////////////////////////////////////////////////////////////////////////
//	Module 		: CustomTimer.cpp
//	Created 	: 15.08.2023
//  Modified 	: 15.08.2023
//	Author		: Dance Maniac (M.F.S. Team)
//	Description : Engine custom timer
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomTimer.h"
#include "object_broker.h"
#include "ai_space.h"
#include "alife_simulator.h"
#include "alife_time_manager.h"
#include "../xrEngine/device.h"

#include "script_engine.h"
#include <luabind/luabind.hpp>
#include <luabind/functor.hpp>

CCustomTimerBase::CCustomTimerBase()
{
    m_iTimerStartValue = 0;
    m_iTimerCurValue = 0;
    m_bIsActive = false;
}

CCustomTimerBase::~CCustomTimerBase()
{
    StopCustomTimer();
}

void CCustomTimerBase::StartCustomTimer()
{
    m_bIsActive = true;
    m_iStartTime = ai().alife().time_manager().game_time();

}

void CCustomTimer::StartCustomTimer()
{
    CCustomTimerBase::StartCustomTimer();

#ifdef DEBUG
    Msg("Custom Timer: %s : Started", m_sTimerName);
#endif
}

void CCustomTimerBase::StopCustomTimer()
{
    m_bIsActive = false;
}

void CCustomTimer::StopCustomTimer()
{
    CCustomTimerBase::StopCustomTimer();

#ifdef DEBUG
    Msg("Custom Timer: %s : Stopped (timer value: %d)", m_sTimerName, getCurValue());
#endif
}

void CCustomTimerBase::ResetCustomTimer()
{

    StopCustomTimer();

    m_iTimerCurValue = 0;

    StartCustomTimer();
}

void CCustomTimer::ResetCustomTimer()
{
#ifdef DEBUG
    Msg("Custom Timer: %s : Reset (timer value: %d)", m_sTimerName, getCurValue());
#endif

    CCustomTimerBase::ResetCustomTimer();
}

void CCustomTimerBase::save(NET_Packet& packet)
{
    save_data(m_iTimerStartValue, packet);
    save_data(m_iTimerCurValue, packet);
    save_data(m_iTimerMode, packet);
    save_data(m_iStartTime, packet);
    save_data(m_bIsActive, packet);
}

void CCustomTimer::save(NET_Packet& packet)
{
    save_data(m_sTimerName, packet);
    CCustomTimerBase::save(packet);
}

void CBinder::save(NET_Packet& packet)
{
    CCustomTimerBase::save(packet);
    save_data(m_sFuncName, packet);
    save_data(m_expired, packet);
    save_data(m_params.size(), packet);
    for(auto& elem : m_params)
    {
        save_data(elem, packet);
    }
}

void CCustomTimerBase::load(IReader& packet)
{
    load_data(m_iTimerStartValue, packet);
    load_data(m_iTimerCurValue, packet);
    load_data(m_iTimerMode, packet);
    load_data(m_iStartTime, packet);
    load_data(m_bIsActive, packet);
}

void CCustomTimer::load(IReader& packet)
{
    load_data(m_sTimerName, packet);
    CCustomTimerBase::load(packet);
}

void CBinder::load(IReader& input_packet)
{
    CCustomTimerBase::load(input_packet);
    load_data(m_sFuncName, input_packet);
    load_data(m_expired, input_packet);
    using ParamNumType = std::vector<std::string>::size_type;
    ParamNumType params_num;
    load_data(params_num, input_packet);
    for(ParamNumType i = 0; i < params_num; ++i)
    {
        std::string param;
        load_data(param, input_packet);
        m_params.push_back(param);
    }
    m_bIsActive = true;
}

void CCustomTimerBase::Update()
{
    if (!m_bIsActive)
        return;

    //u32 elapsedTime = (ai().alife().time_manager().game_time() - m_iStartTime);

    //Msg("Binder elapsed time [%u]", elapsedTime);

    m_iTimerCurValue += Device.dwTimeDelta;

    u32 Mult = 1;

    switch (m_iTimerMode)
    {
    case 1: { // seconds
        Mult = 1000;
        break;
    }
    case 2: { // minutes
        Mult = 1000 * 60;
        break;
    }
    case 3: { // hours
        Mult = 1000 * 60 * 60;
        break;
    }
    }

    if (m_iTimerCurValue >= m_iTimerStartValue * Mult){
        OnTimerEnd();
	}
}

void CCustomTimer::OnTimerEnd()
{
     OnTimerStop(m_sTimerName);

     m_bIsActive = false;
     m_iTimerCurValue = 0;

     luabind::functor<void> funct;
     if (ai().script_engine().functor("mfs_functions.on_custom_timer_end", funct)) {
         funct(m_sTimerName.c_str());
     }
}

void CBinder::OnTimerEnd()
{
    m_bIsActive = false;

    luabind::functor<void> funct;
    if (ai().script_engine().functor(m_sFuncName.c_str(), funct)) {
	    switch (m_params.size())
	    {
	    case 0:
        {
	    	funct();
	    	break;
        }
        case 1:
        {
            funct(m_params[0].c_str());
            break;
        }
        case 2:
        {
            funct(m_params[0].c_str(), m_params[1].c_str());
            break;
        }
        case 3:
        {
            funct(m_params[0].c_str(), m_params[1].c_str(), m_params[2].c_str());
            break;
        }
        default:
		    {
                Msg("! Unable to process binder with [%d] params!", m_params.size());
		    }
	    }
        m_expired = true;
        return;
    }
    Msg("! Unable to process binder with name [%s]!", m_sFuncName.c_str());
}

void CTimerManager::CreateTimer(std::string name, int value, int mode)
{
    for (auto& timer : Timers)
    {
        if ((*timer).getName() == name)
        {
            Msg("! Custom Timer with name [%s] already exists!");
            return;
        }
#ifdef DEBUG
        else
        {
            Msg("Custom Timer: %s : Created (start value: %d)", (*timer).getName(), (*timer).getValue());
        }
#endif
    }

    Timers.push_back(std::make_shared<CCustomTimer>(name, value, mode));
}

bool CTimerManager::DeleteTimer(std::string name)
{
    for (auto it = Timers.begin(); it != Timers.end(); ++it)
    {
        if ((*it)->getName() == name)
        {
            (*it)->StopCustomTimer();
            Timers.erase(it);
            return true;

#ifdef DEBUG
            Msg("Custom Timer: %s : Deleted", (*it)->getName());
#endif
        }
    }
    return false;
}

bool CTimerManager::ResetTimer(std::string name)
{
    for (auto& timer : Timers)
    {
        if ((*timer).getName() == name)
        {
            (*timer).ResetCustomTimer();
            return true;
        }
    }
    return false;
}

bool CTimerManager::StartTimer(std::string name, int start_time, int mode)
{
    for (auto& timer : Timers)
    {
        if ((*timer).getName() == name)
        {
            (*timer).SetOnTimerStopCallback([this, name = (*timer).getName()](std::string stopped_name)
            {
                OnTimerStop(stopped_name);
            });

            if ((*timer).getCurValue() > 0)
                (*timer).ResetCustomTimer();

            if (mode)
                (*timer).setMode(mode);

            if (start_time > 0)
                (*timer).setValue(start_time);

            (*timer).StartCustomTimer();

            return true;
        }
    }
    return false;
}

bool CTimerManager::StopTimer(std::string name)
{
    for (auto& timer : Timers)
    {
        if ((*timer).getName() == name)
        {
            (*timer).StopCustomTimer();
            return true;
        }
    }
    return false;
}

void CTimerManager::save(NET_Packet& packet)
{
    u32 timer_count = static_cast<u32>(Timers.size());
    save_data(timer_count, packet);

    for (const auto& timer : Timers)
    {
        timer->save(packet);
    }
}

void CTimerManager::load(IReader& packet)
{
    u32 timer_count = 0;
    load_data(timer_count, packet);

    Timers.clear();

    for (u32 i = 0; i < timer_count; ++i)
    {
        auto timer = std::make_shared<CCustomTimer>();
        timer->load(packet);
        Timers.push_back(timer);
    }
}

int CTimerManager::GetTimerValue(std::string name) const
{
    for (const auto& timer : Timers)
    {
        if ((*timer).getName() == name)
        {
            return (*timer).getCurValue();
        }
    }

    return -1;
}

void CTimerManager::Update()
{
    for (auto& timer : Timers)
    {
        timer->Update();
    }
}

void CBinderManager::CreateBinder(std::string name, const std::vector<std::string>& params, int value, int mode)
{
    Binders.push_back(std::make_unique<CBinder>(name, params, value, mode));
}

void CBinderManager::save(NET_Packet& packet)
{
    u32 timer_count = static_cast<u32>(Binders.size());
    save_data(timer_count, packet);

    for (const auto& timer : Binders)
    {
        timer->save(packet);
    }
}

void CBinderManager::load(IReader& packet)
{
    u32 timer_count = 0;
    load_data(timer_count, packet);

    Binders.clear();

    for (u32 i = 0; i < timer_count; ++i)
    {
        Binders.push_back(std::make_unique<CBinder>());
        Binders.back()->load(packet);
    	/*auto timer = std::make_unique<CBinder>();
        timer->load(packet);
        Binders.push_back(timer);*/
    }
}

void CBinderManager::Update()
{
    int expired_num = 0;
    auto OrigBindersNum = Binders.size();
    for (size_t i = 0; i < OrigBindersNum; ++i)
    {
        Binders[i]->Update();
        if(Binders[i]->getExpired())
        {
            ++expired_num;
        }
    }
    if(!expired_num)
    {
	    return;
    }
    // move all expired binders at the end of vector ...
    int found_expired = 0;
    for(int i = 0; i < Binders.size() - expired_num; ++i)
    {
        while(Binders[i]->getExpired())
        {
            std::swap(Binders[i], Binders[Binders.size() - 1 - found_expired]);
            ++found_expired;
        }
        if(expired_num == found_expired)
        {
            break;
        }
    }
    // ... and remove them
    Binders.resize(Binders.size() - expired_num);
}