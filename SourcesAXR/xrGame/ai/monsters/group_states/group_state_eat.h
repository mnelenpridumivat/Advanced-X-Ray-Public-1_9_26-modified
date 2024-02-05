#pragma once

#include "../state.h"

template<typename _Object>
class	CStateGroupEat : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	const CEntityAlive			*corpse;

	u32							m_time_last_eat;

public:
	CStateGroupEat		(_Object *obj);
	~CStateGroupEat		() override;

	void		reinit					() override;
	void		initialize				() override;
	void		finalize				() override;
	void		critical_finalize		() override;
	void		remove_links			(CObject* object) override;

	void		reselect_state			() override;
	void		setup_substates			() override;
	bool		check_completion		() override;
	bool		check_start_conditions	() override;

private:

			bool		hungry					();
};

#include "group_state_eat_inline.h"