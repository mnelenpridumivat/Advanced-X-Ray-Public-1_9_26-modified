﻿#pragma once
#ifdef XREPROPS_EXPORTS
#define smart_cast   dynamic_cast
#define XREPROPS_API __declspec(dllexport)
#else
#define XREPROPS_API __declspec(dllimport)
#endif

#include <limits>
#include "../../xrCore/xrCore.h"
#ifdef XREPROPS_EXPORTS
inline void not_implemented()
{
    if (IsDebuggerPresent())
        DebugBreak();
    else
        R_ASSERT(0);
}
#endif

#include "../xrEUI/stdafx.h"
#include "../../xrEngine/stdafx.h"
#include "../Public/xrEProps.h"
#include "../../xrCore/ChooseTypes.H"
#include "FolderLib.h"
#include "Tree/Base/UITreeItem.h"
#include "ItemListHelper.h"
#include "UITextForm.h"
#include "Tree/Properties/UIPropertiesItem.h"
#include "Tree/Properties/UIPropertiesForm.h"
#include "UIItemListForm.h"
#include "Tree/Choose/UIChooseFormItem.h"
#include "Tree/Choose/UIChooseForm.h"
#include "UIKeyPressForm.h"
