#ifndef PLAYER_STATE_BLITZKRIEG_INCLUDED
#define PLAYER_STATE_BLITZKRIEG_INCLUDED

#include "player_state_param.h"
#include "accumulative_states.h"

namespace award_system
{

class player_blitzkrieg : public player_state_param
{
	typedef player_state_param inherited;
public:
					player_blitzkrieg	(game_state_accumulator* owner);
	~player_blitzkrieg	() override {};

	void		update						() override {};
	u32 const	get_u32_param				() override;
	float const get_float_param				() override { return -1.0f; };
	void		reset_game					() override;

	void		OnPlayerTakeArtefact		(game_PlayerState const * ps) override;
	void		OnPlayerDropArtefact		(game_PlayerState const * ps) override;
	void		OnPlayerBringArtefact		(game_PlayerState const * ps) override;
protected:
	u32					m_deliver_time;
	u32					m_take_time;
	u32					m_art_drop_count;
};//class player_blitzkrieg

ADD_ACCUMULATIVE_STATE(acpv_blitzkrieg_time, player_blitzkrieg);
#undef ACCUMULATIVE_STATE_LIST
#define ACCUMULATIVE_STATE_LIST SAVE_TYPE_LIST(acpv_blitzkrieg_time, player_blitzkrieg)

} //namespace award_system

#endif //#ifndef PLAYER_STATE_BLITZKRIEG_INCLUDED