﻿#pragma once

enum
{
    COMMAND_EXTFIRST_EXT = COMMAND_MAIN_LAST - 1,

    COMMAND_VALIDATE,

    COMMAND_SELECT_PREVIEW_OBJ,
    COMMAND_EDIT_PREVIEW_PROPS,

    COMMAND_PLAY_CURRENT,
    COMMAND_STOP_CURRENT,
    COMMAND_JUMP_TO_ITEM,
    COMMAND_SAVE_XR,
    COMMAND_LOAD_XR,
    COMMAND_COMPACT_PARTICLES,
    COMMAND_CREATE_GROUP_FROM_SELECTED
};
//------------------------------------------------------------------------------

class CParticleMain: public TUI
{
    typedef TUI  inherited;

    virtual void RealUpdateScene();
    virtual void RealQuit();

public:
    CParticleMain();
    virtual ~CParticleMain();

    virtual LPSTR  GetCaption();

    virtual void   ResetStatus();
    virtual void   SetStatus(LPCSTR s, bool bOutLog);
    virtual void   ProgressDraw();
    virtual void   OutCameraPos();
    virtual void   OutUICursorPos();
    virtual void   OutGridSize();
    virtual void   OutInfo();

    virtual LPCSTR EditorName()
    {
        return "particle";
    }
    virtual LPCSTR EditorDesc()
    {
        if (xrGameManager::GetGame() == EGame::SHOC)
            return "Particle Editor [ShoC]";
        else if (xrGameManager::GetGame() == EGame::CS)
            return "Particle Editor [CS]";
        else
            return "Particle Editor [CoP]";
    }
    HICON        EditorIcon() override;

    virtual bool ApplyShortCut(DWORD Key, TShiftState Shift);
    virtual bool ApplyGlobalShortCut(DWORD Key, TShiftState Shift);

    // commands
    virtual void RegisterCommands();
    virtual void OnDrawUI();
};
extern CParticleMain* PUI;
