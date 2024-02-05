#pragma once
#include "../state.h"

template<typename _Object>
class CStateMonsterMoveToRestrictor : public CState<_Object> {
	typedef CState<_Object> inherited;

public:
						CStateMonsterMoveToRestrictor	(_Object *obj) : inherited(obj) {}
	~CStateMonsterMoveToRestrictor	() override {}

	void		initialize					() override;
	void		execute						() override;

	bool		check_start_conditions		() override;
	bool		check_completion			() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "state_move_to_restrictor_inline.h"
