#pragma once

#include "UIDialogWnd.h"

class CUIStatic;
class CUI3tButton;
class CUIKickPlayer;
class CUIChangeMap;
class CUIChangeWeather;
class CUIChangeGameType;
class CUIXml;
class CUITextVote;

class CUIVotingCategory : public CUIDialogWnd 
{
private:
	typedef CUIDialogWnd inherited;
public:
						CUIVotingCategory	();
	~CUIVotingCategory	() override;

	bool		OnKeyboardAction			(int dik, EUIMessages keyboard_action) override;
	void		SendMessage			(CUIWindow* pWnd, s16 msg, void* pData = nullptr) override;

	void				OnBtn				(int i);
	void				OnBtnCancel			();

	void		Update				() override;

protected:
	void				InitVotingCategory	();

	CUIStatic*			header;
	CUI3tButton*		btn[7];
	CUIStatic*			txt[7];
	CUIStatic*			bkgrnd;
	CUI3tButton*		btn_cancel;

	CUIKickPlayer*		kick;
	CUIChangeMap*		change_map;
	CUIChangeWeather*	change_weather;
	CUIChangeGameType*	change_gametype;
	CUIXml*				xml_doc;
};