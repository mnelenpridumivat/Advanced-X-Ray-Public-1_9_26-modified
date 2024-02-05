#pragma once

template<typename _Object>
class CStateGroupPanicRun : public CState<_Object> {
	typedef CState<_Object> inherited;

public:
						CStateGroupPanicRun	(_Object *obj) : inherited(obj) {}
	~CStateGroupPanicRun	() override {}

	void		initialize				() override;
	void		execute					() override;

	bool		check_completion		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "group_state_panic_run_inline.h"
