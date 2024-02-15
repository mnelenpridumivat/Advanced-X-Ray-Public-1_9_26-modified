#pragma once
#include "UIButton.h"
#include "UI_IB_Static.h"

class CUI3tButton : 
	public CUIButton,
	public IMetaClass
{
	DECLARE_METACLASS1(CUI3tButton, CUIButton)
	typedef CUIButton	inherited;
	friend class CUIXmlInit;
//.	using CUIButton::SetTextColor;
public:
					CUI3tButton					();
	~CUI3tButton				() override;
	// appearance

	virtual	void 	InitButton					(Fvector2 pos, Fvector2 size);
	void 	InitTexture					(LPCSTR tex_name) override;
	virtual void 	InitTexture					(LPCSTR tex_enabled, LPCSTR tex_disabled, LPCSTR tex_touched, LPCSTR tex_highlighted);

//.			void 	SetTextColor				(u32 color);
	void 	SetTextureOffset			(float x, float y) override;
	void 	SetWidth					(float width) override;
	void 	SetHeight					(float height) override;
			void 	InitSoundH					(LPCSTR sound_file);
			void 	InitSoundT					(LPCSTR sound_file);

	void 	OnClick						() override;
	void 	OnFocusReceive				() override;
	void	OnFocusLost					() override;

	void	DrawTexture					() override;
	void	Update						() override;
	void 	Draw						() override;

	bool 	OnMouseDown					(int mouse_btn) override;

	void			SetStateTextColor				(u32 color, IBState state){m_dwTextColor[state] = color; m_bUseTextColor[state] = true;}
	u32				m_dwTextColor[4];
	bool			m_bUseTextColor[4]; // note: 0 index will be ignored


	bool					m_frameline_mode;
	bool					vertical;
	CUI_IB_Static*			m_background;
	CUI_IB_FrameLineWnd*	m_back_frameline;
private:	
			void		PlaySoundH					();
			void		PlaySoundT					();

	ref_sound			m_sound_h;
	ref_sound			m_sound_t;	

}; // class CUI3tButton
