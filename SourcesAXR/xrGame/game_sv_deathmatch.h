#pragma once

#include "game_sv_mp.h"
#include "inventory_space.h"
#include "../xrCore/client_id.h"
#include "Hit.h"
#include "../xrEngine/pure_relcase.h"

class IClient;

class	game_sv_Deathmatch			: 
	public game_sv_mp,
	private pure_relcase,
	public IMetaClass
{
	DECLARE_METACLASS2(game_sv_Deathmatch, game_sv_mp, pure_relcase)
	typedef game_sv_mp inherited;
protected:
	struct		RPointData
	{
		u32		PointID;
		float	MinEnemyDist;
		bool	bFreezed;

		RPointData(u32 ID, float Dist, bool Freezed):
		PointID(ID),MinEnemyDist(Dist), bFreezed(Freezed){};
		IC	bool operator<(const RPointData &x) const
		{
			if (bFreezed && !x.bFreezed) return false;
			if (!bFreezed && x.bFreezed) return true;
			return MinEnemyDist < x.MinEnemyDist;
		};
	};
	xr_vector<u32>					m_vFreeRPoints[TEAM_COUNT];
	u32								m_dwLastRPoints[TEAM_COUNT];

	BOOL							m_delayedRoundEnd;
	u32								m_roundEndDelay;

	BOOL							m_delayedTeamEliminated;
	u32								m_TeamEliminatedDelay;

	shared_str							m_sBaseWeaponCostSection;
		
	xr_vector<game_TeamState>		teams;//dm,tdm,ah	

	LPCSTR							pWinnigPlayerName;

	void				ReadOptions				(shared_str &options) override;
	void				ConsoleCommands_Create	() override;
	void				ConsoleCommands_Clear	() override;
	/////////////////////////////////////////////////////////////
	DEF_VECTOR(ANOMALIES, xr_string);
	DEF_VECTOR(ANOMALY_SETS, ANOMALIES);

	ANOMALIES						m_AnomaliesPermanent;
	ANOMALY_SETS					m_AnomalySetsList;
	xr_vector<u8>					m_AnomalySetID;	
	u32								m_dwLastAnomalySetID;
	u32								m_dwLastAnomalyStartTime;	
	
	DEF_VECTOR(ANOMALIES_ID, u16);
	DEF_VECTOR(ANOMALY_SETS_ID, ANOMALIES_ID);

	ANOMALY_SETS_ID					m_AnomalyIDSetsList;

	bool							m_bSpectatorMode;
	u32								m_dwSM_SwitchDelta;
	u32								m_dwSM_LastSwitchTime;
	u32								m_dwSM_CurViewEntity;
	CObject	*						m_pSM_CurViewEntity;
	void							SM_SwitchOnNextActivePlayer			();
	void							SM_SwitchOnPlayer		(CObject* pNewObject);

	BOOL							Is_Anomaly_InLists		(CSE_Abstract* E);

protected:


	virtual		bool				checkForTimeLimit		();
	virtual		bool				checkForFragLimit		();
	virtual		bool				checkForRoundStart		();
	virtual		bool				checkForRoundEnd		();
	virtual		bool				check_for_Anomalies		();
	virtual		void				check_for_WarmUp		();

				void				Send_Anomaly_States		(ClientID id_who);
				void				Send_EventPack_for_AnomalySet	(u32 AnomalySet, u8 Event);

	virtual		void				OnPlayerBuyFinished		(ClientID id_who, NET_Packet& P);

	virtual		void				CheckItem				(game_PlayerState*	ps, PIItem pItem, xr_vector<s16> *pItemsDesired, xr_vector<u16> *pItemsToDelete, bool ExactMatch);
	virtual		bool				HasChampion				();

	virtual		void				check_Player_for_Invincibility	(game_PlayerState* ps);

	virtual		void				Check_ForClearRun		(game_PlayerState* ps);
	void				FillDeathActorRejectItems(CSE_ActorMP *actor, xr_vector<CSE_Abstract*> & to_reject) override;

	u32								m_dwWarmUp_CurTime;
	bool							m_bInWarmUp;
	
				void	__stdcall	net_Relcase				(CObject* O);

public:
									game_sv_Deathmatch		();
	~game_sv_Deathmatch		() override;
	void				Create					(shared_str &options) override;

	LPCSTR				type_name				() const override { return "deathmatch";};
	void				net_Export_State		(NET_Packet& P, ClientID id_to) override;

	void				OnEvent					(NET_Packet &tNetPacket, u16 type, u32 time, ClientID sender ) override;

	virtual		void				OnTeamScore				(u32 /**team/**/, bool)						;		// команда выиграла
	virtual		void				OnTeamsInDraw			()								{};		// ничья

	// Events
	void				OnRoundStart			() override;												// старт раунда
	void				OnRoundEnd				() override;	// round_end_reason							// конец раунда
	virtual		void				OnDelayedRoundEnd		( ERoundEnd_Result reason );
	virtual		void				OnDelayedTeamEliminated();

	void				OnPlayerHitPlayer		(u16 id_hitter, u16 id_hitted, NET_Packet& P) override; //игрок получил Hit
	virtual		void				OnPlayerHitPlayer_Case	(game_PlayerState* ps_hitter, game_PlayerState* ps_hitted, SHit* pHitS);

	BOOL				OnTouch					(u16 eid_who, u16 eid_what, BOOL bForced = FALSE) override;
	void				OnDetach				(u16 eid_who, u16 eid_what) override;

	BOOL				OnPreCreate				(CSE_Abstract* E) override;
	void				OnCreate				(u16 eid_who) override;
	void				OnPostCreate			(u16 id_who) override;

	void				OnPlayerConnect			(ClientID id_who) override;
	void				OnPlayerConnectFinished	(ClientID id_who) override;
	void				OnPlayerDisconnect		(ClientID id_who, LPSTR Name, u16 GameID) override;
	void				OnPlayerReady			(ClientID id_who) override;
	virtual		KILL_RES			GetKillResult			(game_PlayerState* pKiller, game_PlayerState* pVictim);
	virtual		bool				OnKillResult			(KILL_RES KillResult, game_PlayerState* pKiller, game_PlayerState* pVictim);
	virtual		void				OnGiveBonus				(KILL_RES KillResult, game_PlayerState* pKiller, game_PlayerState* pVictim, KILL_TYPE KillType, SPECIAL_KILL_TYPE SpecialKillType, CSE_Abstract* pWeaponA);
	virtual		void				Processing_Victim		(game_PlayerState* pVictim, game_PlayerState* pKiller);
	virtual		void				Victim_Exp				(game_PlayerState* pVictim);
	bool				CheckTeams				() override { return false; };
	void				OnPlayerKillPlayer		(game_PlayerState* ps_killer, game_PlayerState* ps_killed, KILL_TYPE KillType, SPECIAL_KILL_TYPE SpecialKillType, CSE_Abstract* pWeaponA) override;

	void				OnPlayer_Sell_Item		(ClientID id_who, NET_Packet &P) override;

	void				OnPlayerSelectSkin		(NET_Packet& P, ClientID sender) override;
	virtual		void				OnPlayerChangeSkin		(ClientID id_who, s8 skin);
	
	virtual		void				OnFraglimitExceed		();
	virtual		void				OnTimelimitExceed		();
				void				OnPlayerScores			();
	void				OnDestroyObject			(u16 eid_who) override;
	void				OnPlayerFire (ClientID id_who, NET_Packet &P) override;
	// Main
	void				Update					() override;
				BOOL				AllPlayers_Ready		();

	void				assign_RP				(CSE_Abstract* E, game_PlayerState* ps_who) override;
	virtual		u32					RP_2_Use				(CSE_Abstract* E);

#ifdef DEBUG
	void				OnRender				() override;
#endif

	void				SetSkin					(CSE_Abstract* E, u16 Team, u16 ID) override;//	{};

	virtual		void				SpawnWeaponsForActor	(CSE_Abstract* pE, game_PlayerState*	ps);

	
	virtual		void				LoadTeams				();
	virtual		void				LoadTeamData			(const shared_str& caSection);
	virtual		void				LoadSkinsForTeam		(const shared_str& caSection, TEAM_SKINS_NAMES* pTeamSkins);
	virtual		void				LoadDefItemsForTeam		(const shared_str& caSection, /*TEAM_WPN_LIST *pWpnList,*/ DEF_ITEMS_LIST* pDefItems);

	virtual		char*				GetAnomalySetBaseName	() {return "deathmatch_game_anomaly_sets";};
	virtual		void				LoadAnomalySets			();
				
				void				LoadItemRespawns		();

	virtual		void				StartAnomalies			(int AnomalySet = -1);

	virtual		bool				IsBuyableItem			(LPCSTR	ItemName);
	void							RemoveItemFromActor		(CSE_Abstract* pItem);
	//----- Money routines -----------------------------------------------------------------
	virtual		void				Money_SetStart			(ClientID	id_who);
	virtual		s32					GetMoneyAmount			(const shared_str& caSection, char* caMoneyStr);
				int					GetTeamScore			(u32 idx);
				void				SetTeamScore			(u32 idx, int val);
				game_PlayerState*	GetWinningPlayer		();
	BOOL				CanHaveFriendlyFire		() override {return FALSE;}
	void				RespawnPlayer			(ClientID id_who, bool NoSpectator) override;
	virtual		void				check_InvinciblePlayers	();	
	virtual		void				check_ForceRespawn		();
	void				on_death				(CSE_Abstract *e_dest, CSE_Abstract *e_src) override;
	//---------------------------------------------------------------------------------------------------
	virtual		BOOL				IsDamageBlockIndEnabled	();
	virtual		s32					GetTimeLimit			();
	virtual		s32					GetFragLimit			();
	virtual		u32					GetDMBLimit				();
	virtual		u32					GetForceRespawn			();
	virtual		u32					GetWarmUpTime			();
	virtual		BOOL				IsAnomaliesEnabled		();
	virtual		u32					GetAnomaliesTime		();

	u32					GetNumTeams				() override {return teams.size();};

	// adtitional methods for predicates
	void		__stdcall			RespawnPlayerAsSpectator(IClient* client);
protected:
	void				WriteGameState			(CInifile& ini, LPCSTR sect, bool bRoundResult) override;
	shared_str m_not_free_ammo_str;
	bool CanChargeFreeAmmo(char const * ammo_section) override;
};
