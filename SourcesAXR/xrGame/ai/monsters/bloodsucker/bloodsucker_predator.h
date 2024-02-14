#pragma once
#include "../state.h"

template<typename _Object>
class	CStateBloodsuckerPredator :
	public CState<_Object>,
	public IMetaClass
{
	DECLARE_METACLASS1(CStateBloodsuckerPredator, CState<_Object>)

	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	u32							m_target_node;
	u32							m_time_start_camp;

public:
						CStateBloodsuckerPredator		(_Object *obj);

	void		reinit							() override;

	void		initialize						() override;
	void		reselect_state					() override;
	void		finalize						() override;
	void		critical_finalize				() override;
	bool		check_start_conditions			() override;
	bool		check_completion				() override;
	void		remove_links					(CObject* object) override { inherited::remove_links(object);}

	void		setup_substates					() override;
	void		check_force_state				() override;

private:
			void		select_camp_point				();
};

#include "bloodsucker_predator_inline.h"