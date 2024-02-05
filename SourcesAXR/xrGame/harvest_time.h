#ifndef HARVEST_TIME_INCLUDED
#define HARVEST_TIME_INCLUDED

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

class harvest_time : public player_state_param
{
	typedef player_state_param inherited;
public:
						harvest_time		(game_state_accumulator* owner);
						~harvest_time		() override {};

	void		update				() override {};
	u32 const	get_u32_param		() override;
	float const get_float_param		() override { return 0.0f; };
	void		reset_game			() override;

	void		OnPlayerKilled		(u16 killer_id, u16 target_id, u16 weapon_id, std::pair<KILL_TYPE, SPECIAL_KILL_TYPE> kill_type) override;
	void		OnPlayerSpawned		(game_PlayerState const * ps) override;
protected:
	u32					m_harvest_count;
	u32					m_spawn_time;
}; //class harvest_time

ADD_ACCUMULATIVE_STATE(acpv_harvest_count, harvest_time);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_harvest_count, harvest_time)

} //namespace award_system

#endif //#ifndef HARVEST_TIME_INCLUDED