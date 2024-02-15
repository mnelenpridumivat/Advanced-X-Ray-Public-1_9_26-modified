#pragma once

#include "../state.h"

template<typename _Object>
class	CStateGroupPanic : 
	public CState<_Object>,
	public IMetaClass
{
	DECLARE_METACLASS1(CStateGroupPanic, CState<_Object>)
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;
	
public:
						CStateGroupPanic		(_Object *obj);
	~CStateGroupPanic		() override;

	void		initialize				() override;
	void		reselect_state			() override;
	void		check_force_state		() override;
	void		setup_substates			() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "group_state_panic_inline.h"
