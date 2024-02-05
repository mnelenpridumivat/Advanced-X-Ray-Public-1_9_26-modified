#pragma once

#include "../state.h"
#include "state_data.h"

template<typename _Object>
class CStateMonsterMoveAroundPoint : public CState<_Object> {
	typedef CState<_Object> inherited;

	SStateDataMoveAroundPoint data;

public:
						CStateMonsterMoveAroundPoint	(_Object *obj) : inherited(obj, &data) {}
	~CStateMonsterMoveAroundPoint	() override {}

	void		initialize						() override;
	void		execute							() override;

	bool		check_completion				() override;
};

#include "state_move_to_point_inline.h"