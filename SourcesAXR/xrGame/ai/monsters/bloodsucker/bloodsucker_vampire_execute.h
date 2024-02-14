#pragma once
#include "../state.h"

template<typename _Object>
class	CStateBloodsuckerVampireExecute :
	public CState<_Object>,
	public IMetaClass
{
	DECLARE_METACLASS1(CStateBloodsuckerVampireExecute, CState<_Object>)

	typedef CState<_Object>		inherited;

	enum {
		eActionPrepare,
		eActionContinue,
		eActionFire,
		eActionWaitTripleEnd,
		eActionCompleted
	} m_action;

	u32					time_vampire_started;
	
	bool				m_effector_activated;

public:
						CStateBloodsuckerVampireExecute	(_Object *obj) : inherited(obj) {}

	void		initialize						() override;
	void		execute							() override;
	void		finalize						() override;
	void		critical_finalize				() override;
	bool		check_start_conditions			() override;
	bool		check_completion				() override;
	void		remove_links					(CObject* object) override { inherited::remove_links(object);}

private:
			void		execute_vampire_prepare			();
			void		execute_vampire_continue		();
			void		execute_vampire_hit				();

			void		look_head						();
			void		show_hud						();
			void		cleanup							();
};

#include "bloodsucker_vampire_execute_inline.h"
