#pragma once
#include "../state.h"

template<typename _Object>
class CStateMonsterRestWalkGraph : public CState<_Object> {
	typedef CState<_Object> inherited;

public:
						CStateMonsterRestWalkGraph	(_Object *obj);
	~CStateMonsterRestWalkGraph	() override;

	void		execute					() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_rest_walk_graph_inline.h"
