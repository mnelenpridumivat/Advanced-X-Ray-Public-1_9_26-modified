#include "UICustomSpin.h"

class CUISpinNum : public CUICustomSpin 
{
public:
					CUISpinNum			();

					void	InitSpin			(Fvector2 pos, Fvector2 size) override;

	// CUIOptionsItem
					void	SetCurrentOptValue	() override;	// opt->current
					void	SaveBackUpOptValue	() override;	// current->backup
					void	SaveOptValue		() override;	// current->opt
					void	UndoOptValue		() override;	// backup->current
					bool	IsChangedOptValue	() const override;	// backup!=current

					void	OnBtnUpClick		() override;
					void	OnBtnDownClick		() override;

			void	SetMax				(int max)	{m_iMax=max;};
			void	SetMin				(int min)	{m_iMin=min;};
			int		Value				() const {return m_iVal;}
protected:
			void	SetValue			(int v);
					bool	CanPressUp			() override;
					bool	CanPressDown		() override;
					void	IncVal				() override;
					void	DecVal				() override;



	int		m_iMax;
	int		m_iMin;
	int		m_iStep;
	int		m_iVal;
	int		m_opt_backup_value;
};

class CUISpinFlt : public CUICustomSpin 
{
public:
	CUISpinFlt();

	void	InitSpin			(Fvector2 pos, Fvector2 size) override;

	// CUIOptionsItem
	void	SetCurrentOptValue	() override;	// opt->current
	void	SaveBackUpOptValue	() override;	// current->backup
	void	SaveOptValue		() override;	// current->opt
	void	UndoOptValue		() override;	// backup->current
	bool	IsChangedOptValue	() const override;	// backup!=current

	void	OnBtnUpClick		() override;
	void	OnBtnDownClick		() override;

			void	SetMax				(float max);
			void	SetMin				(float min);
protected:
			void	SetValue			(float v);
	bool	CanPressUp			() override;
	bool	CanPressDown		() override;
	void	IncVal				() override;
	void	DecVal				() override;



	float		m_fMax;
	float		m_fMin;
	float		m_fStep;
	float		m_fVal;
	float		m_opt_backup_value;
};

