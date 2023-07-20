#include "stdafx.h"
#include "pch_script.h"
#include "anomal_pseudo_gigant.h"
#include "../../../sound_player.h"
#include "../burer/burer.h"
#include "../../../GamePersistent.h"
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
	inherited::Load(section);
	m_flame = xr_new<CAnomalGigPolterFlame>(this);
	m_flame->load(section);
	m_tele = xr_new<CAnomalGigPolterTele>(this);
	m_tele->load(section);

	m_shield_cooldown = READ_IF_EXISTS(pSettings, r_u32, section, "shield_cooldown", 4000);
	m_shield_time = READ_IF_EXISTS(pSettings, r_u32, section, "shield_time", 3000);
	m_shield_keep_particle = READ_IF_EXISTS(pSettings, r_string, section, "shield_keep_particle", 0);
	m_shield_keep_particle_period = READ_IF_EXISTS(pSettings, r_u32, section, "shield_keep_particle_period", 1000);

	particle_fire_shield = pSettings->r_string(section, "Particle_Shield");
}

void CAnomalPseudoGigant::UpdateCL()
{
	inherited::UpdateCL();
	if (use_fire_ability()) m_flame->update_frame();
	if (use_tele_ability()) m_tele->update_frame();
}

void CAnomalPseudoGigant::shedule_Update(u32 dt)
{
	inherited::shedule_Update(dt);
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

void CAnomalPseudoGigant::on_shield_on()
{
	//luabind::call_member<void>(this, "on_shield_on");
}

void CAnomalPseudoGigant::on_shield_off()
{
	//luabind::call_member<void>(this, "on_shield_off");
}

void CAnomalPseudoGigant::on_hit()
{
	//luabind::call_member<void>(this, "on_hit");
}

void CAnomalPseudoGigant::on_jump()
{
	//luabind::call_member<void>(this, "on_jump");
}

void	CAnomalPseudoGigant::Hit(SHit* pHDS)
{
	if (m_shield_active &&
		pHDS->hit_type == ALife::eHitTypeFireWound &&
		Device.dwFrame != last_hit_frame)
	{
		// вычислить позицию и направленность партикла
		Fmatrix pos;
		//CParticlesPlayer::MakeXFORM(this,element,Fvector().set(0.f,0.f,1.f),p_in_object_space,pos);
		CParticlesPlayer::MakeXFORM(this, pHDS->bone(), pHDS->dir, pHDS->p_in_bone_space, pos);

		// установить particles
		CParticlesObject* ps = CParticlesObject::Create(particle_fire_shield, TRUE);

		ps->UpdateParent(pos, Fvector().set(0.f, 0.f, 0.f));
		GamePersistent().ps_needtoplay.push_back(ps);

	}
	else if (!m_shield_active)
	{
		inherited::Hit(pHDS);
	}

	last_hit_frame = Device.dwFrame;
}
