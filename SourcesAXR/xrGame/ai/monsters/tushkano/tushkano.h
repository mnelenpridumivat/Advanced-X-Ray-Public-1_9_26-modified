#pragma once
#include "../BaseMonster/base_monster.h"
#include "../controlled_entity.h"
#include "../../../../xrServerEntities/script_export_space.h"

class CTushkano :	public CBaseMonster,
					public CControlledEntity<CTushkano> {


	typedef		CBaseMonster					inherited;
	typedef		CControlledEntity<CTushkano>	CControlled;

public:
					CTushkano 			();
	~CTushkano 			() override;

	void	Load				(LPCSTR section) override;
	void	CheckSpecParams		(u32 spec_params) override;
	char*	get_monster_class_name () override { return "tushkano"; }


	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CTushkano)
#undef script_type_list
#define script_type_list save_type_list(CTushkano)
