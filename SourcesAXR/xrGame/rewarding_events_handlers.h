#ifndef REWARDING_EVENTS_HANDLERS_INCLUDED
#define REWARDING_EVENTS_HANDLERS_INCLUDED

#include "event_conditions_collection.h" //for event_action_delegate_t
#include "game_cl_base_weapon_usage_statistic.h"
#include "../xrServerEntities/associative_vector.h"
#include "game_events_handler.h"

namespace award_system
{

class reward_event_handler;

class rewarding_event_handlers : public game_events_handler
{
public:
			rewarding_event_handlers	(game_state_accumulator* pstate_accum,
										 event_action_delegate_t ea_delegate);
			~rewarding_event_handlers	() override;

	void	init						();
	void	set_null_handler			(reward_event_handler* new_handler);

			void	OnWeapon_Fire				(u16 sender, u16 sender_weapon_id) override;
			void	OnBullet_Fire				(u16 sender, u16 sender_weapon_id, const Fvector& position, const Fvector& direction) override;
			void	OnBullet_Hit				(CObject const * hitter, CObject const * victim, CObject const * weapon, u16 const bone) override;
			void	OnArtefactSpawned			() override;
			void	OnPlayerTakeArtefact		(game_PlayerState const * ps) override;
			void	OnPlayerDropArtefact		(game_PlayerState const * ps) override;
			void	OnPlayerBringArtefact		(game_PlayerState const * ps) override;
			void	OnPlayerSpawned				(game_PlayerState const * ps) override;
			void	OnPlayerKilled				(u16 killer_id, u16 target_id, u16 weapon_id, std::pair<KILL_TYPE, SPECIAL_KILL_TYPE> kill_type) override;
			void	OnPlayerChangeTeam			(s8 team) override;
			void	OnPlayerRankChanged			() override;
			void	OnRoundEnd					() override;
			void	OnRoundStart				() override;
private:
	typedef associative_vector<u32, reward_event_handler*>	handlers_store_t;

	handlers_store_t					m_events_store;
	event_action_delegate_t				m_reward_action;
	game_state_accumulator*				m_player_state_accum;
	reward_event_handler*				m_null_hanlder;
}; //class rewarding_event_handlers


} //namespace award_system


#endif //#ifndef REWARDING_EVENTS_HANDLERS_INCLUDED