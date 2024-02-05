#pragma once

#include "../BaseMonster/base_monster.h"
#include "../../../../xrServerEntities/script_export_space.h"

class CAI_PseudoDog : public CBaseMonster {
	typedef		CBaseMonster	inherited;

public:

	float			m_anger_hunger_threshold;
	float			m_anger_loud_threshold;

	TTime			m_time_became_angry;

	TTime			time_growling;			// время нахождения в состоянии пугания

	enum {
		eAdditionalSounds		= MonsterSound::eMonsterSoundCustom,
		ePsyAttack				= eAdditionalSounds | 0,
	};
public:
					CAI_PseudoDog		();
	~CAI_PseudoDog		() override;

	DLL_Pure	*_construct		() override;

	void	Load				(LPCSTR section) override;

	void	reinit				() override;
	void	reload				(LPCSTR section) override;

	bool	ability_can_drag	() override {return true;}
	bool	ability_psi_attack	() override {return true;}

	void	CheckSpecParams		(u32 spec_params) override;
	//virtual void	play_effect_sound	();

	void	HitEntityInJump		(const CEntity *pEntity) override;

	virtual IStateManagerBase *create_state_manager	();
	char*	get_monster_class_name () override { return "pseudodog"; }

private:
#ifdef _DEBUG	
	virtual void	debug_on_key		(int key);
#endif

	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CAI_PseudoDog)
#undef script_type_list
#define script_type_list save_type_list(CAI_PseudoDog)
