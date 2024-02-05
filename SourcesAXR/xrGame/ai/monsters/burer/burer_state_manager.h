#pragma once
#include "../monster_state_manager.h"

class CBurer;

class CStateManagerBurer : public CMonsterStateManager<CBurer> {
	typedef CMonsterStateManager<CBurer> inherited;
public:
					CStateManagerBurer		(CBurer *monster);
	void	execute					() override;
	void	setup_substates			() override;
	void	remove_links			(CObject* object) override { inherited::remove_links(object);}
};

