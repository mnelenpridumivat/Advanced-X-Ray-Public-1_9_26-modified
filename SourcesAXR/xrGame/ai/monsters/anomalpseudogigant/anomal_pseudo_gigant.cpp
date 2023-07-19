#include "stdafx.h"
#include "anomal_pseudo_gigant.h"
#include "../../../sound_player.h"
#include "../burer/burer.h"
#include "anomal_pseudo_gigant_state_manager.h"

CAnomalPseudoGigant::CAnomalPseudoGigant()
{
	StateMan = xr_new<CStateManagerAnomalPseudoGigant>(this);
}

CAnomalPseudoGigant::~CAnomalPseudoGigant()
{
	xr_delete(m_flame);
	xr_delete(m_tele);
}

void CAnomalPseudoGigant::Load(LPCSTR section)
{
	m_flame = xr_new<CAnomalGigPolterFlame>(this);
	m_flame->load(section);
	m_tele = xr_new<CAnomalGigPolterTele>(this);
	m_tele->load(section);
}

void CAnomalPseudoGigant::UpdateCL()
{
	inherited::UpdateCL();
	if (use_fire_ability()) m_flame->update_frame();
	if (use_tele_ability()) m_tele->update_frame();
}

void CAnomalPseudoGigant::shedule_Update(u32 dt)
{
	if (use_fire_ability()) m_flame->update_schedule();
	if (use_tele_ability()) m_tele->update_schedule();
}

void CAnomalPseudoGigant::jump(const Fvector& position, float factor)
{
	com_man().script_jump(position, factor);
	sound().play(MonsterSound::eMonsterSoundAggressive);
}

float	CAnomalPseudoGigant::get_detection_success_level()
{
	return override_if_debug("detection_success_level", m_detection_success_level);
}

void CAnomalPseudoGigant::ActivateShield()
{
	m_shield_active = true;
}

void CAnomalPseudoGigant::DeactivateShield()
{
	m_shield_active = false;
}
