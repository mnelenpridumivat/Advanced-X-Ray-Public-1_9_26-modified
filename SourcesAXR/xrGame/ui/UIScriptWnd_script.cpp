#include "pch_script.h"
#include "../base_client_classes.h"
//UI-controls
#include "UIScriptWnd.h"
#include "UIButton.h"
#include "UIMessageBox.h"
#include "UIPropertiesBox.h"
#include "UICheckButton.h"
#include "UIRadioButton.h"
#include "UIStatic.h"
#include "UIEditBox.h"
#include "UIFrameWindow.h"
#include "UIFrameLineWnd.h"
#include "UIProgressBar.h"
#include "UITabControl.h"

#include "uiscriptwnd_script.h"

using namespace luabind;

extern export_class script_register_ui_window1(export_class &&);
extern export_class script_register_ui_window2(export_class &&);

#pragma optimize("s",on)
void CUIDialogWndEx::script_register(lua_State *L)
{
	export_class				instance("CUIScriptWnd");

	module(L)
	[
		script_register_ui_window2(
			script_register_ui_window1(
				std::move(instance)
			)
		)
		.def("Load",			&BaseType::Load)
	];
}

SCRIPT_EXPORT3(CUIDialogWndEx, DLL_PureScript, CUIWindow);

export_class script_register_ui_window1(export_class &&instance)
{
	return std::move(instance)
		.def(					constructor<>())

		.def("AddCallback",		static_cast<void(BaseType::*)(LPCSTR, s16, const luabind::functor<void>&, const luabind::object&)>(&
			     BaseType::AddCallback))

		.def("Register",		static_cast<void (BaseType::*)(CUIWindow*, LPCSTR)>(&BaseType::Register))

	;
}
