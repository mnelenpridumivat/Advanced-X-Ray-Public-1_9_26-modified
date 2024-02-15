#pragma once

#include "game_sv_deathmatch.h"

class	game_sv_TeamDeathmatch			: 
	public game_sv_Deathmatch,
	public IMetaClass
{
	DECLARE_METACLASS1(game_sv_TeamDeathmatch, game_sv_Deathmatch)
private:
	typedef game_sv_Deathmatch inherited;
	bool	teams_swaped;

protected:
	bool				checkForFragLimit		() override;
	bool				HasChampion				() override;

	void				ReadOptions				(shared_str &options) override;
	void				ConsoleCommands_Create	() override;
	void				ConsoleCommands_Clear	() override;

public:	
									game_sv_TeamDeathmatch	(){m_type = eGameIDTeamDeathmatch;}
	void				Create					(shared_str& options) override;

	void				OnEvent					(NET_Packet &tNetPacket, u16 type, u32 time, ClientID sender ) override;

	LPCSTR				type_name			() const override { return "teamdeathmatch";};

	void				Update					() override;
	void				net_Export_State		(NET_Packet& P, ClientID id_to) override;				// full state
	// Events	
	void				OnPlayerConnect			(ClientID id_who) override;
	void				OnPlayerConnectFinished	(ClientID id_who) override;

	void				OnPlayerSelectTeam		(NET_Packet& P, ClientID sender) override;
	virtual		void				OnPlayerChangeTeam		(ClientID id_who, s16 team);
	KILL_RES			GetKillResult			(game_PlayerState* pKiller, game_PlayerState* pVictim) override;
	bool				OnKillResult			(KILL_RES KillResult, game_PlayerState* pKiller, game_PlayerState* pVictim) override;
	void				OnPlayerKillPlayer		(game_PlayerState* ps_killer, game_PlayerState* ps_killed, KILL_TYPE KillType, SPECIAL_KILL_TYPE SpecialKillType, CSE_Abstract* pWeaponA) override;
	virtual		void				UpdateTeamScore			(game_PlayerState* ps_killer, s16 OldKills);
	bool				CheckTeams				() override { return true; };

	void				OnPlayerHitPlayer		(u16 id_hitter, u16 id_hitted, NET_Packet& P) override;
	void				OnPlayerHitPlayer_Case	(game_PlayerState* ps_hitter, game_PlayerState* ps_hitted, SHit* pHitS) override;

	void				OnRoundStart			() override;
	void				OnRoundEnd				() override;
	virtual		void				AutoBalanceTeams		();
	virtual		void				AutoSwapTeams			();

	virtual		u8					AutoTeam				( );
	virtual		u32					GetPlayersCountInTeams	(u8 team);
	virtual		bool				TeamSizeEqual			();
	u32					RP_2_Use				(CSE_Abstract* E) override;

	void				LoadTeams				() override;

	char*				GetAnomalySetBaseName	() override {return "teamdeathmatch_game_anomaly_sets";};
	BOOL				CanHaveFriendlyFire		() override {return TRUE;}
	void				OnFraglimitExceed		() override;
	void				OnTimelimitExceed		() override;

	BOOL				isFriendlyFireEnabled	() override;
	virtual		float				GetFriendlyFire			();

	virtual		BOOL				Get_AutoTeamBalance		();
	virtual		BOOL				Get_AutoTeamSwap		();
	virtual		BOOL				Get_FriendlyIndicators	();
	virtual		BOOL				Get_FriendlyNames		();

	virtual		int					Get_TeamKillLimit		();
	virtual		BOOL				Get_TeamKillPunishment	();

				BOOL				OnTouchItem(CSE_ActorMP *actor, CSE_Abstract *item);
				void				OnDetachItem(CSE_ActorMP *actor, CSE_Abstract *item);

	BOOL				OnTouch					(u16 eid_who, u16 eid_what, BOOL bForced = FALSE) override;
	void				OnDetach				(u16 eid_who, u16 eid_what) override;

				void				OnObjectEnterTeamBase	(u16 id, u16 zone_team);
				void				OnObjectLeaveTeamBase	(u16 id, u16 zone_team);
	void				RespawnPlayer			(ClientID id_who, bool NoSpectator) override;
protected:
	void				WriteGameState			(CInifile& ini, LPCSTR sect, bool bRoundResult) override;
};
