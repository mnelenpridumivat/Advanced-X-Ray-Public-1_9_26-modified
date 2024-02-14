#pragma once
#include "../BaseMonster/base_monster.h"
#include "../../../../xrServerEntities/script_export_space.h"

class CChimera :
	public CBaseMonster,
	public IMetaClass
{
	DECLARE_METACLASS1(CChimera, CBaseMonster)

public:
							CChimera					();
							~CChimera					() override;

							void			Load						(LPCSTR section) override;
							void			reinit						() override;
							void			UpdateCL					() override;

							void			CheckSpecParams				(u32 spec_params) override;
							void			HitEntityInJump				(const CEntity *pEntity) override;
							void			jump						(Fvector const &position, float factor) override;

private:
							char*			get_monster_class_name		() override { return "chimera"; }
							EAction			CustomVelocityIndex2Action	(u32 velocity_index) override;

	typedef					CBaseMonster				inherited;
	
	SVelocityParam 			m_velocity_rotate;
	SVelocityParam 			m_velocity_jump_start;

	struct attack_params
	{
		float				attack_radius;
		TTime				prepare_jump_timeout;
		TTime				attack_jump_timeout;
		TTime				stealth_timeout;
		float				force_attack_distance;
		u32					num_attack_jumps;
		u32					num_prepare_jumps;
	};

	attack_params			m_attack_params;

public:
	attack_params const&	get_attack_params			() const { return m_attack_params; }


	
	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CChimera)
#undef script_type_list
#define script_type_list save_type_list(CChimera)
