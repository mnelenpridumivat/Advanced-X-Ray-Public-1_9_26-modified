#pragma once

#include "../state.h"

template<typename _Object>
class	CStateMonsterHearHelpSound : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

public:
					CStateMonsterHearHelpSound	(_Object *obj);
	~CStateMonsterHearHelpSound	() override {}

	void	reselect_state				() override;
	void	setup_substates				() override;

	bool	check_start_conditions		() override;
	bool	check_completion			() override;

	void	remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_help_sound_inline.h"