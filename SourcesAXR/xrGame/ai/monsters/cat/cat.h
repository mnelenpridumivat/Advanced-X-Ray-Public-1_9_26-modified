#pragma once
#include "../BaseMonster/base_monster.h"
#include "../../../../xrServerEntities/script_export_space.h"

class CCat : public CBaseMonster{
	typedef		CBaseMonster	inherited;
public:
					CCat				();
	~CCat				() override;

	void	Load				(LPCSTR section) override;
	void	reinit				() override;

	void	UpdateCL			() override;

	void	CheckSpecParams		(u32 spec_params) override;

			void	try_to_jump			();

	void	HitEntityInJump		(const CEntity *pEntity) override;

	char*	get_monster_class_name () override { return "cat"; }


	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CCat)
#undef script_type_list
#define script_type_list save_type_list(CCat)


