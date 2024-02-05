#pragma once
#include "../state.h"

template<typename _Object>
class CStateChimeraThreatenSteal : public CStateMonsterMoveToPointEx<_Object> {
	typedef CStateMonsterMoveToPointEx<_Object>		inherited;

public:
	IC					CStateChimeraThreatenSteal	(_Object *obj) : inherited(obj){}
	void		initialize					() override;
	void		finalize					() override;
	void		execute						() override;
	bool		check_completion			() override;
	bool		check_start_conditions		() override;
};

#include "chimera_state_threaten_steal_inline.h"
