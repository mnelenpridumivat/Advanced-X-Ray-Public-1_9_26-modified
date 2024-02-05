#pragma once
#include "../state.h"
#include "state_data.h"

template<typename _Object>
class CStateMonsterLookToPoint : public CState<_Object> {
	typedef CState<_Object> inherited;

	SStateDataLookToPoint	data;

public:
						CStateMonsterLookToPoint	(_Object *obj);
	~CStateMonsterLookToPoint	() override;

	void		initialize					() override;
	void		execute						() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}

	bool		check_completion			() override;
};

#include "state_look_point_inline.h"