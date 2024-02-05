#pragma once

template<typename _Object>
class CStateMonsterPanicRun : public CState<_Object> {
	typedef CState<_Object> inherited;

public:
						CStateMonsterPanicRun	(_Object *obj) : inherited(obj) {}
	~CStateMonsterPanicRun	() override {}

	void		initialize				() override;
	void		execute					() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	bool		check_completion		() override;
};

#include "monster_state_panic_run_inline.h"
