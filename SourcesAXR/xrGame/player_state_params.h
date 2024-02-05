#ifndef DEATH_COUNT_INCLUDED
#define DEATH_COUNT_INCLUDED

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

class player_death_counter : public player_state_param
{
	typedef	player_state_param inherited;
public:
						player_death_counter		(game_state_accumulator* owner);
	~player_death_counter		() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override;
	float const get_float_param				() override { return -1.0f; };
	void		reset_game					() override {};
};//class player_death_counter

ADD_ACCUMULATIVE_STATE(acpv_death_count, player_death_counter);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_death_count, player_death_counter)

class player_artdeliver_counter : public player_state_param
{
	typedef player_state_param inherited;
public:
						player_artdeliver_counter	(game_state_accumulator* owner);
	~player_artdeliver_counter	() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override;
	float const get_float_param				() override { return 0.0f; };
	void		reset_game					() override {};
}; //class player_artdeliver_counter

ADD_ACCUMULATIVE_STATE(acpv_artdeliver_count, player_artdeliver_counter);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_artdeliver_count, player_artdeliver_counter)


class player_rawkill_counter : public player_state_param
{
	typedef player_state_param inherited;
public:
						player_rawkill_counter		(game_state_accumulator* owner);
	~player_rawkill_counter		() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override;
	float const get_float_param				() override { return 0.0f; };
	void		reset_game					() override;

	void		OnPlayerSpawned				(game_PlayerState const * ps) override;
	void		OnPlayerKilled				(u16 killer_id, u16 target_id, u16 weapon_id, std::pair<KILL_TYPE, SPECIAL_KILL_TYPE> kill_type) override;
protected:
	u32					m_raw_kills;
}; //class player_rawkill_counter

ADD_ACCUMULATIVE_STATE(acpv_kill_in_raw, player_rawkill_counter);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_kill_in_raw, player_rawkill_counter)

class player_state_move : public player_state_param
{
	typedef player_state_param inherited;
public:
						player_state_move	(game_state_accumulator* owner);
	~player_state_move	() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override;
	float const get_float_param				() override { return 0.0f; };
	void		reset_game					() override {};
}; //class player_state_move

ADD_ACCUMULATIVE_STATE(acpv_move_state, player_state_move);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_move_state, player_state_move)

class player_state_velocity : public player_state_param
{
	typedef player_state_param inherited;
public:
						player_state_velocity	(game_state_accumulator* owner);
	~player_state_velocity	() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override { return 0; }
	float const get_float_param				() override;
	void		reset_game					() override {};
}; //class player_state_velocity

ADD_ACCUMULATIVE_STATE(acpv_move_velocity, player_state_velocity);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_move_velocity, player_state_velocity)

class player_state_ang_velocity : public player_state_param
{
	typedef player_state_param inherited;
public:
						player_state_ang_velocity	(game_state_accumulator* owner);
	~player_state_ang_velocity	() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override { return 0; }
	float const get_float_param				() override;
	void		reset_game					() override {};
}; //class player_state_ang_velocity

ADD_ACCUMULATIVE_STATE(acpv_move_ang_velocity, player_state_ang_velocity);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_move_ang_velocity, player_state_ang_velocity)

} //namespace award_system

#endif //#ifndef DEATH_COUNT_INCLUDED