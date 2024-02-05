#pragma once
#include "../state.h"

template<typename _Object>
class CStateGroupEating : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;

	CEntityAlive	*corpse;
	u32				time_last_eat;

public:
	CStateGroupEating		(_Object *obj);
	~CStateGroupEating	() override;

	void		initialize				() override;
	void		execute					() override;

	bool		check_start_conditions	() override;
	bool		check_completion		() override;
	void		remove_links			(CObject* object) override;
};

#include "group_state_eat_eat_inline.h"
