#pragma once

#include "game_cl_mp.h"
#include "UIGameCTA.h"
#include "game_cl_capture_the_artefact_captions_manager.h"
/// This class describes the client part of "Capture The Artefact" game mode.
class game_cl_CaptureTheArtefact	: public game_cl_mp
{
private:
	typedef game_cl_mp inherited;
	
	CUIGameCTA * m_game_ui;

	BOOL	m_bReadMapDesc;
	BOOL	m_bTeamSelected;
	BOOL	m_bSkinSelected;
	BOOL	m_winnerTeamShowed;
	
	CTAGameClCaptionsManager	m_captions_manager;

	u32		m_curReinforcementTime;
	u32		m_maxReinforcementTime;

	u32		m_currentWarmupTime;
	s32		m_s32TimeLimit;
	bool	m_inWarmup;

	s32 maxScore;
	s32 greenTeamScore;
	s32 blueTeamScore;

	Fvector	greenTeamRPos;
	Fvector	blueTeamRPos;

	u16 greenArtefact;
	u16 blueArtefact;
	bool haveGotUpdate;
	//bool sendedSpawnMe;

	u16 greenArtefactOwner;	//GameID, if 0, then no body took the artefact
	u16 blueArtefactOwner;
	
	const shared_str & GetLocalPlayerTeamSection() const;
	ETeam GetLocalPlayerTeam() const;
	
	bool		m_player_on_base;
	bool		m_allow_buy;
	bool		m_bFriendlyIndicators;
	bool		m_bFriendlyNames;
	bool		m_bBearerCantSprint;
	bool		m_bCanActivateArtefact;
	bool		m_bShowPlayersNames;
	u32			m_dwVoteEndTime;
	float		m_baseRadius;

	s32		spawn_cost;
	s32		buy_amount;
	s32		total_money;
	s32		last_money;

	void UpdateMoneyIndicator();
	
	void LoadSndMessages() override;
	void OnPlayerEnterBase();
	void OnPlayerLeaveBase();
	void SetInvinciblePlayer(u16 const gameId, bool const invincible);
	void SpawnMe();

	void PlayCapturedTheArtefact(game_PlayerState const * capturer);
	void PlayDeliveredTheArtefact(game_PlayerState const * deliverer);
	void PlayReturnedTheArtefact(game_PlayerState const * returnerer);
	void PlayRankChangedSnd();

	void UpdateVotingTime(u32 current_time);
	void UpdateWarmupTime(u32 current_time);
	void UpdateTimeLimit(u32 current_time);
public:
	game_cl_CaptureTheArtefact();
	void	SetGameUI(CUIGameCustom * already_created_ui) override;
	~game_cl_CaptureTheArtefact() override;
	CUIGameCustom * createGameUI() override;
	/// Initializes teams
	void Init() override;
	void shedule_Update(u32 dt) override;
	void net_import_state(NET_Packet& P) override;
	void net_import_update(NET_Packet& P) override;
	void TranslateGameMessage(u32 msg, NET_Packet& P) override;

	void OnGameMenuRespond_ChangeSkin(NET_Packet& P) override;
	void OnGameMenuRespond_ChangeTeam(NET_Packet& P) override;
	void OnPlayerFlagsChanged(game_PlayerState* ps) override;
	void OnNewPlayerConnected(ClientID const & newClient) override;
	void OnRender() override;

	bool IsEnemy(game_PlayerState* ps) override;

	bool CanBeReady() override;
	bool NeedToSendReady_Actor			(int key, game_PlayerState* ps) override;
	bool NeedToSendReady_Spectator		(int key, game_PlayerState* ps) override;

	bool OnKeyboardPress(int key) override;
	bool OnKeyboardRelease(int key) override;

	void OnSpawn(CObject* pObj) override;
	virtual	BOOL CanCallBuyMenu();
	virtual BOOL CanCallSkinMenu() {return TRUE;};
	virtual BOOL CanCallTeamSelectMenu();
	virtual	BOOL CanCallInventoryMenu();
			bool LocalPlayerCanBuyItem(shared_str const & name_sect);
	
			void	Set_ShowPlayerNames			(bool Show) {m_bShowPlayersNames = Show;};
			bool	Get_ShowPlayerNames			()			{return m_bShowPlayersNames;};
			bool	Get_ShowPlayerNamesEnabled	()			{return m_bFriendlyNames;};

	//ui part
	void OnSpectatorSelect() override;
	void OnMapInfoAccept() override;

	void OnTeamChanged() override;
	void OnRankChanged(u8 OldRank) override;
			void OnTeamScoresChanged();

	void OnTeamMenuBack() override;
	void OnTeamMenu_Cancel() override;
	void OnTeamSelect(int Team) override;
	void OnBuyMenu_Ok() override;
	void OnBuyMenu_Cancel() override;
	void OnBuySpawnMenu_Ok() override;
			
			void OnBuyMenuOpen();

	void OnSkinMenuBack			() override;
	void OnSkinMenu_Ok			() override;
	void OnSkinMenu_Cancel		() override;

	void UpdateMapLocations		() override;

	void	OnVoteStart(NET_Packet& P) override;
	void	OnVoteStop(NET_Packet& P) override;
	void	OnVoteEnd(NET_Packet& P) override;

	char*	getTeamSection			(int Team) override;

	s16	ModifyTeam(s16 Team) override {return Team;};
	bool PlayerCanSprint(CActor* pActor) override;

	//very bad... need to fix problem with team indexes...
	void OnSpeechMessage(NET_Packet& P) override;
	u8 GetTeamCount	() override { return 2; };

	void OnSwitchPhase(u32 old_phase, u32 new_phase) override;
	void OnGameRoundStarted	() override;
	u16 GetGreenArtefactOwnerID		() const;
	u16 GetBlueArtefactOwnerID		() const;
	
	Fvector const & GetGreenArtefactRPoint	()	const;
	Fvector const & GetBlueArtefactRPoint	()	const;
	float			GetBaseRadius			()	const;
	u16				GetGreenArtefactID		()	const;
	u16				GetBlueArtefactID		()	const;
	bool			CanActivateArtefact		()	const;

	bool			InWarmUp				()	const;
	bool	Is_Rewarding_Allowed	()  const override { return !InWarmUp(); };
	bool			HasTimeLimit			()	const;

	LPCSTR	GetGameScore			(string32&	score_dest) override;
	void	OnConnected				() override;
	s32				GetGreenTeamScore		() const { return greenTeamScore; };
	s32				GetBlueTeamScore		() const { return blueTeamScore; };
};