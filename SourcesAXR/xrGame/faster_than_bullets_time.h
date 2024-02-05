#ifndef FASTER_THAN_BULLETS_INCLUDED
#define FASTER_THAN_BULLETS_INCLUDED

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

	
class faster_than_bullets_time : public player_state_param
{
	typedef player_state_param inherited;
public:
						faster_than_bullets_time	(game_state_accumulator* owner);
	~faster_than_bullets_time	() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override;
	float const get_float_param				() override { return 0.0f; };
	void		reset_game					() override;

	void		OnPlayerKilled				(u16 killer_id, u16 target_id, u16 weapon_id, std::pair<KILL_TYPE, SPECIAL_KILL_TYPE> kill_type) override;
protected:
	u32					m_no_demag_time;
};//class faster_than_bullets_time

ADD_ACCUMULATIVE_STATE(acpv_faster_than_bullets_time, faster_than_bullets_time);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_faster_than_bullets_time, faster_than_bullets_time)

} //namespace award_system

#endif //#ifndef FASTER_THAN_BULLETS_INCLUDED