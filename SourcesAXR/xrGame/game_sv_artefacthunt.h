#pragma once

#include "game_sv_teamdeathmatch.h"

class	game_sv_ArtefactHunt			: 
	public game_sv_TeamDeathmatch,
	public IMetaClass
{
	DECLARE_METACLASS1(game_sv_ArtefactHunt, game_sv_TeamDeathmatch)
private:
	typedef game_sv_TeamDeathmatch inherited;

	enum	ARTEFACT_STATE
	{
		NONE,
		NOARTEFACT,
		ON_FIELD,
		IN_POSSESSION,
	};

protected:
	
	u32								m_dwNextReinforcementTime;
	int								m_iMoney_for_BuySpawn;

	u32								m_dwArtefactSpawnTime;
	u32								m_dwArtefactRemoveTime;

	u16								m_ArtefactsSpawnedTotal;
	u16								m_dwArtefactID;	

	ARTEFACT_STATE					m_eAState;
	bool							m_bArtefactWasTaken;
	bool							m_bArtefactWasDropped;

	xr_vector<RPoint>				Artefact_rpoints;
//.	xr_vector<u8>					ArtefactsRPoints_ID;
//.	u8								m_LastRespawnPointID;
	CRandom							ArtefactChooserRandom;

	u16								artefactBearerID;//ah,ZoneMap
	u16								m_iAfBearerMenaceID;
	u8								teamInPossession;//ah,ZoneMap

	bool							bNoLostMessage;
	bool							m_bArtefactWasBringedToBase;

	bool							m_bSwapBases;

	void							Artefact_PrepareForSpawn	();
	void							Artefact_PrepareForRemove	();

	bool							Artefact_NeedToSpawn	();
	bool							Artefact_NeedToRemove	();
	bool							Artefact_MissCheck		();

	void							CheckForAnyAlivePlayer	();
	void							UpdatePlayersNotSendedMoveRespond();
	void							ReplicatePlayersStateToPlayer(ClientID CID);

	void				check_Player_for_Invincibility	(game_PlayerState* ps) override;
	void				Check_ForClearRun		(game_PlayerState* ps) override;

	void				ReadOptions				(shared_str &options) override;
	void				ConsoleCommands_Create	() override;
	void				ConsoleCommands_Clear	() override;

	bool				Player_Check_Rank		(game_PlayerState* ps) override;
	//virtual		void			DestroyAllPlayerItems(ClientID id_who);

	bool		assign_rp_tmp		(game_PlayerState* ps_who, xr_vector<RPoint>& points_vec, xr_vector<u32>& dest, xr_vector<u32>& rpIDEnemy, xr_vector<ClientID>& EnemyIt,  bool use_safe_dist);
public:

									game_sv_ArtefactHunt	(){m_type = eGameIDArtefactHunt;}
	void				Create					(shared_str& options) override;

	LPCSTR				type_name			() const override { return "artefacthunt";};
	// Events	
	void				OnEvent					(NET_Packet &tNetPacket, u16 type, u32 time, ClientID sender ) override;
	void				OnRoundStart			() override;							// старт раунда
	KILL_RES			GetKillResult			(game_PlayerState* pKiller, game_PlayerState* pVictim) override;
	bool				OnKillResult			(KILL_RES KillResult, game_PlayerState* pKiller, game_PlayerState* pVictim) override;
	void				OnGiveBonus				(KILL_RES KillResult, game_PlayerState* pKiller, game_PlayerState* pVictim, KILL_TYPE KillType, SPECIAL_KILL_TYPE SpecialKillType, CSE_Abstract* pWeaponA) override;
	void				OnPlayerHitPlayer		(u16 id_hitter, u16 id_hitted, NET_Packet& P) override;
	void				OnPlayerHitPlayer_Case	(game_PlayerState* ps_hitter, game_PlayerState* ps_hitted, SHit* pHitS) override;
	void				OnPlayerKillPlayer		(game_PlayerState* ps_killer, game_PlayerState* ps_killed, KILL_TYPE KillType, SPECIAL_KILL_TYPE SpecialKillType, CSE_Abstract* pWeaponA) override;
	void				OnPlayerFire			(ClientID id_who, NET_Packet &P) override {};
	void				Victim_Exp				(game_PlayerState* pVictim) override {};
	void				UpdateTeamScore			(game_PlayerState* ps_killer, s16 OldKills) override {};
	void				OnPlayerReady			(ClientID id_who) override;
	void				OnPlayerBuySpawn		(ClientID sender) override;

	void				OnTimelimitExceed		() override;

	void				assign_RP				(CSE_Abstract* E, game_PlayerState* ps_who) override;
	u32					RP_2_Use				(CSE_Abstract* E) override;	
	virtual		void				CheckRPUnblock			();
	virtual		void				SetRP					(CSE_Abstract* E, RPoint* pRP);

	void				LoadTeams				() override;

	char*				GetAnomalySetBaseName	() override {return "artefacthunt_game_anomaly_sets";};

	virtual		void				OnObjectEnterTeamBase	(u16 id, u16 zone_team);
	virtual		void				OnObjectLeaveTeamBase	(u16 id, u16 zone_team);
	
	void							OnArtefactOnBase		(ClientID id_who);

	BOOL				OnTouch					(u16 eid_who, u16 eid_what, BOOL bForced = FALSE) override;
	void				OnDetach				(u16 eid_who, u16 eid_what) override;
	void				OnCreate				(u16 id_who) override;


	void				Update					() override;
				
				void				SpawnArtefact			();
				void				RemoveArtefact			();
				void				Assign_Artefact_RPoint	(CSE_Abstract* E);

	void				net_Export_State		(NET_Packet& P, ClientID id_to) override;				// full state
				bool				ArtefactSpawn_Allowed	();
	//-------------------------------------------------------------------------------
	virtual		void				RespawnAllNotAlivePlayers	();
	virtual		bool				CheckAlivePlayersInTeam		(s16 Team);
	virtual		void				MoveAllAlivePlayers			();
	virtual		void				CheckForTeamElimination		();
	virtual		void				CheckForTeamWin				();
	BOOL				CanHaveFriendlyFire		() override {return TRUE;}

	//-----------------------------------------------------------------------------
	virtual		int					Get_ArtefactsCount			();
	virtual		u32					Get_ArtefactsRespawnDelta	();
	virtual		u32					Get_ArtefactsStayTime		();
	virtual		int					Get_ReinforcementTime		();
	virtual		BOOL				Get_ShieldedBases			();
	virtual		BOOL				Get_ReturnPlayers			();
	virtual		BOOL				Get_BearerCantSprint		();

				void				SwapTeams					();

	//  [7/5/2005]
#ifdef DEBUG
	void				OnRender				() override;
#endif
	//  [7/5/2005]
protected:
	void				WriteGameState			(CInifile& ini, LPCSTR sect, bool bRoundResult) override;
};
