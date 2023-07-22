#pragma once
#include "../monster_state_manager.h"

class CAnomalPseudoGigant;

class CStateManagerAnomalPseudoGigant : public CMonsterStateManager<CAnomalPseudoGigant> {
	typedef CMonsterStateManager<CAnomalPseudoGigant> inherited;
public:
					CStateManagerAnomalPseudoGigant(CAnomalPseudoGigant* monster);
	virtual void	execute					();
	virtual void	setup_substates			();
	virtual void	remove_links			(CObject* object) { inherited::remove_links(object);}
};

