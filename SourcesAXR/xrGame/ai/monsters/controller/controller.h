#pragma once
#include "../BaseMonster/base_monster.h"
#include "../anim_triple.h"
#include "../../../../xrServerEntities/script_export_space.h"
#include "../controlled_actor.h"

class CControllerAnimation;
class CControllerDirection;
class SndShockEffector;
class CControllerPsyHit;
class CControllerAura;

class CController :
	public CBaseMonster,
	public CControlledActor,
	public IMetaClass
{
	DECLARE_METACLASS2(CController, CBaseMonster, CControlledActor)

	typedef		CBaseMonster	inherited;

	u8					m_max_controlled_number;
	ref_sound			control_start_sound;		// ����, ������� �������� � ������ � ������
	ref_sound			control_hit_sound;			// ����, ������� �������� � ������ � ������

	ref_sound			m_sound_hit_fx;
	SndShockEffector*	m_sndShockEffector;					

	SAttackEffector		m_control_effector;

	u32					time_control_hit_started;
	bool				active_control_fx;
	
	LPCSTR				particles_fire;

	CControllerAnimation	*m_custom_anim_base;
	CControllerDirection	*m_custom_dir_base;

	u32					m_psy_fire_start_time;
	u32					m_psy_fire_delay;

	bool				m_tube_at_once;

public:	
	float			aura_radius;
	float			aura_damage;

	//////////////////////////////////////////////////////////////////////////

public:	
	CControllerPsyHit	*m_psy_hit;

	ref_sound			m_sound_aura_left_channel;
	ref_sound			m_sound_aura_right_channel;
	ref_sound			m_sound_aura_hit_left_channel;
	ref_sound			m_sound_aura_hit_right_channel;

	ref_sound			m_sound_tube_start;
	ref_sound			m_sound_tube_pull;
	ref_sound			m_sound_tube_hit_left;
	ref_sound			m_sound_tube_hit_right;

	ref_sound			m_sound_tube_prepare;

public:	
	SVelocityParam		m_velocity_move_fwd;
	SVelocityParam		m_velocity_move_bkwd;

public:	
	CControllerAnimation	&custom_anim()	{return (*m_custom_anim_base);}
	CControllerDirection	&custom_dir()	{return (*m_custom_dir_base);}

public:
	xr_vector<CEntity*> m_controlled_objects;

public:
					CController			();
	~CController		() override;

	void	Load				(LPCSTR section) override;
	void	reload				(LPCSTR section) override;
	void	reinit				() override;
	void	UpdateCL			() override;
	void	shedule_Update		(u32 dt) override;
	void	Die					(CObject* who) override;

	void	net_Destroy			() override;
	BOOL	net_Spawn			(CSE_Abstract *DC) override;
	void	net_Relcase			(CObject *O) override;

	void	CheckSpecParams		(u32 spec_params) override;
	void	InitThink			() override;

	void	create_base_controls() override;

	const MonsterSpace::SBoneRotation &head_orientation	() const override;

	void	TranslateActionToPathParams	() override;

	bool	ability_pitch_correction () override {return false;}

	//-------------------------------------------------------------------

	bool	is_relation_enemy	(const CEntityAlive *tpEntityAlive) const override;
	xr_vector<shared_str>				m_friend_community_overrides;
	void								load_friend_community_overrides	(LPCSTR section);
	bool								is_community_friend_overrides	(const CEntityAlive *tpEntityAlive) const;
	//-------------------------------------------------------------------
	// Controller ability
			bool	HasUnderControl		() {return (!m_controlled_objects.empty());}
			void	TakeUnderControl	(CEntity *);
			void	UpdateControlled	();
			void	FreeFromControl		();
			void	OnFreedFromControl	(const CEntity *);  // ���� ������ ��� ���� ��������� (destroyed || die)

			void	set_controlled_task (u32 task);



			void	play_control_sound_start	();
			void	play_control_sound_hit		();

			void	control_hit					();

			void	psy_fire					();
			bool	can_psy_fire				();

			void	tube_fire					();
			bool	can_tube_fire				();
			
			float	m_tube_damage;
			u32		m_tube_condition_see_duration ;
			u32		m_tube_condition_min_delay    ;
			float   m_tube_condition_min_distance ;

			void	set_psy_fire_delay_zero		();
			void	set_psy_fire_delay_default	();

			float	get_tube_min_distance		() const { return m_tube_condition_min_distance; }
			bool	tube_ready					() const;

	//-------------------------------------------------------------------

	

public: 

	void						draw_fire_particles();
	
	void						test_covers();


public:
	enum EMentalState {
		eStateIdle,
		eStateDanger
	} m_mental_state;

	void				set_mental_state			(EMentalState state);
	void		HitEntity					(const CEntity *pEntity, float fDamage, 
								              float impulse, Fvector &dir, ALife::EHitType hit_type, bool draw_hit_marks) override;

public:
	bool		use_center_to_aim			() const override {return true;}

	SAnimationTripleData anim_triple_control;

	char*		get_monster_class_name		() override { return "controller"; }

private:
	float				m_stamina_hit;


#ifdef DEBUG
	CBaseMonster::SDebugInfo show_debug_info() override;

#endif

private:
#ifdef _DEBUG	
		virtual void	debug_on_key		(int key);

		Fvector			P1,P2;
#endif

public:
	bool					run_home_point_when_enemy_inaccessible () const override { return false; }
	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CController)
#undef script_type_list
#define script_type_list save_type_list(CController)

