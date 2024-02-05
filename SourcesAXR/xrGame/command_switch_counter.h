#ifndef COMMAND_SWITCH_COUNTER_INCLUDED
#define COMMAND_SWITCH_COUNTER_INCLUDED

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

class command_switch_counter : public player_state_param
{
	typedef player_state_param inherited;
public:
						command_switch_counter		(game_state_accumulator* owner) : inherited(owner) { m_counter = 0; };
	~command_switch_counter		() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override { return m_counter; };
	float const get_float_param				() override { return 0.0f; };
	void		reset_game					() override { m_counter = 0; };
	void		OnPlayerChangeTeam			(s8 team) override { ++m_counter; };
private:
	u32					m_counter;
};// class command_switch_counter

ADD_ACCUMULATIVE_STATE(acpv_command_switch_count, command_switch_counter);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_command_switch_count, command_switch_counter)

} //namespace award_system


#endif //#ifndef COMMAND_SWITCH_COUNTER_INCLUDED