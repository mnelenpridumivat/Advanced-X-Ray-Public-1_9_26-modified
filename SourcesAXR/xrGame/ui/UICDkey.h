//
#pragma once
#include "UIEditBox.h"

class CUICDkey : public CUIEditBox
{
private:
	typedef			CUIEditBox		inherited;

public:
					CUICDkey		();
	void	SetText			(LPCSTR str) override {}
	virtual	LPCSTR	GetText			();

	// CUIOptionsItem
	void	SetCurrentOptValue	() override;	// opt->current
	void	SaveBackUpOptValue	() override;	// current->backup
	void	SaveOptValue		() override;	// current->opt
	void	UndoOptValue		() override;	// backup->current
	bool	IsChangedOptValue	() const override;	// backup!=current
	
			void	CreateCDKeyEntry();			
			void	assign_callbacks();

	void	Show			(bool status) override;
	void	Draw			() override;
	void	OnFocusLost		() override;

private:
	void xr_stdcall	paste_from_clipboard();

private:
	string512		m_opt_backup_value;
	bool			m_view_access;
}; // class CUICDkey

class CUIMPPlayerName : public CUIEditBox
{
private:
	typedef			CUIEditBox		inherited;

public:
					CUIMPPlayerName	() {};
	~CUIMPPlayerName() override {};

//	virtual	void	SetText			(LPCSTR str) {}

//	virtual void	SetCurrentValue();
//	virtual void	SaveValue();
//	virtual bool	IsChanged();

	void	OnFocusLost		() override;

}; // class CUIMPPlayerName

extern	void	GetCDKey_FromRegistry		(char* cdkey);
extern	void	WriteCDKey_ToRegistry		(LPSTR cdkey);
extern	void	GetPlayerName_FromRegistry	(char* name, u32 const name_size);
extern	void	WritePlayerName_ToRegistry	(LPSTR name);
