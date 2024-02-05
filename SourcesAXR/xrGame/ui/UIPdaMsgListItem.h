#pragma once
#include "UIStatic.h"

class CUIPdaMsgListItem : public CUIColorAnimConrollerContainer
{
	typedef	CUIColorAnimConrollerContainer	inherited;
public:
			void		InitPdaMsgListItem				(const Fvector2& size);
	void		SetFont							(CGameFont* pFont) override;
	
	CUIStatic			UIIcon;
	CUITextWnd			UITimeText;
	CUITextWnd			UICaptionText;
	CUITextWnd			UIMsgText;
};