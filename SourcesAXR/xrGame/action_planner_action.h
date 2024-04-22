////////////////////////////////////////////////////////////////////////////
//	Module 		: action_planner_action.h
//	Created 	: 28.01.2004
//  Modified 	: 10.03.2004
//	Author		: Dmitriy Iassenev
//	Description : Action planner action
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "action_base.h"
#include "action_planner.h"
#include "script_export_space.h"

class CScriptGameObject;

template <typename _object_type>
class CActionPlannerAction : 
	public CActionPlanner<_object_type>,
	public CActionBase<_object_type>
{
protected:
	typedef	CActionPlanner<_object_type>					inherited_planner;
	typedef	CActionBase<_object_type>						inherited_action;
	typedef typename inherited_action::_edge_value_type		_edge_value_type;
	typedef typename inherited_action::_condition_type		_condition_type;
	typedef typename inherited_action::_value_type			_value_type;
	typedef typename inherited_planner::_world_operator _world_operator;
	using _action_id_type = typename inherited_planner::_action_id_type;

public:
	typedef typename inherited_action::COperatorCondition	COperatorCondition;

#ifdef LOG_ACTION
public:
	void		set_use_log				(bool value) override;
	void		show					(LPCSTR offset = "") override;
#endif

public:
	IC					CActionPlannerAction	(_object_type *object = nullptr, LPCSTR action_name = "");
	~CActionPlannerAction	() override;
	virtual void		setup					(_object_type *object, CPropertyStorage *storage) override;
	void		initialize				() override;
	void		execute					() override;
	void		finalize				() override;
	virtual bool		completed				() const;
	IC		void		add_condition			(_world_operator *action, _condition_type condition_id, _value_type condition_value);
	IC		void		add_effect				(_world_operator *action, _condition_type condition_id, _value_type condition_value);

	void		save					(NET_Packet &packet) override
	{inherited_planner::save(packet); inherited_action::save(packet);}

	void		load					(IReader &packet) override
	{inherited_planner::load(packet); inherited_action::load(packet);}

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
typedef CActionPlannerAction<CScriptGameObject> CScriptActionPlannerAction;
add_to_type_list(CScriptActionPlannerAction)
#undef script_type_list
#define script_type_list save_type_list(CScriptActionPlannerAction)

#include "action_planner_action_inline.h"