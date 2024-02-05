#pragma once
#include "../state.h"

template<typename _Object>
class	CStateChimeraThreaten : public CState<_Object> {
protected:
	typedef CState<_Object> inherited;
	typedef CState<_Object>* state_ptr;

	enum {
		eStateWalk			= static_cast<u32>(0),
		eStateFaceEnemy,
		eStateThreaten,
		eStateSteal
	};

	u32					m_last_time_threaten;

public:
						CStateChimeraThreaten	(_Object *obj);
	~CStateChimeraThreaten	() override;

	void		reinit					() override;

	void		initialize				() override;

	void		reselect_state			() override;
	void 		finalize				() override;
	void 		critical_finalize		() override;
	bool 		check_start_conditions	() override;
	bool 		check_completion		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "chimera_state_threaten_inline.h"
