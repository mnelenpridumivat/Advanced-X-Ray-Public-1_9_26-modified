#pragma once
#include "../BaseMonster/base_monster.h"
#include "../controlled_entity.h"
#include "../ai_monster_bones.h"
#include "../anim_triple.h"
#include "../../../../xrServerEntities/script_export_space.h"

#define FAKE_DEATH_TYPES_COUNT	4

class CZombie :	public CBaseMonster,
				public CControlledEntity<CZombie> {
	
	typedef		CBaseMonster				inherited;
	typedef		CControlledEntity<CZombie>	CControlled;

	bonesManipulation	Bones;

public:
					CZombie		();
	~CZombie	() override;

	void	Load				(LPCSTR section) override;
	BOOL	net_Spawn			(CSE_Abstract* DC) override;
	void	reinit				() override;
	void	reload				(LPCSTR section) override;

	void	Hit					(SHit* pHDS) override;

	bool	ability_pitch_correction () override {return false;}

	void	shedule_Update		(u32 dt) override;
	
	static	void 	BoneCallback		(CBoneInstance *B);
			void	vfAssignBones		();

	bool	use_center_to_aim				() const override {return true;}
	char*	get_monster_class_name () override { return "zombie"; }


	CBoneInstance			*bone_spine;
	CBoneInstance			*bone_head;

	SAnimationTripleData	anim_triple_death[FAKE_DEATH_TYPES_COUNT];
	u8				active_triple_idx;
	
	u32				time_dead_start;
	u32				last_hit_frame;
	u32				time_resurrect;
	bool			fakedeath_is_active;

	u8				fake_death_count;
	float			health_death_threshold;
	u8				fake_death_left;

	bool			fake_death_fall_down	(); //return true if everything is ok
	void			fake_death_stand_up		();
	virtual bool	fake_death_is_active	() const { return fakedeath_is_active; }

#ifdef _DEBUG
	virtual void	debug_on_key			(int key);
#endif


	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CZombie)
#undef script_type_list
#define script_type_list save_type_list(CZombie)
