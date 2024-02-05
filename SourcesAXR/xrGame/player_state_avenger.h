#ifndef PLAYER_STATE_AVENGER
#define PLAYER_STATE_AVENGER

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

class player_state_avenger : public player_state_param
{
	typedef player_state_param inherited;
public:
						player_state_avenger		(game_state_accumulator* owner);
						~player_state_avenger		() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override { return m_aveng_count; };
	float const get_float_param				() override { return 0.0f; };
	void		reset_game					() override;

	void		OnPlayerKilled				(u16 killer_id, u16 target_id, u16 weapon_id, std::pair<KILL_TYPE, SPECIAL_KILL_TYPE> kill_type) override;
	void		OnPlayerSpawned				(game_PlayerState const * ps) override;
protected:
			void		feel_my_team_players		(game_PlayerState const * of_player, buffer_vector<shared_str> & dest);
	typedef	associative_vector<shared_str, u32>		player_spawn_times_t;
	player_spawn_times_t	m_player_spawns;
	u32						m_aveng_count;
}; //class player_state_avenger

ADD_ACCUMULATIVE_STATE(acpv_avenger, player_state_avenger);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_avenger, player_state_avenger)

} //namespace award_system

#endif //#ifndef PLAYER_STATE_AVENGER