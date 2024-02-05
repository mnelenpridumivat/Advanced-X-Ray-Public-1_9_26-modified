#pragma once
#include "../state.h"

template<typename _Object>
class CStateBurerAttackGravi : public CState<_Object> {
	typedef CState<_Object> inherited;	
public:
							CStateBurerAttackGravi	(_Object *obj);

	void		initialize				() override;
	void		execute					() override;
	void		finalize				() override;
	void		critical_finalize		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	bool		check_start_conditions	() override;
	bool		check_completion		() override;

private:
				// выполнять состояние
				void		ExecuteGraviStart		();
				void		ExecuteGraviContinue	();
				void		ExecuteGraviFire		();

private:
	enum 
	{
		ACTION_GRAVI_STARTED,
		ACTION_GRAVI_CONTINUE,
		ACTION_GRAVI_FIRE,
		ACTION_WAIT_ANIM_END,
		ACTION_COMPLETED,

	}						m_action;

	u32						m_time_gravi_started;
	TTime					m_next_gravi_allowed_tick;
	TTime					m_anim_end_tick;
};

#include "burer_state_attack_gravi_inline.h"

