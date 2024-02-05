#pragma once
#include "pseudodog_state_manager.h"

class CStateManagerPsyDog : public CStateManagerPseudodog {
	typedef CStateManagerPseudodog inherited;
public:
					CStateManagerPsyDog	(CAI_PseudoDog *monster);
	void	execute				() override;
	void	remove_links		(CObject* object) override { inherited::remove_links(object);}
};
