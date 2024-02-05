// File:		UIDebugFonts.h
// Description:	Output list of all fonts
// Created:		22.03.2005
// Author:		Serge Vynnychenko
// Mail:		narrator@gsc-game.kiev.ua
//
// Copyright 2005 GSC Game World

#pragma once

#include "UIStatic.h"
#include "UIDialogWnd.h"

class CUIDebugFonts : public CUIDialogWnd 
{
public:
				CUIDebugFonts		();
				~CUIDebugFonts		() override;

			void InitDebugFonts		(Frect r);
				bool OnKeyboardAction			(int dik, EUIMessages keyboard_action) override;
			void FillUpList			();
protected:
	CUIStatic  m_background;
};