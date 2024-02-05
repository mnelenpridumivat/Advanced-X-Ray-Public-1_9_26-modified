#pragma once

#include "UIDialogWnd.h"
#include "UIWndCallback.h"
#include "UIMessageBox.h"

class CUIStatic;
class CUITabControl;
class CUIXml;
class CUIMpPlayersAdm;
class CUIMpServerAdm;
class CUIMpChangeMapAdm;
class CUIWindow;
class CUI3tButton;
class CUIMessageBoxEx;

class CUIMpAdminMenu :	public CUIDialogWnd, public CUIWndCallback 
{
private:
		typedef CUIWindow	inherited;
		CUIStatic*			m_pBack;
		CUITabControl*		m_pTabControl;
		CUIMpPlayersAdm*	m_pPlayersAdm;
		CUIMpServerAdm*		m_pServerAdm;
		CUIMpChangeMapAdm*	m_pChangeMapAdm;
		CUIXml*				xml_doc;

		CUIWindow*			m_pActiveDialog;
		shared_str			m_sActiveSection;
		CUI3tButton*		m_pClose;

		CUIMessageBoxEx*	m_pMessageBoxLogin;
		CUIMessageBoxEx*	m_pMessageBoxOk;

public:
							CUIMpAdminMenu();
		~CUIMpAdminMenu() override;
				void		Init();
		void 		SendMessage(CUIWindow* pWnd, s16 msg, void* pData = NULL) override;
		bool		OnKeyboardAction(int dik, EUIMessages keyboard_action) override;
				void		SetActiveSubdialog	(const shared_str& section);
		void	xr_stdcall	RemoteAdminLogin(CUIWindow*, void*);
				void		ShowMessageBox(CUIMessageBox::E_MESSAGEBOX_STYLE style, LPCSTR reason="");
};


