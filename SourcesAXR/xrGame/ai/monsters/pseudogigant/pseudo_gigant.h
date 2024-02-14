#pragma once
#include "../BaseMonster/base_monster.h"
#include "../controlled_entity.h"
#include "../../../../xrServerEntities/script_export_space.h"


class CPseudoGigant :
	public CBaseMonster,
	public CControlledEntity<CPseudoGigant>,
	public IMetaClass
{
	DECLARE_METACLASS2(CPseudoGigant, CBaseMonster, CControlledEntity<CPseudoGigant>)
	
	typedef		CBaseMonster						inherited;
	typedef		CControlledEntity<CPseudoGigant>	CControlled;

private:
	xr_vector<CObject*>		m_nearest_pseudogig_kick;

	// step_effector
	struct {
		float time;
		float amplitude;	
		float period_number;
	} step_effector;

	SAttackEffector m_threaten_effector;
	ref_sound		m_sound_threaten_hit;		// ����, ������� �������� � ������ � ������
	ref_sound		m_sound_start_threaten;		// ����, ������� �������� � ������ � ������
	
	u32				m_time_next_threaten;
	
	u32				m_threaten_delay_min;
	u32				m_threaten_delay_max;
	float			m_threaten_dist_min;
	float			m_threaten_dist_max;

	float			m_kick_damage;
	
	u32				m_time_kick_actor_slow_down;

	SVelocityParam	m_fsVelocityJumpPrepare;
	SVelocityParam	m_fsVelocityJumpGround;

	LPCSTR			m_kick_particles;


public:
					CPseudoGigant				();
	~CPseudoGigant				() override;

	void	Load				(LPCSTR section) override;
	void	reinit				() override;

	bool	ability_earthquake	() override {return true;}
	void	event_on_step		() override;

	bool	check_start_conditions	(ControlCom::EControlType type) override;
	void	on_activate_control		(ControlCom::EControlType) override;

	void	on_threaten_execute	() override;

	void	HitEntityInJump		(const CEntity *pEntity) override;
	void	TranslateActionToPathParams	() override;
	char*	get_monster_class_name () override { return "pseudogigant"; }

	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CPseudoGigant)
#undef script_type_list
#define script_type_list save_type_list(CPseudoGigant)
