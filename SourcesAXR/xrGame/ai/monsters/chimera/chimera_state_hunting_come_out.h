#pragma once
#include "../state.h"

template<typename _Object>
class	CStateChimeraHuntingComeOut : public CState<_Object> {
protected:
	typedef CState<_Object> inherited;

public:
						CStateChimeraHuntingComeOut	(_Object *obj);

	void		reselect_state				() override;
	bool 		check_start_conditions		() override;
	bool 		check_completion			() override;	

};

#include "chimera_state_hunting_come_out_inline.h"
