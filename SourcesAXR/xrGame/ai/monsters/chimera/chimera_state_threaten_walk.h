#pragma once
#include "../state.h"

template<typename _Object>
class CStateChimeraThreatenWalk : public CStateMonsterMoveToPointEx<_Object> {
	typedef CStateMonsterMoveToPointEx<_Object>		inherited;

public:
	IC					CStateChimeraThreatenWalk	(_Object *obj) : inherited(obj){}
	void		initialize					() override;
	void		execute						() override;
	bool		check_completion			() override;
	bool		check_start_conditions		() override;
	
};

#include "chimera_state_threaten_walk_inline.h"
