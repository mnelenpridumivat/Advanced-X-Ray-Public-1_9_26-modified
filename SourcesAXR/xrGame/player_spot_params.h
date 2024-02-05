#ifndef PLAYER_SPOT_PARAMS_INCLUDED
#define PLAYER_SPOT_PARAMS_INCLUDED

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

extern u32 const calculate_spots(game_PlayerState* ps);

class player_spots_counter : public player_state_param
{
	typedef player_state_param inherited;
public:
						player_spots_counter		(game_state_accumulator* owner);
	~player_spots_counter		() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override;
	float const get_float_param				() override { return 0.0f; };
	void		reset_game					() override {};
};//class player_spots_counter

ADD_ACCUMULATIVE_STATE(acpv_spots, player_spots_counter);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_spots, player_spots_counter)

class player_spots_with_top_enemy_divider : public player_spots_counter
{
	typedef player_spots_counter inherited;
public:
						player_spots_with_top_enemy_divider		(game_state_accumulator* owner) : inherited(owner) {};
	~player_spots_with_top_enemy_divider	() override {};
	u32 const	get_u32_param							() override { return 0; };
	float const get_float_param							() override;
private:
	u32 const			get_top_enemy_player_score				();
}; //player_spots_with_top_enemy_divider

ADD_ACCUMULATIVE_STATE(acpv_enemy_top_player_div, player_spots_with_top_enemy_divider);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_enemy_top_player_div, player_spots_with_top_enemy_divider)

}//namespace award_system


#endif //#ifndef PLAYER_SPOT_PARAMS_INCLUDED