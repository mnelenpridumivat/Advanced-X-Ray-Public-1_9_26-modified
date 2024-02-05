#pragma once

#include "../state.h"

template<typename _Object>
class	CStateCustomGroup : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

public:
	CStateCustomGroup		(_Object *obj);
	~CStateCustomGroup		() override;

	void		execute					() override;
	void		setup_substates			() override;
	bool 		check_completion		() override {return (object->b_state_end);}
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "group_state_custom_inline.h"