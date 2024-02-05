#pragma once
#include "../monster_state_manager.h"

class CController;

class CStateManagerController : public CMonsterStateManager<CController> {

	typedef CMonsterStateManager<CController> inherited;

public:
						CStateManagerController			(CController *obj);
	~CStateManagerController		() override;

	void		reinit							() override;
	void		execute							() override;
	void		remove_links					(CObject* object) override { inherited::remove_links(object);}
	bool		check_control_start_conditions	(ControlCom::EControlType type) override;
};
