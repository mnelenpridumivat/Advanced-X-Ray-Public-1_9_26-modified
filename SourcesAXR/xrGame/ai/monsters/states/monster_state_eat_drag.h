#pragma once

template<typename _Object>
class CStateMonsterDrag : public CState<_Object> {
	typedef CState<_Object>		inherited;

	Fvector				m_cover_position;
	u32					m_cover_vertex_id;
	
	bool				m_failed;
	Fvector				m_corpse_start_position;

public:
						CStateMonsterDrag		(_Object *obj);
	~CStateMonsterDrag		() override;

	void		initialize				() override;
	void		execute					() override;
	void		finalize				() override;
	void		critical_finalize		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	bool		check_completion		() override;
};


#include "monster_state_eat_drag_inline.h"