#pragma once

#include "UIStatic.h"

class CUIStatix : public CUIStatic 
{
public:
					CUIStatix			();
					~CUIStatix			() override;

					void 	Update				() override;
					void 	OnFocusReceive		() override;
					void 	OnFocusLost			() override;
					bool 	OnMouseDown			(int mouse_btn) override;
			void 	SetSelectedState	(bool state);
			bool 	GetSelectedState	();

private:
	bool			m_bSelected;
	void			start_anim			();
	void			stop_anim			();
};
