#pragma once
#include "../state.h"
#include "../../../../xrServerEntities/clsid_game.h"

template<typename _Object>
class	CStateBloodsuckerVampire : public CState<_Object> {
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	const CEntityAlive *enemy;

public:
						CStateBloodsuckerVampire		(_Object *obj);

	void		reinit							() override;

	void		initialize						() override;
	void		reselect_state					() override;
	void		finalize						() override;
	void		critical_finalize				() override;
	bool		check_start_conditions			() override;
	bool		check_completion				() override;
	void		remove_links					(CObject* object) override;

	void		setup_substates					() override;
	void		check_force_state				() override;
};

#include "bloodsucker_vampire_inline.h"
