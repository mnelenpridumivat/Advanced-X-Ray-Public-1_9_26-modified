#pragma once

#include "../BaseMonster/base_monster.h"
#include "../controlled_entity.h"
#include "../../../../xrServerEntities/script_export_space.h"

class CAI_Boar : public CBaseMonster,
				 public CControlledEntity<CAI_Boar> {

	typedef		CBaseMonster	inherited;
	typedef		CControlledEntity<CAI_Boar>	CControlled;

public:
					CAI_Boar			();
	~CAI_Boar			() override;

	void	Load				(LPCSTR section) override;
	BOOL	net_Spawn			(CSE_Abstract* DC) override;
	void	reinit				() override;

	void	UpdateCL			() override;

	virtual bool	CanExecRotationJump	() {return true;}
	void	CheckSpecParams		(u32 spec_params) override;

	// look at enemy
	static void	_BCL	BoneCallback	(CBoneInstance *B);
	
			float	_velocity;
			float	_cur_delta, _target_delta;
			bool	look_at_enemy;

	bool	ability_can_drag	() override {return true;}

	char*	get_monster_class_name () override { return "boar"; }
	
	DECLARE_SCRIPT_REGISTER_FUNCTION

};

add_to_type_list(CAI_Boar)
#undef script_type_list
#define script_type_list save_type_list(CAI_Boar)