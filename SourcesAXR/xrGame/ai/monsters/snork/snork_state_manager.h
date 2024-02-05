#pragma once
#include "../monster_state_manager.h"

class CSnork;

class CStateManagerSnork : public CMonsterStateManager<CSnork> 
{
private:
	typedef				CMonsterStateManager<CSnork>	inherited;

public:
						CStateManagerSnork		(CSnork *obj);
	~CStateManagerSnork		() override;

	void		execute					() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};
