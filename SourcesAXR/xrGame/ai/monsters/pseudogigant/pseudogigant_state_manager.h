#pragma once
#include "../monster_state_manager.h"

class CPseudoGigant;

class CStateManagerGigant : public CMonsterStateManager<CPseudoGigant> {
	typedef CMonsterStateManager<CPseudoGigant> inherited;
public:

					CStateManagerGigant	(CPseudoGigant *monster);
	void	execute				() override;
	void	remove_links		(CObject* object) override { inherited::remove_links(object);}
};
