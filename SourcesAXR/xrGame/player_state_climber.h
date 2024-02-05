#ifndef PLAYER_STATE_CLIMBER_INCLUDED
#define PLAYER_STATE_CLIMBER_INCLUDED

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

class player_state_climber : public player_state_param
{
	typedef player_state_param inherited;
public:
						player_state_climber	(game_state_accumulator* owner);
						~player_state_climber	() override {};

	void		update				() override {};
	u32 const	get_u32_param		() override;
	float const get_float_param		() override { return 0.0f; };
	void		reset_game			() override { m_player_is_climber = false; };

	void		OnPlayerRankChanged	() override;
protected:
	bool				m_player_is_climber;
}; //class player_state_climber

ADD_ACCUMULATIVE_STATE(acpv_climber, player_state_climber);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_climber, player_state_climber)

} //namespace award_system

#endif //#ifndef PLAYER_STATE_CLIMBER_INCLUDED