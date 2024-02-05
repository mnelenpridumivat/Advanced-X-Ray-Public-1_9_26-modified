#ifndef PLAYER_STATE_AMMO_ELAPSED_INCLUDED
#define PLAYER_STATE_AMMO_ELAPSED_INCLUDED

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

class player_state_ammo_elapsed : public player_state_param
{
	typedef	player_state_param inherited;
public:
						player_state_ammo_elapsed		(game_state_accumulator* owner);
	~player_state_ammo_elapsed		() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override;
	float const get_float_param				() override { return 0.0f; };
	void		reset_game					() override {};
};//class player_state_ammo_elapsed

ADD_ACCUMULATIVE_STATE(acpv_ammo_elapsed, player_state_ammo_elapsed);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_ammo_elapsed, player_state_ammo_elapsed)

} //namespace award_system

#endif //#ifndef PLAYER_STATE_AMMO_ELAPSED_INCLUDED