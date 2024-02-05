#pragma once
#include "../state.h"

template<typename _Object>
class	CStateChimeraHuntingMoveToCover : public CState<_Object> {
protected:
	typedef CState<_Object> inherited;

public:
						CStateChimeraHuntingMoveToCover	(_Object *obj);

	void		initialize						() override;
	void		execute							() override;
	bool 		check_start_conditions			() override;
	bool 		check_completion				() override;
};

#include "chimera_state_hunting_move_to_cover_inline.h"
