#pragma once
#include "../state.h"

template<typename Object>
class	CStateAnomalPseudoGigantAttack : public CState<Object>
{
	typedef CState<Object> inherited;
	typedef CState<Object> *state_ptr;

public:
						CStateAnomalPseudoGigantAttack			(Object *obj);

	virtual	void		initialize					();
	virtual	void		execute						();
	virtual void		remove_links				(CObject* object) { inherited::remove_links(object); }

	virtual void		finalize					();
	virtual void		critical_finalize			();
	virtual void		setup_substates();

private:
	bool				m_wait_state_end;
	bool				m_lost_delta_health;
	bool				m_allow_anti_aim;
	float				m_last_health;
	TTime				m_next_runaway_allowed_tick;

	void				switch_original_states();

protected:

	u32					m_time_next_run_away;
	u32					m_time_start_check_behinder;
	u32					m_time_start_behinder;

	bool		check_steal_state();
	bool		check_find_enemy_state();
	bool		check_run_away_state();
	bool		check_run_attack_state();
	bool		check_camp_state();
	bool		check_home_point();
	bool		check_shield_state();
};

#include "anomal_pseudo_gigant_state_attack_inline.h"
