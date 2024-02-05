#pragma once
#include "../state.h"
#include "state_data.h"

template<typename _Object>
class CStateMonsterHideFromPoint : public CState<_Object> {
	typedef CState<_Object> inherited;

	SStateHideFromPoint data;

public:
						CStateMonsterHideFromPoint	(_Object *obj) : inherited(obj, &data){}
	~CStateMonsterHideFromPoint	() override {}

	void		initialize					() override;
	void		execute						() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}

	bool		check_completion			() override;
						
};

#include "state_hide_from_point_inline.h"