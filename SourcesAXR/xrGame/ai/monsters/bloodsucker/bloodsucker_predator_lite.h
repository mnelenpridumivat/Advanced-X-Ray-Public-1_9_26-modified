#pragma once
#include "../state.h"

template<typename _Object>
class	CStateBloodsuckerPredatorLite : public CState<_Object> {
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	u32							m_target_node;
	bool						m_freezed;

public:
						CStateBloodsuckerPredatorLite		(_Object *obj);

	void		reinit							() override;

	void		initialize						() override;
	void		reselect_state					() override;
	void		finalize						() override;
	void		critical_finalize				() override;
	bool		check_completion				() override;

	void		setup_substates					() override;
	void		check_force_state				() override;

private:
			void		select_camp_point				();
			bool		enemy_see_me					();

};

#include "bloodsucker_predator_lite_inline.h"