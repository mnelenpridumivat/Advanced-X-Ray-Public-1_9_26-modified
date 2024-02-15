#pragma once
#include "PolterInterface.h"
#include "../BaseMonster/base_monster.h"
#include "../telekinesis.h"
#include "../energy_holder.h"
#include "../../../../xrServerEntities/script_export_space.h"

class CPhysicsShellHolder;
class CStateManagerPoltergeist;
class CPoltergeisMovementManager;
class CPolterSpecialAbility;
class CPolterTele;

//////////////////////////////////////////////////////////////////////////


class CPoltergeist :	
	public CBaseMonster,
	public CTelekinesis,
	public CEnergyHolder,
	public IPolterInterface,
	public IMetaClass
{
	DECLARE_METACLASS4(CPoltergeist, CBaseMonster, CTelekinesis, CEnergyHolder, IPolterInterface)
	
	typedef		CBaseMonster	inherited;
	typedef		CEnergyHolder	Energy;

	friend class CPoltergeisMovementManager;
	friend class CPolterTele;

	float					m_height;
	bool					m_disable_hide;
	bool					m_dead_always_visible;
	bool					m_bPolterVisibleDie;

	SMotionVel				invisible_vel;


	CPolterSpecialAbility	*m_flame;
	CPolterSpecialAbility	*m_tele;
	CPolterSpecialAbility	*m_chem;

	bool					m_actor_ignore;

	TTime					m_last_detection_time;
	Fvector					m_last_actor_pos;
	char const*				m_detection_pp_effector_name;
	u32						m_detection_pp_type_index;
	float					m_detection_near_range_factor;
	float					m_detection_far_range_factor;
	float					m_detection_far_range;
	float					m_detection_speed_factor;
	float					m_detection_loose_speed;
	float					m_current_detection_level;
	float					m_detection_success_level;
	float					m_detection_max_level;

public:
	bool					m_detect_without_sight;

	// begin IPolterInterface
	virtual CBaseMonster* GetMonster() override { return this; }
	virtual CTelekinesis* GetTelekinesis() override { return this; }
	virtual const Fvector& GetCurrentPosition() override { return m_current_position; }
	virtual float GetTargetHeight() override { return target_height; }
	virtual float GetCurrentDetectionLevel() override { return get_current_detection_level(); }
	virtual float GetDetectionSuccessLevel() override { return get_detection_success_level(); }
	virtual bool GetActorIgnore() override { return get_actor_ignore(); }
	// end IPolterInterface

public:
					CPoltergeist		();
	~CPoltergeist		() override;

	void	Load				(LPCSTR section) override;
	void	reload				(LPCSTR section) override;
	void	reinit				() override;

	BOOL	net_Spawn			(CSE_Abstract* DC) override;
	void	net_Destroy			() override;
	void	net_Relcase			(CObject *O) override;

	void	UpdateCL			() override;
	void	shedule_Update		(u32 dt) override;

			void	set_actor_ignore	(bool const actor_ignore) { m_actor_ignore = actor_ignore; }
			bool	get_actor_ignore	() const { return m_actor_ignore; }

	void	Die					(CObject* who) override;

	CMovementManager *create_movement_manager() override;

	void	ForceFinalAnimation	() override;

	void	on_activate			() override;
	void	on_deactivate		() override;
	void	Hit					(SHit* pHDS) override;
	char*	get_monster_class_name () override { return "poltergeist"; }

			bool	detected_enemy		();
			float	get_fly_around_distance	() const { return m_fly_around_distance; }
			float	get_fly_around_change_direction_time() const { return m_fly_around_change_direction_time; }

	void	renderable_Render	() override;

	IC		bool	is_hidden			() {return state_invisible;}

	
	// Poltergeist ability
			void	PhysicalImpulse		(const Fvector &position);
			void	StrangeSounds		(const Fvector &position);
			
			ref_sound m_strange_sound;
	
	// Movement
			Fvector m_current_position;		// Позиция на ноде

	// Dynamic Height
			u32		time_height_updated;
			float	target_height;

			void	UpdateHeight			();

	// Invisibility 

			void	EnableHide				(){m_disable_hide = false;}
			void	DisableHide				(){m_disable_hide = true;}

public:
	bool	run_home_point_when_enemy_inaccessible () const override { return false; }
	
private:
			void	Hide					();
			void	Show					();

			float	m_height_change_velocity;
			u32		m_height_change_min_time;
			u32		m_height_change_max_time;
			float	m_height_min;
			float	m_height_max;
			
			float	m_fly_around_level;
			float	m_fly_around_distance;
			float	m_fly_around_change_direction_time;

			float	get_current_detection_level			() const { return m_current_detection_level; }
			bool	check_work_condition				() const;
			void    remove_pp_effector					();
			void	update_detection					();

			float	get_detection_near_range_factor		();
			float	get_detection_far_range_factor		();
			float	get_detection_loose_speed			();
			float	get_detection_far_range				();
			float	get_detection_speed_factor			();
			float	get_detection_success_level			();
			float   xr_stdcall get_post_process_factor	() const;

public:
#ifdef DEBUG
	CBaseMonster::SDebugInfo show_debug_info() override;
#endif
	

			friend class CPolterFlame;
	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CPoltergeist)
#undef script_type_list
#define script_type_list save_type_list(CPoltergeist)

