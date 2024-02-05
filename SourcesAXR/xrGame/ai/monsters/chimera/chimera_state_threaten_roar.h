#pragma once
#include "../state.h"

template<typename _Object>
class CStateChimeraThreatenRoar : public CState<_Object> {
	typedef CState<_Object>		inherited;

public:
	IC					CStateChimeraThreatenRoar	(_Object *obj) : inherited(obj){}

	void		initialize					() override;
	void		execute						() override;
	bool		check_completion			() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "chimera_state_threaten_roar_inline.h"
