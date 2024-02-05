#pragma once

#include "../state.h"
#include "../../../entitycondition.h"
#include "../states/state_data.h"
template<typename _Object>
class	CStateGroupRest : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	u32					time_for_life;
	u32					time_for_sleep;

public:
						CStateGroupRest		(_Object *obj);
	~CStateGroupRest		() override;

	void		initialize				() override;
	void		execute					() override;
	void		finalize				() override;
	void		critical_finalize		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "group_state_rest_inline.h"