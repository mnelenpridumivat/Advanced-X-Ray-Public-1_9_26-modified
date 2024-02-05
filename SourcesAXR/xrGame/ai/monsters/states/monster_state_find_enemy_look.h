#pragma once

#include "../state.h"

template<typename _Object>
class CStateMonsterFindEnemyLook : public CState<_Object> {
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	bool		look_right_side;
	u8			current_stage;
	Fvector		target_point;

	Fvector		current_dir;
	Fvector		start_position;

	enum {
		eMoveToPoint = static_cast<u32>(0),
		eLookAround,
		eTurnToPoint
	} ;

public:
						CStateMonsterFindEnemyLook	(_Object *obj);
	~CStateMonsterFindEnemyLook	() override;

	void		initialize					() override;
	void		reselect_state				() override;
	bool		check_completion			() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}

	void		setup_substates				() override;
};

#include "monster_state_find_enemy_look_inline.h"
