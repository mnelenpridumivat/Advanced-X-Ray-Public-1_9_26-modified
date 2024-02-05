#ifndef PLAYER_STATE_MARKSMAN
#define PLAYER_STATE_MARKSMAN

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

class player_state_marksman : public player_state_param
{
	typedef player_state_param inherited;
public:
						player_state_marksman		(game_state_accumulator* owner);
						~player_state_marksman		() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override;
	float const get_float_param				() override { return 0.0f; };
	void		reset_game					() override;

	void		OnPlayerKilled				(u16 killer_id, u16 target_id, u16 weapon_id, std::pair<KILL_TYPE, SPECIAL_KILL_TYPE> kill_type) override;
	void		OnPlayerSpawned				(game_PlayerState const * ps) override;
protected:

	static int const						max_kill_dist = 80;
	//data of the vector is float - kill distance - used only for debug.
	associative_vector<shared_str, float>	m_sniper_victims;
	u32										m_spawn_time;
}; //class player_state_marksman

ADD_ACCUMULATIVE_STATE(acpv_marksman_count, player_state_marksman);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_marksman_count, player_state_marksman)

} //namespace award_system

#endif //#ifndef PLAYER_STATE_MARKSMAN