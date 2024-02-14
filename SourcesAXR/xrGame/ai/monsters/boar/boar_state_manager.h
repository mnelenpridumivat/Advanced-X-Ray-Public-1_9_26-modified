#pragma once
#include "../monster_state_manager.h"

class CAI_Boar;

class CStateManagerBoar :
	public CMonsterStateManager<CAI_Boar>,
	public IMetaClass
{
	DECLARE_METACLASS1(CStateManagerBoar, CMonsterStateManager<CAI_Boar>)

	typedef CMonsterStateManager<CAI_Boar> inherited;

public:

					CStateManagerBoar	(CAI_Boar *monster);

	void	execute				() override;
	void	remove_links		(CObject* object) override { inherited::remove_links(object);}
};
