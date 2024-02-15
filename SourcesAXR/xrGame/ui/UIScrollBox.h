#pragma once
#include "uiFrameLineWnd.h"

class CUIScrollBox :
	public CUIFrameLineWnd,
	public IMetaClass
{
	DECLARE_METACLASS1(CUIScrollBox, CUIFrameLineWnd)
	typedef	CUIFrameLineWnd		inherited;
public:
								CUIScrollBox			();

	bool				OnMouseAction					(float x, float y, EUIMessages mouse_action) override;
};
