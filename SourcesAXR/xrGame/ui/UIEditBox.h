#pragma once
#include "../../xrServerEntities/script_export_space.h"
#include "UIOptionsItem.h"
#include "UICustomEdit.h"
class CUIFrameLineWnd;

class CUIEditBox : 
	public CUIOptionsItem, 
	public CUICustomEdit,
	public IMetaClass
{
	DECLARE_METACLASS2(CUIEditBox, CUIOptionsItem, CUICustomEdit)
public:
					CUIEditBox				();

					void	InitCustomEdit			(Fvector2 pos, Fvector2 size) override;

	// CUIOptionsItem
					void			SetCurrentOptValue	() override;// opt->current
					void			SaveBackUpOptValue	() override;// current->backup
					void			SaveOptValue		() override;// current->opt
					void			UndoOptValue		() override;// backup->current
					bool			IsChangedOptValue	() const override;// backup!=current

	// CUIMultiTextureOwner
					void	InitTexture				(LPCSTR texture) override;
					void	InitTextureEx			(LPCSTR texture, LPCSTR  shader) override;
protected:
	CUIFrameLineWnd*	m_frameLine;
	shared_str			m_opt_backup_value;
	DECLARE_SCRIPT_REGISTER_FUNCTION
};
