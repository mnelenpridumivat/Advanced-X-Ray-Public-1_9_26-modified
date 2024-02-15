#pragma once
#include "uiwindow.h"


class CUIFrameWindow: 
	public CUIWindow,
	public ITextureOwner,
	public IMetaClass
{
	DECLARE_METACLASS2(CUIFrameWindow, CUIWindow, ITextureOwner)
	typedef CUIWindow inherited;
public:
					CUIFrameWindow				();

	void	SetTextureRect				(const Frect& r) override {};
	const Frect& GetTextureRect			()										const override {return m_tex_rect[fmBK];}
	void	SetWndSize					(const Fvector2& size) override;

	void	SetTextureColor				(u32 color) override {m_texture_color = color;}
	u32		GetTextureColor				()										const override {return m_texture_color;}

	void	InitTexture					(LPCSTR texture) override;
	void	InitTextureEx				(LPCSTR texture, LPCSTR  shader) override;

	void	SetStretchTexture			(bool stretch) override {}
	bool	GetStretchTexture			() override {return false;};

	void	Draw						() override;
	
protected:
	bool			m_bTextureVisible;

	enum EFramePart{
		fmBK=0, fmL, fmR, fmT, fmB, fmLT, fmRB, fmRT, fmLB, fmMax
	};

	ui_shader			m_shader;
	shared_str			dbg_tex_name;
	Frect				m_tex_rect			[fmMax];
	u32					m_texture_color;
	void				DrawElements		();
	bool				get_points			(Frect const& r, int i, Fvector2& LTp, Fvector2& RBp, Fvector2& LTt, Fvector2& RBt);
	void				draw_tile_line		(Frect rect, int i, bool b_horz, Fvector2 const& ts);
	void				draw_tile_rect		(Frect rect, int i, Fvector2 const& ts);
};
