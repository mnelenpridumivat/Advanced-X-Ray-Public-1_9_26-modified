#pragma once
#include "../monster_state_manager.h"

class CAI_Bloodsucker;

class CStateManagerBloodsucker : public CMonsterStateManager<CAI_Bloodsucker> {
	typedef CMonsterStateManager<CAI_Bloodsucker> inherited;

public:
					CStateManagerBloodsucker	(CAI_Bloodsucker *monster);
	void	execute						() override;
	void	update						() override;
			void	drag_object					();
	void	remove_links				(CObject* object) override { inherited::remove_links(object);}
			bool	check_vampire				();
};
