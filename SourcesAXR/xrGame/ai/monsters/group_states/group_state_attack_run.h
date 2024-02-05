#pragma once

#include "../state.h"

template<typename _Object>
class CStateGroupAttackRun : public CState<_Object> {
	typedef CState<_Object> inherited;

	TTime				m_time_path_rebuild;
	
	TTime               m_next_encircle_tick;
	TTime               m_encircle_time;
	Fvector             m_encircle_dir;

	TTime               m_intercept_tick;
	TTime               m_intercept_length;
	Fvector             m_intercept;

	TTime               m_memorized_tick;
	Fvector             m_memorized_pos;
	Fvector             m_predicted_vel;

public:
	IC					CStateGroupAttackRun	(_Object *obj);

	void		initialize				() override;
	void		execute					() override;
	void		finalize				() override;
	void		critical_finalize		() override;

	bool 		check_completion		() override;
	bool 		check_start_conditions	() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "group_state_attack_run_inline.h"
