#pragma once

#include "UIDialogWnd.h"

class CUIStatic;
class CUITextWnd;
class CUI3tButton;
class CUIFrameWindow;
class CUIListBox;
class CUIXml;

class CUIChangeMap : public CUIDialogWnd 
{
public:
					CUIChangeMap			();
					~CUIChangeMap			() override;
			void	InitChangeMap			(CUIXml& xml_doc);

					bool	OnKeyboardAction				(int dik, EUIMessages keyboard_action) override;
					void	SendMessage				(CUIWindow* pWnd, s16 msg, void* pData = nullptr) override;

	void 			OnBtnOk					();
	void 			OnBtnCancel				();
	void 			OnItemSelect			();

protected:
			void	FillUpList				();

	CUIStatic*		bkgrnd;
	CUITextWnd*		header;
	CUIStatic*		map_pic;
	CUIStatic*		map_frame;
	CUITextWnd*		map_version;
	CUIFrameWindow* frame;
	CUIFrameWindow* lst_back;
	CUIListBox*		lst;

	CUI3tButton*	btn_ok;
	CUI3tButton*	btn_cancel;

	u32						m_prev_upd_time;
};