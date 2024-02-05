#pragma once
#include "../monster_state_manager.h"

class CFracture;

class CStateManagerFracture : public CMonsterStateManager<CFracture> {
	typedef CMonsterStateManager<CFracture> inherited;

public:
						CStateManagerFracture	(CFracture *obj);
	~CStateManagerFracture	() override;

	void		execute					() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};
