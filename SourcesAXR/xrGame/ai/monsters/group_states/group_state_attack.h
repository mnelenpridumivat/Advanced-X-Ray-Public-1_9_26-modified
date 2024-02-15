#pragma once

#include "../state.h"
#include "../../../ai_debug.h"

template<typename _Object>
class	CStateGroupAttack : 
	public CState<_Object>,
	public IMetaClass
{
	DECLARE_METACLASS1(CStateGroupAttack, CState<_Object>)
public:
	CStateGroupAttack (_Object *obj);
	~CStateGroupAttack	() override;

	void		initialize			() override;
	void		execute				() override;
	void		setup_substates		() override;
	void		critical_finalize	() override;
	void		finalize		    () override;
	void		remove_links		(CObject* object) override;

protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	const CEntityAlive* m_enemy;
	u32					m_time_next_run_away;
	u32					m_time_start_check_behinder;
	u32					m_time_start_behinder;
	float				m_delta_distance;
	u32					m_time_start_drive_out;
	bool				m_drive_out;

protected:
	bool				check_home_point	();
	bool				check_behinder		();
};

#include "group_state_attack_inline.h"
