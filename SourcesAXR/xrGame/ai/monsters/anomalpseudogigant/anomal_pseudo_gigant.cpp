#include "stdafx.h"
#include "pch_script.h"
#include "anomal_pseudo_gigant.h"
#include "../../../sound_player.h"
#include "../burer/burer.h"
#include "../../../GamePersistent.h"
#include "script_callback_ex.h"
#include "script_game_object.h"
#include "../monster_velocity_space.h"
#include "../control_animation_base.h"
#include "../control_movement_base.h"
#include "anomal_pseudo_gigant_state_manager.h"

CAnomalPseudoGigant::CAnomalPseudoGigant()
{
	StateMan = xr_new<CStateManagerAnomalPseudoGigant>(this);
	m_shield_active = false;
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

	SVelocityParam& velocity_turn = move().get_velocity(MonsterMovement::eVelocityParameterStand);

	anim().AddAnim(eAnimShieldStart, "stand_lie_down_", -1, &velocity_turn, PS_STAND, 	"fx_stand_f", "fx_stand_b", "fx_stand_l", "fx_stand_r");
	anim().AddAnim(eAnimShieldContinue, "stand_sleep_", -1, &velocity_turn, PS_LIE, 	"fx_stand_f", "fx_stand_b", "fx_stand_l", "fx_stand_r");

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

//IC		CAnomalGigPolterSpecialAbility* ability() { return (m_flame ? m_flame : m_tele); } // remake: tele on 66% hp, flame +tele on 33% hp

bool CAnomalPseudoGigant::use_tele_ability() { 
	return m_tele->is_avalable(); 
}

bool CAnomalPseudoGigant::use_fire_ability() { 
	return m_flame->is_avalable(); 
}

void CAnomalPseudoGigant::ActivateShield()
{
	m_shield_active = true;
	callback(GameObject::eShieldOn)(lua_game_object());
}

void CAnomalPseudoGigant::DeactivateShield()
{
	m_shield_active = false;
	callback(GameObject::eShieldOff)(lua_game_object());
}

/*void CAnomalPseudoGigant::on_shield_on()
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
}*/

void CAnomalPseudoGigant::on_jump()
{
	callback(GameObject::eJump)(lua_game_object());
	//luabind::call_member<void>(this, "on_jump");
}

void	CAnomalPseudoGigant::Hit(SHit* pHDS)
{
	//inherited::Hit(pHDS);
	if (conditions().GetHealth() <= 0.0f) {
		return;
	}
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

bool CAnomalPseudoGigant::check_start_conditions(ControlCom::EControlType type)
{
	if (m_shield_active) {
		return false;
	}
	inherited::check_start_conditions(type);
}
