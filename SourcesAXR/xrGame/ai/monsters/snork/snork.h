#pragma once
#include "../BaseMonster/base_monster.h"
#include "../../../../xrServerEntities/script_export_space.h"

class CSnork :	public CBaseMonster {
	typedef		CBaseMonster		inherited;

	SVelocityParam	m_fsVelocityJumpPrepare;
	SVelocityParam	m_fsVelocityJumpGround;

public:
					CSnork				();
	~CSnork				() override;

	void	Load				(LPCSTR section) override;
	void	reinit				() override;
	void	UpdateCL			() override;
	void	CheckSpecParams		(u32 spec_params) override;
	void	jump				(const Fvector &position, float factor) override;
	bool	ability_jump_over_physics	() override {return true;}
	bool	ability_distant_feel		() override {return true;}
	void	HitEntityInJump		(const CEntity *pEntity) override;
			
			bool	find_geometry		(Fvector &dir);
			float	trace				(const Fvector &dir);

			bool	trace_geometry		(const Fvector &d, float &range);

	bool	check_start_conditions	(ControlCom::EControlType type) override;
	void	on_activate_control		(ControlCom::EControlType) override;
	char*	get_monster_class_name () override { return "snork"; }

	bool	run_home_point_when_enemy_inaccessible () const override { return false; }

private:
#ifdef _DEBUG	
	virtual void	debug_on_key		(int key);
#endif

public:

		u32		m_target_node;
		bool	start_threaten;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CSnork)
#undef script_type_list
#define script_type_list save_type_list(CSnork)
