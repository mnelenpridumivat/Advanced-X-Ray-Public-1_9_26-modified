#pragma once

#include "../state.h"

template<typename _Object>
class	CStateMonsterHearInterestingSound : 
	public CState<_Object>,
	public IMetaClass
{
	DECLARE_METACLASS1(CStateMonsterHearInterestingSound, CState<_Object>)
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

public:
					CStateMonsterHearInterestingSound	(_Object *obj);
	~CStateMonsterHearInterestingSound	() override {}

	void	reselect_state						() override;
	void	setup_substates						() override;
	void	remove_links						(CObject* object) override { inherited::remove_links(object);}

private:
			Fvector	get_target_position					();

};

#include "monster_state_hear_int_sound_inline.h"