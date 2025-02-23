#pragma once

#include "UIDialogWnd.h"
#include "../encyclopedia_article_defs.h"

class CInventoryOwner;
class CUIFrameLineWnd;
class CUIButton;
class CUI3tButtonEx;
class CUITabControl;
class CUIStatic;
class CUIXml;
class CUIFrameWindow;
class UIHint;

class CUIActorInfoWnd;
class CUIPdaContactsWnd;
class CUITaskWnd;
class CUIFactionWarWnd;
class CUIRankingWnd;
class CUILogsWnd;
class CUIEncyclopediaWnd;
class CUIDiaryWnd;
class CUIAnimatedStatic;
class UIHint;


namespace pda_section {
	enum part {
		quests = (1 << 8),
		map = (1 << 9),
		diary = (1 << 10),
		contacts = (1 << 11),
		ranking = (1 << 12),
		statistics = (1 << 13),
		encyclopedia = (1 << 14),
		skills = (1 << 15),
		downloads = (1 << 16),
		games = (1 << 17),
		mplayer = (1 << 18),


		news = diary | (1 << 1),
		info = diary | (1 << 2),
		journal = diary | (1 << 3),

	};
};

class CUIPdaWnd : public CUIDialogWnd
{
	typedef CUIDialogWnd	inherited;
protected:
	CUITabControl* UITabControl;
	CUI3tButtonEx* m_btn_close;

	CUIStatic* UIMainPdaFrame;
	CUIStatic* UINoice;

	CUIStatic* m_caption;
	shared_str				m_caption_const;
	CUIAnimatedStatic* m_anim_static;

	// Текущий активный диалог
	CUIWindow* m_pActiveDialog;
	shared_str				m_sActiveSection;

	UIHint* m_hint_wnd;

	u32 dwPDAFrame;

	bool bButtonL, bButtonR;

public:
	CUITaskWnd* pUITaskWnd;
	CUIFactionWarWnd* pUIFactionWarWnd;
	CUIRankingWnd* pUIRankingWnd;
	CUILogsWnd* pUILogsWnd;
	CUIEncyclopediaWnd* pUIEncyclopediaWnd;
	CUIDiaryWnd* pUIDiaryWnd;
	Frect m_cursor_box;

	virtual void			Reset();

public:
	CUIPdaWnd();
	virtual					~CUIPdaWnd();

	virtual void 			Init();

	virtual void 			SendMessage(CUIWindow* pWnd, s16 msg, void* pData = NULL);

	virtual void 			Draw();
	virtual void 			Update();
	virtual void 			Show();
	virtual void 			Hide();
	virtual bool			OnMouseAction(float x, float y, EUIMessages mouse_action);
			void			MouseMovement(float x, float y);
	virtual void			Enable(bool status);
	virtual bool			OnKeyboardAction(int dik, EUIMessages keyboard_action);

	UIHint* get_hint_wnd() const { return m_hint_wnd; }
	void			DrawHint();

	void			SetActiveCaption();
	void			SetCaption(LPCSTR text);
	void			Show_SecondTaskWnd(bool status);
	void			Show_MapLegendWnd(bool status);

	void			SetActiveSubdialog(const shared_str& section);
	virtual bool			StopAnyMove() { return false; }

	void			UpdatePda();
	void			PdaContentsChanged(pda_section::part type);

	void			ResetCursor();
	float			m_power;
	Fvector2		last_cursor_pos;

	Fvector			target_joystickrot, joystickrot;
	float			target_buttonpress, buttonpress;

	void ResetJoystick(bool bForce)
	{
		if (bForce)
		{
			joystickrot.set(0.f, 0.f, 0.f);
			buttonpress = 0.f;
		}

		target_joystickrot.set(0.f, 0.f, 0.f);
		target_buttonpress = 0.f;
	}

	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CUIPdaWnd)
#undef script_type_list
#define script_type_list save_type_list(CUIPdaWnd)
