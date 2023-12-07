#include "pch_script.h"
#include "UIWindow.h"
#include "UIFrameWindow.h"
#include "UIFrameLineWnd.h"
#include "UIDialogWnd.h"
#include "UIDialogHolder.h"
#include "../GamePersistent.h"
#include "UILabel.h"
#include "UIMMShniaga.h"
#include "UITextureMaster.h"
#include "UIScrollView.h"

CFontManager& mngr(){
	return UI().Font();
}

// hud font
CGameFont* GetFontSmall()
{return mngr().pFontStat;}

CGameFont* GetFontMedium()
{return mngr().pFontMedium;}
CGameFont* GetFontDI()
{return mngr().pFontDI;}
//������ ��� ����������
CGameFont* GetFontGraffiti19Russian()
{return mngr().pFontGraffiti19Russian;}
CGameFont* GetFontGraffiti22Russian()
{return mngr().pFontGraffiti22Russian;}
CGameFont* GetFontLetterica16Russian()
{return mngr().pFontLetterica16Russian;}
CGameFont* GetFontLetterica18Russian()
{return mngr().pFontLetterica18Russian;}
CGameFont* GetFontGraffiti32Russian()
{return mngr().pFontGraffiti32Russian;}
CGameFont* GetFontGraffiti50Russian()
{return mngr().pFontGraffiti50Russian;}
CGameFont* GetFontLetterica25()
{return mngr().pFontLetterica25;}


int GetARGB(u16 a, u16 r, u16 g, u16 b)
{return color_argb(a,r,g,b);}

const Fvector2* get_wnd_pos(CUIWindow* w)
{
	return &w->GetWndPos();
}
using namespace luabind;
#pragma optimize("s",on)
void CUIWindow::script_register(lua_State *L)
{
	module(L)
	[
		def("GetARGB",					&GetARGB),
		def("GetFontSmall",				&GetFontSmall),
		def("GetFontMedium",			&GetFontMedium),
		def("GetFontDI",				&GetFontDI),
		def("GetFontGraffiti19Russian",	&GetFontGraffiti19Russian),
		def("GetFontGraffiti22Russian",	&GetFontGraffiti22Russian),
		def("GetFontLetterica16Russian",&GetFontLetterica16Russian),
		def("GetFontLetterica18Russian",&GetFontLetterica18Russian),
		def("GetFontGraffiti32Russian",	&GetFontGraffiti32Russian),
		def("GetFontGraffiti50Russian",	&GetFontGraffiti50Russian),
		def("GetFontLetterica25",		&GetFontLetterica25),

		class_<CUIWindow>("CUIWindow")
		.def(							constructor<>())
		.def("AttachChild",				&CUIWindow::AttachChild, adopt<2>())
		.def("DetachChild",				&CUIWindow::DetachChild)
		.def("SetAutoDelete",			&CUIWindow::SetAutoDelete)
		.def("IsAutoDelete",			&CUIWindow::IsAutoDelete)

		.def("SetWndRect",				(void (CUIWindow::*)(Frect))	&CUIWindow::SetWndRect_script)
		.def("SetWndPos",				(void (CUIWindow::*)(Fvector2)) &CUIWindow::SetWndPos_script)
		.def("SetWndSize",				(void (CUIWindow::*)(Fvector2)) &CUIWindow::SetWndSize_script)
		.def("GetWndPos",				&get_wnd_pos)
		.def("GetWidth",				&CUIWindow::GetWidth)
		.def("GetHeight",				&CUIWindow::GetHeight)

		.def("Enable",					&CUIWindow::Enable)
		.def("IsEnabled",				&CUIWindow::IsEnabled)
		.def("Show",					&CUIWindow::Show)
		.def("IsShown",					&CUIWindow::IsShown)

		.def("WindowName",				&CUIWindow::WindowName_script)
		.def("SetWindowName",			&CUIWindow::SetWindowName)
		.def("SetPPMode",				&CUIWindow::SetPPMode)
		.def("ResetPPMode",				&CUIWindow::ResetPPMode),

		class_<CDialogHolder>("CDialogHolder")
        .def("TopInputReceiver",		&CDialogHolder::TopInputReceiver)
        .def("SetMainInputReceiver",	&CDialogHolder::SetMainInputReceiver)
		.def("AddDialogToRender",		&CDialogHolder::AddDialogToRender)
		.def("RemoveDialogToRender",	&CDialogHolder::RemoveDialogToRender),

		class_<CUIDialogWnd, CUIWindow>("CUIDialogWnd")
		.def("ShowDialog",				&CUIDialogWnd::ShowDialog)
		.def("HideDialog",				&CUIDialogWnd::HideDialog)
		.def("GetHolder",				&CUIDialogWnd::GetHolder),

		class_<CUIFrameWindow, CUIWindow>("CUIFrameWindow")
		.def(							constructor<>())
		.def("SetWidth",				&CUIFrameWindow::SetWidth)
		.def("SetHeight",				&CUIFrameWindow::SetHeight)
		.def("SetColor",				&CUIFrameWindow::SetTextureColor),

		class_<CUIFrameLineWnd, CUIWindow>("CUIFrameLineWnd")
		.def(							constructor<>())
		.def("SetWidth",				&CUIFrameLineWnd::SetWidth)
		.def("SetHeight",				&CUIFrameLineWnd::SetHeight)
		.def("SetColor",				&CUIFrameLineWnd::SetTextureColor),

		class_<CUIMMShniaga, CUIWindow>("CUIMMShniaga")
		.enum_("enum_page_id")
		[
			value("epi_main",				CUIMMShniaga::epi_main),
			value("epi_new_game",			CUIMMShniaga::epi_new_game),
			value("epi_new_network_game",	CUIMMShniaga::epi_new_network_game)
		]
		.def("SetVisibleMagnifier",			&CUIMMShniaga::SetVisibleMagnifier)
		.def("SetPage",						&CUIMMShniaga::SetPage)
		.def("ShowPage",					&CUIMMShniaga::ShowPage),
		
		


		class_<CUIScrollView, CUIWindow>("CUIScrollView")
		.def(							constructor<>())
		.def("AddWindow",				&CUIScrollView::AddWindow)
		.def("RemoveWindow",			&CUIScrollView::RemoveWindow)
		.def("Clear",					&CUIScrollView::Clear)
		.def("ScrollToBegin",			&CUIScrollView::ScrollToBegin)
		.def("ScrollToEnd",				&CUIScrollView::ScrollToEnd)
		.def("GetMinScrollPos",			&CUIScrollView::GetMinScrollPos)
		.def("GetMaxScrollPos",			&CUIScrollView::GetMaxScrollPos)
		.def("GetCurrentScrollPos",		&CUIScrollView::GetCurrentScrollPos)
		.def("SetScrollPos",			&CUIScrollView::SetScrollPos),

		class_<enum_exporter<EUIMessages> >("ui_events")
			.enum_("events")
			[
	// CUIWindow
				value("WINDOW_LBUTTON_DOWN",			static_cast<int>(WINDOW_LBUTTON_DOWN)),
				value("WINDOW_RBUTTON_DOWN",			static_cast<int>(WINDOW_RBUTTON_DOWN)),
				value("WINDOW_LBUTTON_UP",				static_cast<int>(WINDOW_LBUTTON_UP)),
				value("WINDOW_RBUTTON_UP",				static_cast<int>(WINDOW_RBUTTON_UP)),
				value("WINDOW_MOUSE_MOVE",				static_cast<int>(WINDOW_MOUSE_MOVE)),
				value("WINDOW_LBUTTON_DB_CLICK",		static_cast<int>(WINDOW_LBUTTON_DB_CLICK)),
				value("WINDOW_KEY_PRESSED",				static_cast<int>(WINDOW_KEY_PRESSED)),
				value("WINDOW_KEY_RELEASED",			static_cast<int>(WINDOW_KEY_RELEASED)),
				value("WINDOW_KEYBOARD_CAPTURE_LOST",	static_cast<int>(WINDOW_KEYBOARD_CAPTURE_LOST)),


	// CUIButton
				value("BUTTON_CLICKED",					static_cast<int>(BUTTON_CLICKED)),
				value("BUTTON_DOWN",					static_cast<int>(BUTTON_DOWN)),
				
	// CUITabControl
				value("TAB_CHANGED",					static_cast<int>(TAB_CHANGED)),

	// CUICheckButton
				value("CHECK_BUTTON_SET",				static_cast<int>(CHECK_BUTTON_SET)),
				value("CHECK_BUTTON_RESET",				static_cast<int>(CHECK_BUTTON_RESET)),
				
	// CUIRadioButton
				value("RADIOBUTTON_SET",				static_cast<int>(RADIOBUTTON_SET)),

	// CUIScrollBox
				value("SCROLLBOX_MOVE",					static_cast<int>(SCROLLBOX_MOVE)),
				
	// CUIScrollBar
				value("SCROLLBAR_VSCROLL",				static_cast<int>(SCROLLBAR_VSCROLL)),
				value("SCROLLBAR_HSCROLL",				static_cast<int>(SCROLLBAR_HSCROLL)),

	// CUIListWnd
				value("LIST_ITEM_CLICKED",				static_cast<int>(LIST_ITEM_CLICKED)),
				value("LIST_ITEM_SELECT",				static_cast<int>(LIST_ITEM_SELECT)),
	
	// UIPropertiesBox
				value("PROPERTY_CLICKED",				static_cast<int>(PROPERTY_CLICKED)),

	// CUIMessageBox
				value("MESSAGE_BOX_OK_CLICKED",			static_cast<int>(MESSAGE_BOX_OK_CLICKED)),
				value("MESSAGE_BOX_YES_CLICKED",		static_cast<int>(MESSAGE_BOX_YES_CLICKED)),
				value("MESSAGE_BOX_NO_CLICKED",			static_cast<int>(MESSAGE_BOX_NO_CLICKED)),
				value("MESSAGE_BOX_CANCEL_CLICKED",		static_cast<int>(MESSAGE_BOX_CANCEL_CLICKED)),
				value("MESSAGE_BOX_COPY_CLICKED",		static_cast<int>(MESSAGE_BOX_COPY_CLICKED)),
				value("MESSAGE_BOX_QUIT_GAME_CLICKED",	static_cast<int>(MESSAGE_BOX_QUIT_GAME_CLICKED)),
				value("MESSAGE_BOX_QUIT_WIN_CLICKED",	static_cast<int>(MESSAGE_BOX_QUIT_WIN_CLICKED)),

				value("EDIT_TEXT_COMMIT",				static_cast<int>(EDIT_TEXT_COMMIT)),
	// CMainMenu
				value("MAIN_MENU_RELOADED",				static_cast<int>(MAIN_MENU_RELOADED))
			]
	];
}
