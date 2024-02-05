#pragma once

#include "UIGameCustom.h"
#include "UIGameDM.h"

#include "ui/UIDialogWnd.h"
#include "ui/UISpawnWnd.h"

// refs 

class CUITDMFragList;
class CUITDMPlayerList;
class CUISkinSelectorWnd;
class game_cl_TeamDeathmatch;
class CUIStatic;
class CUITextWnd;
class CUISpawnWnd;

class CUIGameTDM: public CUIGameDM
{
private:
	game_cl_TeamDeathmatch * m_game;
	typedef CUIGameDM inherited;

public:
	CUISpawnWnd*		m_pUITeamSelectWnd;

protected:
	CUIStatic*			m_team1_icon;
	CUIStatic*			m_team2_icon;
	CUITextWnd*			m_team1_score;
	CUITextWnd*			m_team2_score;
	CUITextWnd*			m_buy_msg_caption;
public:
	CUIGameTDM			();
	~CUIGameTDM				() override;
	void		SetClGame				(game_cl_GameState* g) override;
	void		UnLoad					() override;
	void		Init					(int stage) override;
			void		SetScoreCaption			(int t1, int t2);			
			void		SetBuyMsgCaption		(LPCSTR str);
	void		SetFraglimit			(int local_frags, int fraglimit) override;
	void		Render					() override;
	void _BCL	OnFrame					() override;

	bool		IR_UIOnKeyboardPress	(int dik) override;
	bool		IR_UIOnKeyboardRelease	(int dik) override;
};
