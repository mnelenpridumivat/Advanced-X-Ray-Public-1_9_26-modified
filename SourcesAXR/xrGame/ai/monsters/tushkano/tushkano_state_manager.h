#pragma once
#include "../monster_state_manager.h"

class CTushkano;

class CStateManagerTushkano : public CMonsterStateManager<CTushkano> {
	typedef CMonsterStateManager<CTushkano> inherited;

public:
						CStateManagerTushkano	(CTushkano *obj);
	~CStateManagerTushkano	() override;

	void		execute					() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};
