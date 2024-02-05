////////////////////////////////////////////////////////////////////////////
//	Module 		: script_action_planner_wrapper.h
//	Created 	: 19.03.2004
//  Modified 	: 26.03.2004
//	Author		: Dmitriy Iassenev
//	Description : Script action planner wrapper
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "action_planner.h"

class CScriptActionPlannerWrapper : public CScriptActionPlanner, public luabind::wrap_base {
public:
	void		setup						(CScriptGameObject *object) override;
	static	void		setup_static				(CScriptActionPlanner *planner, CScriptGameObject *object);
	void		update						() override;
	static	void		update_static				(CScriptActionPlanner *planner);
};

#include "script_action_planner_wrapper_inline.h"