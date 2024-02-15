#pragma once

#include "ui3tbutton.h"
#include "UIOptionsItem.h"

class UIHint;

class CUICheckButton : 
	public CUI3tButton, 
	public CUIOptionsItem,
	public IMetaClass
{
	DECLARE_METACLASS2(CUICheckButton, CUI3tButton, CUIOptionsItem)
	typedef CUI3tButton			inherited;

public:
					CUICheckButton			();
	~CUICheckButton			() override;

	void	Update					() override;

	// CUIOptionsItem
	void	SetCurrentOptValue	() override;	// opt->current
	void	SaveBackUpOptValue	() override;	// current->backup
	void	SaveOptValue		() override;	// current->opt
	void	UndoOptValue		() override;	// backup->current
	bool	IsChangedOptValue	() const override;	// backup!=current

	void 	OnFocusReceive		() override;
	void	OnFocusLost			() override;
	void	Show				( bool status ) override;
	bool 	OnMouseAction				( float x, float y, EUIMessages mouse_action ) override;
	bool	OnMouseDown			( int mouse_btn ) override;

			void InitCheckButton		(Fvector2 pos, Fvector2 size, LPCSTR texture_name);

	//состояние кнопки
	IC	bool	GetCheck					() const {return GetButtonState() == BUTTON_PUSHED;}
	IC	void	SetCheck(bool ch)
	{
		SetButtonState( ch ? BUTTON_PUSHED : BUTTON_NORMAL);
	}

	void SetDependControl(CUIWindow* pWnd);

private:
	bool							m_opt_backup_value;
	void InitTexture2				(LPCSTR texture_name);
	CUIWindow* m_pDependControl;

};