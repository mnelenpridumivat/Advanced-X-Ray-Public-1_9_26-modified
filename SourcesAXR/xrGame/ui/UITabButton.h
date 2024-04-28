#pragma once
#include "UI3tButton.h"

class CUITabButton : public CUI3tButton 
{
	typedef CUI3tButton inherited;
public:
	shared_str						m_btn_id;

				CUITabButton		();
	~CUITabButton		() override;

	void SendMessage		(CUIWindow* pWnd, s16 msg, void* pData = 0) override;
	bool OnMouseAction			(float x, float y, EUIMessages mouse_action) override;
	bool OnMouseDown		(int mouse_btn) override;
};