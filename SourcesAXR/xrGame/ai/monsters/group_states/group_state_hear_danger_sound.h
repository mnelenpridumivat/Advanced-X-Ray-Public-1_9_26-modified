#pragma once

#include "../state.h"

template<typename _Object>
class	CStateGroupHearDangerousSound : 
	public CState<_Object>,
	public IMetaClass
{
	DECLARE_METACLASS1(CStateGroupHearDangerousSound, CState<_Object>)
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	u32				m_target_node;


public:
	CStateGroupHearDangerousSound		(_Object *obj);
	~CStateGroupHearDangerousSound	() override {}

	void	initialize						() override;
	void	reselect_state					() override;
	void	setup_substates					() override;
	void	remove_links					(CObject* object) override { inherited::remove_links(object);}
};

#include "group_state_hear_danger_sound_inline.h"