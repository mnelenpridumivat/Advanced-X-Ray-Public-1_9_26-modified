#pragma once
#include "../state.h"
#include "state_data.h"

template<typename _Object>
class CStateMonsterCustomActionLook : public CState<_Object> {
	typedef CState<_Object> inherited;

	SStateDataActionLook	data;

public:
						CStateMonsterCustomActionLook	(_Object *obj);
	~CStateMonsterCustomActionLook	() override;

	void		execute						() override;
	bool		check_completion			() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "state_custom_action_look_inline.h"