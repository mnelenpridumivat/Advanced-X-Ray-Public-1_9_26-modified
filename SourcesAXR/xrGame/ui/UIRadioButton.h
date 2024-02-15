#pragma once

#pragma once
#include "UITabButton.h"

class CUIRadioButton : 
	public CUITabButton,
	public IMetaClass
{
	DECLARE_METACLASS1(CUIRadioButton, CUITabButton)
	typedef CUITabButton inherited;
public:
	void InitButton(Fvector2 pos, Fvector2 size) override;
	void InitTexture(LPCSTR tex_name) override;
	virtual void SetTextX(float x)	{/*do nothing*/}
};