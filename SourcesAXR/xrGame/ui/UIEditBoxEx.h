#pragma once

#include "UICustomEdit.h"

class CUIFrameWindow;

class CUIEditBoxEx : /*public CUIMultiTextureOwner, */
	public CUICustomEdit,
	public IMetaClass
{
	DECLARE_METACLASS2(CUIEditBoxEx, CUICustomEdit)
public:
					CUIEditBoxEx	();
					~CUIEditBoxEx	() override;

					void	InitCustomEdit	(Fvector2 pos, Fvector2 size) override;

	// CUIMultiTextureOwner
					void	InitTexture		(LPCSTR texture) override;
					void	InitTextureEx	(LPCSTR texture,LPCSTR shader) override;
protected:
	CUIFrameWindow*	m_pFrameWindow;
};
