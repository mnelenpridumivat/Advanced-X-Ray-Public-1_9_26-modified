#pragma once

#include "../../../detail_path_manager.h"

template<typename _Object>
class CStateMonsterHittedMoveOut : public CState<_Object> {
	typedef	CState<_Object>		inherited;
	typedef	CState<_Object>*	state_ptr;

	struct {
		Fvector position;
		u32		node;
	} target;

public:

					CStateMonsterHittedMoveOut	(_Object *obj) : inherited(obj) {}
	~CStateMonsterHittedMoveOut	() override {}

	void	initialize					() override;
	void	execute						() override;
	bool 	check_completion			() override;
	void	remove_links				(CObject* object) override { inherited::remove_links(object);}

private:
			void	select_target				();

};

#include "monster_state_hitted_moveout_inline.h"

