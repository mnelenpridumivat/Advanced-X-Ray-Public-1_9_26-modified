#pragma once
#include "../monster_state_manager.h"

class CZombie;

class CStateManagerZombie : public CMonsterStateManager<CZombie> {
	typedef CMonsterStateManager<CZombie> inherited;

public:
						CStateManagerZombie		(CZombie *obj);
	~CStateManagerZombie	() override;

	void		execute					() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};
