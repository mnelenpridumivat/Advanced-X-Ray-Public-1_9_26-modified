#pragma once
#include "UIDialogWnd.h"
#include "UIWndCallback.h"

class CUIMessageBox;

class CUIMessageBoxEx : 
	public CUIDialogWnd, 
	public CUIWndCallback,
	public IMetaClass
{
	DECLARE_METACLASS2(CUIMessageBoxEx, CUIDialogWnd, CUIWndCallback)
public:
					CUIMessageBoxEx		();
					~CUIMessageBoxEx	() override;
			void	 SetText			(LPCSTR text);
			LPCSTR	GetText				();
	virtual void	InitMessageBox		(LPCSTR xml_template);
					void	SendMessage			(CUIWindow* pWnd, s16 msg, void* pData = NULL) override;

	LPCSTR			GetHost				();
	LPCSTR			GetPassword			();

	void			SetTextEditURL		(LPCSTR text);
	LPCSTR			GetTextEditURL		();

	CUIWndCallback::void_function		func_on_ok;
	CUIWndCallback::void_function		func_on_no;
	void xr_stdcall	OnOKClicked			(CUIWindow*, void*);
	void xr_stdcall	OnNOClicked			(CUIWindow*, void*);

					bool	OnKeyboardAction			(int dik, EUIMessages keyboard_action) override;
					bool	NeedCenterCursor	()const override {return false;}

    CUIMessageBox*						m_pMessageBox;
};