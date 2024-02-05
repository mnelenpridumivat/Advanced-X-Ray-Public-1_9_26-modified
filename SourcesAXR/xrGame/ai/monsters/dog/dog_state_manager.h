#pragma once
#include "../monster_state_manager.h"

class CAI_Dog;

class CStateManagerDog : public CMonsterStateManager<CAI_Dog> {
	typedef CMonsterStateManager<CAI_Dog> inherited;

public:

					CStateManagerDog	(CAI_Dog *monster);
	void	execute				() override;
			bool	check_eat			();
	void	remove_links		(CObject* object) override { inherited::remove_links(object);}
};
