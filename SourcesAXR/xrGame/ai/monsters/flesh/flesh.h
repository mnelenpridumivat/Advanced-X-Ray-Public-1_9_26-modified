#pragma once
#include "../BaseMonster/base_monster.h"
#include "../controlled_entity.h"
#include "../../../../xrServerEntities/script_export_space.h"

class CAI_Flesh : public CBaseMonster,
				  public CControlledEntity<CAI_Flesh> {

	typedef		CBaseMonster					inherited;
	typedef		CControlledEntity<CAI_Flesh>	CControlled;

public:
							CAI_Flesh		();
	~CAI_Flesh		() override;

	void	Load					(LPCSTR section) override;
	BOOL	net_Spawn				(CSE_Abstract* DC) override;

	void	CheckSpecParams			(u32 spec_params) override;

	bool	ability_can_drag		() override {return true;}

	char*	get_monster_class_name () override { return "flesh"; }


private:
	bool	ConeSphereIntersection	(Fvector ConeVertex, float ConeAngle, Fvector ConeDir, 
									Fvector SphereCenter, float SphereRadius);
	
	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CAI_Flesh)
#undef script_type_list
#define script_type_list save_type_list(CAI_Flesh)

