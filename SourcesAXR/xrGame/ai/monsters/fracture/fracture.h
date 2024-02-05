#pragma once
#include "../BaseMonster/base_monster.h"
#include "../../../../xrServerEntities/script_export_space.h"

class CStateManagerFracture;

class CFracture : public CBaseMonster {
	typedef		CBaseMonster		inherited;
	
public:
					CFracture 			();
	~CFracture 			() override;

	void	Load				(LPCSTR section) override;
	void	CheckSpecParams		(u32 spec_params) override;

	char*	get_monster_class_name () override { return "fracture"; }


	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CFracture)
#undef script_type_list
#define script_type_list save_type_list(CFracture)
