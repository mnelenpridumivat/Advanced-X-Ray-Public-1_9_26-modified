#pragma once
#include "game_cl_deathmatch.h"

class CUISpawnWnd;
class CUIGameTDM;

class game_cl_TeamDeathmatch :public game_cl_Deathmatch
{
typedef game_cl_Deathmatch inherited;
	CUIGameTDM*							m_game_ui;
protected:
	bool								m_bFriendlyIndicators;
	bool								m_bFriendlyNames;

void				shedule_Update			(u32 dt) override;
void				TranslateGameMessage	(u32 msg, NET_Packet& P) override;

void				LoadSndMessages				() override;
public :
										game_cl_TeamDeathmatch	();
~game_cl_TeamDeathmatch	() override;
void				Init					() override;
void				net_import_state		(NET_Packet& P) override;
CUIGameCustom*		createGameUI			() override;
void				SetGameUI				(CUIGameCustom*) override;
void				GetMapEntities			(xr_vector<SZoneMapEntityData>& dst) override;

BOOL					CanCallBuyMenu			() override;
BOOL					CanCallSkinMenu			() override;
BOOL					CanCallInventoryMenu	() override;
	virtual	BOOL					CanCallTeamSelectMenu	();


void					OnSpectatorSelect		() override;
void				OnSkinMenuBack			() override;
void				OnTeamMenuBack			() override;
void				OnMapInfoAccept			() override;

void				OnGameMenuRespond_ChangeTeam	(NET_Packet& P) override;

void				OnTeamSelect			(int Result) override;
char*				getTeamSection			(int Team) override;
void				OnTeamChanged			() override;
void				PlayRankChangesSndMessage () override;
void				OnTeamMenu_Cancel		() override;

	virtual			void				Set_ShowPlayerNames		(bool Show) {m_bShowPlayersNames = Show;};
	virtual			bool				Get_ShowPlayerNames		() {return m_bShowPlayersNames;};
s16					ModifyTeam				(s16 Team) override {return (Team != -1) ? Team-1 : Team;};
	virtual			bool				Get_ShowPlayerNamesEnabled () {return m_bFriendlyNames;};

bool				IsPlayerInTeam			(game_PlayerState* ps, ETeam team) override;
LPCSTR				GetGameScore			(string32&	score_dest) override;
	s32									GetGreenTeamScore		() const { return teams[0].score; };
	s32									GetBlueTeamScore		() const { return teams[1].score; };
//from UIGameTDM
protected:
const shared_str			GetBaseCostSect			() override {return "teamdeathmatch_base_cost";}
const shared_str			GetTeamMenu				(s16 team) override;
//	CUISpawnWnd*						pUITeamSelectWnd;

	PRESET_ITEMS						PresetItemsTeam1;
	PRESET_ITEMS						PresetItemsTeam2;

	BOOL								m_bTeamSelected;
	bool								m_bShowPlayersNames;

bool						CanBeReady				() override;
void						SetCurrentBuyMenu		() override;
void						SetCurrentSkinMenu		() override;

bool						OnKeyboardPress			(int key) override;

void					OnRender				() override;
bool					IsEnemy					(game_PlayerState* ps) override;
bool					IsEnemy					(CEntityAlive* ea1, CEntityAlive* ea2) override;

void						UpdateMapLocations		() override;
void						OnSwitchPhase			(u32 old_phase, u32 new_phase) override;

void						SetScore				() override;
void						OnSwitchPhase_InProgress() override;

u8						GetTeamCount			() override { return 2; };
void					OnConnected				() override;
};

IC bool	TDM_Compare_Players		(game_PlayerState* p1, game_PlayerState* p2)
{
	return DM_Compare_Players(p1, p2);
};