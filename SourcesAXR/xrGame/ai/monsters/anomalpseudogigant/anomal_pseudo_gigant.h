#pragma once
#include "../xrGame/ai/monsters/pseudogigant/pseudo_gigant.h"
#include "../telekinesis.h"
#include "../../../../xrGame/Hit.h"

class CAnomalGigPolterSpecialAbility;

class CAnomalPseudoGigant : public CPseudoGigant,
							public CTelekinesis {
							//	{

	typedef		CPseudoGigant						inherited;

	bool					m_actor_ignore;

	float					m_current_detection_level;
	float					m_detection_success_level;
	float					m_detection_max_level;

public:
	CAnomalPseudoGigant();
	virtual			~CAnomalPseudoGigant();

	virtual void	Load(LPCSTR section);

	virtual void	UpdateCL();
	virtual	void	shedule_Update(u32 dt);

	virtual	char* get_monster_class_name() { return "anomalpseudogigant"; }

	void	set_actor_ignore(bool const actor_ignore) { m_actor_ignore = actor_ignore; }
	bool	get_actor_ignore() const { return m_actor_ignore; }

	// snork jump

	virtual void	jump(const Fvector& position, float factor);
	virtual bool	ability_jump_over_physics() { return true; }


	// Poltergeist ability

private:

	CAnomalGigPolterSpecialAbility* m_flame = nullptr;
	CAnomalGigPolterSpecialAbility* m_tele = nullptr;

public:

	void	PhysicalImpulse(const Fvector& position);
	void	StrangeSounds(const Fvector& position);

	float	get_current_detection_level() const { return m_current_detection_level; }

	float	get_detection_success_level();

	//IC		CAnomalGigPolterSpecialAbility* ability() { return (m_flame ? m_flame : m_tele); } // remake: tele on 66% hp, flame +tele on 33% hp
	IC		bool use_tele_ability() { return true; }
	IC		bool use_fire_ability() { return true; }

	// burer shield

	void	ActivateShield();
	void	DeactivateShield();

	TTime	m_shield_cooldown;
	TTime	m_shield_time;
	bool	m_shield_active;
	LPCSTR	m_shield_keep_particle;
	TTime	m_shield_keep_particle_period;

	ref_sound m_strange_sound;

	DECLARE_SCRIPT_REGISTER_FUNCTION

};

bool   actor_is_reloading_weapon();

add_to_type_list(CAnomalPseudoGigant)
#undef script_type_list
#define script_type_list save_type_list(CAnomalPseudoGigant)


//////////////////////////////////////////////////////////////////////////
// Interface
//////////////////////////////////////////////////////////////////////////

class CAnomalGigPolterSpecialAbility {

	CParticlesObject* m_particles_object;
	CParticlesObject* m_particles_object_electro;

	LPCSTR				m_particles_hidden;
	LPCSTR				m_particles_damage;
	LPCSTR				m_particles_death;
	LPCSTR				m_particles_idle;

	ref_sound			m_sound_base;
	u32					m_last_hit_frame;

protected:
	CAnomalPseudoGigant* m_object;

public:
	CAnomalGigPolterSpecialAbility(CAnomalPseudoGigant* gigant);
	virtual			~CAnomalGigPolterSpecialAbility();

	virtual void	load(LPCSTR section);
	virtual void	update_schedule();
	virtual void	update_frame();
	virtual void	on_hide();
	virtual void	on_show();
	virtual void	on_destroy() {}
	//virtual void	on_die();
	virtual void	on_hit(SHit* pHDS);
};





//////////////////////////////////////////////////////////////////////////
// Flame
//////////////////////////////////////////////////////////////////////////
class CAnomalGigPolterFlame : public CAnomalGigPolterSpecialAbility {

	typedef CAnomalGigPolterSpecialAbility inherited;

	ref_sound				m_sound;
	LPCSTR					m_particles_prepare;
	LPCSTR					m_particles_fire;
	LPCSTR					m_particles_stop;
	u32						m_time_fire_delay;
	u32						m_time_fire_play;

	float					m_length;
	float					m_hit_value;
	u32						m_hit_delay;

	u32						m_count;
	u32						m_delay;	// between 2 flames

	u32						m_time_flame_started;

	float					m_min_flame_dist;
	float					m_max_flame_dist;
	float					m_min_flame_height;
	float					m_max_flame_height;

	float					m_pmt_aura_radius;


	// Scanner
	float					m_scan_radius;
	u32						m_scan_delay_min;
	u32						m_scan_delay_max;

	SPPInfo					m_scan_effector_info;
	float					m_scan_effector_time;
	float					m_scan_effector_time_attack;
	float					m_scan_effector_time_release;
	ref_sound				m_scan_sound;

	bool					m_state_scanning;
	u32						m_scan_next_time;


	enum EFlameState {
		ePrepare,
		eFire,
		eStop
	};


public:
	struct SFlameElement {
		const CObject* target_object;
		Fvector				position;
		Fvector				target_dir;
		u32					time_started;
		ref_sound			sound;
		CParticlesObject* particles_object;
		EFlameState			state;
		u32					time_last_hit;
	};


private:
	DEFINE_VECTOR(SFlameElement*, FLAME_ELEMS_VEC, FLAME_ELEMS_IT);
	FLAME_ELEMS_VEC			m_flames;

public:
	CAnomalGigPolterFlame(CAnomalPseudoGigant* gigant);
	virtual			~CAnomalGigPolterFlame();

	virtual void	load(LPCSTR section);
	virtual void	update_schedule();
	virtual void	on_destroy();
	//virtual void	on_die();

private:
	void	select_state(SFlameElement* elem, EFlameState state);
	bool	get_valid_flame_position(const CObject* target_object, Fvector& res_pos);
	void	create_flame(const CObject* target_object);
};


//////////////////////////////////////////////////////////////////////////
// TELE
//////////////////////////////////////////////////////////////////////////
class CAnomalGigPolterTele : public CAnomalGigPolterSpecialAbility {
	typedef CAnomalGigPolterSpecialAbility inherited;

	xr_vector<CObject*>	m_nearest;

	// external params
	float				m_pmt_radius;
	float				m_pmt_object_min_mass;
	float				m_pmt_object_max_mass;
	u32					m_pmt_object_count;
	u32					m_pmt_time_to_hold;
	u32					m_pmt_time_to_wait;
	u32					m_pmt_time_to_wait_in_objects;
	u32					m_pmt_raise_time_to_wait_in_objects;
	float				m_pmt_distance;
	float				m_pmt_object_height;
	u32					m_pmt_time_object_keep;
	float				m_pmt_raise_speed;
	float				m_pmt_fly_velocity;

	float				m_pmt_object_collision_damage;

	ref_sound			m_sound_tele_hold;
	ref_sound			m_sound_tele_throw;

	enum ETeleState {
		eStartRaiseObjects,
		eRaisingObjects,
		eFireObjects,
		eWait
	} m_state;

	u32					m_time;
	u32					m_time_next;

public:
	CAnomalGigPolterTele(CAnomalPseudoGigant* gigant);
	virtual			~CAnomalGigPolterTele();

	virtual void	load(LPCSTR section);
	virtual void	update_schedule();
	virtual void	update_frame();

private:
	void	tele_find_objects(xr_vector<CObject*>& objects, const Fvector& pos);
	bool	tele_raise_objects();
	void	tele_fire_objects();

	bool	trace_object(CObject* obj, const Fvector& target);
};