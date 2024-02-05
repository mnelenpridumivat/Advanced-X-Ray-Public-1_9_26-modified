#ifndef PLAYER_STATE_SKEWER_INCLUDED
#define PLAYER_STATE_SKEWER_INCLUDED

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

class player_state_skewer : public player_state_param
{
	typedef player_state_param inherited;
public:
						player_state_skewer		(game_state_accumulator* owner);
	~player_state_skewer	() override {};

	void		update					() override {};
	u32 const	get_u32_param			() override;
	float const get_float_param			() override { return 0.0f; };
	void		reset_game				() override;

	void		OnWeapon_Fire			(u16 sender, u16 sender_weapon_id) override;
	void		OnPlayerKilled			(u16 killer_id, u16 target_id, u16 weapon_id, std::pair<KILL_TYPE, SPECIAL_KILL_TYPE> kill_type) override;
protected:
	u32					m_shot;
	u32					m_kills_count;
};//class player_state_skewer

ADD_ACCUMULATIVE_STATE(acpv_skewer_count, player_state_skewer);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_skewer_count, player_state_skewer)

}//namespace award_system

#endif //#ifndef PLAYER_STATE_SKEWER_INCLUDED
