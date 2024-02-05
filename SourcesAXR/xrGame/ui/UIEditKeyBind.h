#pragma once

#include "UIStatic.h"
#include "UIOptionsItem.h"

struct _action;
struct _keyboard;
class CUIColorAnimatorWrapper;

class CUIEditKeyBind : public CUIStatic, public CUIOptionsItem 
{
	bool			m_bPrimary;
	_action*		m_action;
	_keyboard*		m_keyboard;
	_keyboard*		m_opt_backup_value;
public:
					CUIEditKeyBind			(bool bPrim);
	~CUIEditKeyBind			() override;
	// options item
	void	AssignProps				(const shared_str& entry, const shared_str& group) override;

	void	SetCurrentOptValue		() override;	// opt->current
	void	SaveBackUpOptValue		() override;	// current->backup
	void	SaveOptValue			() override;	// current->opt
	void	UndoOptValue			() override;	// backup->current
	bool	IsChangedOptValue		() const override;	// backup!=current
	
			void	SetValue				();
	void	OnMessage				(LPCSTR message) override;

	// CUIWindow methods
			void	InitKeyBind				(Fvector2 pos, Fvector2 size);
	void	Update					() override;
	bool	OnMouseDown				(int mouse_btn) override;
	void	OnFocusLost				() override;
	bool	OnKeyboardAction				(int dik, EUIMessages keyboard_action) override;

	virtual void	SetText					(LPCSTR text);
			void	SetEditMode				(bool b);
protected:
	void			BindAction2Key			();

	bool			m_bIsEditMode;
	

//.	CUIColorAnimatorWrapper*				m_pAnimation;
};