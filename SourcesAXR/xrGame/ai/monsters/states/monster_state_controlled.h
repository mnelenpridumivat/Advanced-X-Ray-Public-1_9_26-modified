#pragma once

#include "../state.h"

template<typename _Object>
class	CStateMonsterControlled : public CState<_Object> {
	typedef CState<_Object>		inherited;

public:
						CStateMonsterControlled		(_Object *obj);
	void		execute						() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_controlled_inline.h"
