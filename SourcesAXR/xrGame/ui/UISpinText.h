#include "UICustomSpin.h"

class CUISpinText : public CUICustomSpin
{
public:
					CUISpinText			();
	// CUIOptionsItem
					void	SetCurrentOptValue	() override;	// opt->current
					void	SaveBackUpOptValue	() override;	// current->backup
					void	SaveOptValue		() override;	// current->opt
					void	UndoOptValue		() override;	// backup->current
					bool	IsChangedOptValue	() const override;	// backup!=current

	// own
					void	OnBtnUpClick() override;
					void	OnBtnDownClick() override;

			void	AddItem_(const char* item, int id);
			LPCSTR	GetTokenText();
protected:
					bool	CanPressUp		() override;
					bool	CanPressDown	() override;
					void	IncVal			() override {};
					void	DecVal			() override {};
			void	SetItem			(int v);
			struct SInfo{
				shared_str	_orig;
				shared_str	_transl;
				int			_id;
			};
	typedef xr_vector< SInfo >		Items;
	typedef Items::iterator			Items_it;

    Items	m_list;
	int		m_curItem;
	int		m_opt_backup_value;
};