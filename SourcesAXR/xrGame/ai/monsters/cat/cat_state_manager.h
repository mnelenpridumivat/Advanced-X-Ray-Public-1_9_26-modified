#pragma once
#include "../monster_state_manager.h"

class CCat;

class CStateManagerCat : public CMonsterStateManager<CCat> {

	typedef CMonsterStateManager<CCat> inherited;

	u32					m_rot_jump_last_time;

public:
						CStateManagerCat	(CCat *obj);
	~CStateManagerCat	() override;

	void		execute				() override;
	void		remove_links		(CObject* object) override { inherited::remove_links(object);}
};
