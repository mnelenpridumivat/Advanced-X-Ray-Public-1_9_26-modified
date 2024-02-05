#ifndef PLAYER_STATE_AMBASSADOR_INCLUDED
#define PLAYER_STATE_AMBASSADOR_INCLUDED

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

class player_state_ambassador : public player_state_param
{
	typedef player_state_param inherited;
public:
					player_state_ambassador		(game_state_accumulator* owner);
	~player_state_ambassador	() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override;
	float const get_float_param				() override { return -1.0f; };
	void		reset_game					() override;

	void		OnWeapon_Fire				(u16 sender, u16 sender_weapon_id) override;
	void		OnPlayerTakeArtefact		(game_PlayerState const * ps) override;
	void		OnPlayerDropArtefact		(game_PlayerState const * ps) override;
	void		OnPlayerBringArtefact		(game_PlayerState const * ps) override;
protected:
	u32					m_shots_count;
	u32					m_art_drop_count;
	bool				m_delivered;
};//class player_state_ambassador

ADD_ACCUMULATIVE_STATE(acpv_ambassador, player_state_ambassador);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_ambassador, player_state_ambassador)

} //namespace award_system

#endif //#ifndef PLAYER_STATE_AMBASSADOR_INCLUDED