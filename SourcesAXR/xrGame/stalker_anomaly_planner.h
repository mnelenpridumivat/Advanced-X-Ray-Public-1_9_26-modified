////////////////////////////////////////////////////////////////////////////
//	Module 		: stalker_anomaly_planner.h
//	Created 	: 25.03.2004
//  Modified 	: 27.09.2004
//	Author		: Dmitriy Iassenev
//	Description : Stalker anomaly planner
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "action_planner_action_script.h"

class CAI_Stalker;

class CStalkerAnomalyPlanner : public CActionPlannerActionScript<CAI_Stalker> {
private:
	typedef CActionPlannerActionScript<CAI_Stalker> inherited;

public:
						CStalkerAnomalyPlanner	(CAI_Stalker *object = nullptr, LPCSTR action_name = "");
	~CStalkerAnomalyPlanner	() override;
	virtual	void		setup					(CAI_Stalker *object, CPropertyStorage *storage);
	void		update					() override;
			void		add_evaluators			();
			void		add_actions				();
};
