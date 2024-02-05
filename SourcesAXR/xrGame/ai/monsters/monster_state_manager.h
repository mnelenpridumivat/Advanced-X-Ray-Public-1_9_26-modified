#pragma once
#include "state_manager.h"
#include "state.h"

// Lain: added
#ifdef DEBUG
#include "debug_text_tree.h"
#endif

template <typename _Object>
class CMonsterStateManager : public IStateManagerBase, public CState<_Object> {
	typedef CState<_Object> inherited;

public:
					CMonsterStateManager	(_Object *obj) : inherited(obj) {}
	void	reinit					() override;
	void	update					() override;
	void	force_script_state		(EMonsterState state) override;
	void	execute_script_state	() override;
	void	critical_finalize		() override;
	void	remove_links			(CObject* object) override = 0 { inherited::remove_links(object); }

	EMonsterState get_state_type	() override;

	bool	check_control_start_conditions (ControlCom::EControlType type) override
	{ return inherited::check_control_start_conditions(type); }

	// Lain: added
	#ifdef DEBUG
	void    add_debug_info          (debug::text_tree& root_s) override;
	#endif

protected:
			bool	can_eat					();
			bool	check_state				(u32 state_id);
};

#include "monster_state_manager_inline.h"