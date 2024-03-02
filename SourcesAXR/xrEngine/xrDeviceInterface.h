#pragma once

#include "pure.h"
#include "stats.h"
//#include "FactoryPtr.h"
#include "../Include/xrRender/RenderDeviceRender.h"

//#ifdef INGAME_EDITOR
//#include "../xrWeatherEditor/Public/interfaces.hpp"
//#endif   // #ifdef INGAME_EDITOR

#define VIEWPORT_NEAR                     0.2f

#define DEVICE_RESET_PRECACHE_FRAME_COUNT 10

class ENGINE_API xrDeviceInterface
{
public:
    xrDeviceInterface();
    virtual ~xrDeviceInterface();

public:
//#ifdef INGAME_EDITOR
//    virtual xrWeatherEditor::ide* WeatherEditor() const
//    {
//        return nullptr;
//    }
//#endif
#ifndef MASTER_GOLD
    virtual bool IsEditorMode()
    {
        return false;
    }
#else
    constexpr bool IsEditorMode()
    {
        return false;
    }
#endif
    virtual bool Paused() const               = 0;
    virtual void Reset(bool precache = false) = 0;
    IC u32       TimerAsync()
    {
        return get_TimerGlobal().GetElapsed_ms();
    }
    IC u32 TimerAsync_MMT()
    {
        return TimerMM.GetElapsed_ms() + get_Timer_MM_Delta();
    }
    IC CTimer* GetTimerGlobal()
    {
        return &get_TimerGlobal();
    }
    virtual void DumpResourcesMemoryUsage()
    {
        m_pRender->ResourcesDumpMemoryUsage();
    }

    Fmatrix                                  mInvFullTransform;
    CTimer                                   TimerMM;
    CRegistrator<pureFrame>                  seqFrameMT;
    CRegistrator<pureDeviceReset>            seqDeviceReset;
    xr_vector<fastdelegate::FastDelegate0<>> seqParallel;
    CStats*                                  Statistic;
    float                                    fWidth_2, fHeight_2;
    IRenderDeviceRender*                     m_pRender;
    IC void                                  time_factor(const float& time_factor)
    {
        get_Timer().time_factor(time_factor);
        get_TimerGlobal().time_factor(time_factor);
    }

    IC const float& time_factor() const
    {
        VERIFY(get_Timer().time_factor() == get_TimerGlobal().time_factor());
        return (get_Timer().time_factor());
    }

    // Multi-threading
    xrCriticalSection mt_csEnter;
    xrCriticalSection mt_csLeave;
    volatile BOOL     mt_bMustExit;

    ICF void          remove_from_seq_parallel(const fastdelegate::FastDelegate0<>& delegate)
    {
        xr_vector<fastdelegate::FastDelegate0<>>::iterator I = std::find(seqParallel.begin(), seqParallel.end(), delegate);
        if (I != seqParallel.end())
            seqParallel.erase(I);
    }
    virtual void Pause(BOOL bOn, BOOL bTimer, BOOL bSound, LPCSTR reason)             = 0;
    virtual void PreCache(u32 amount, bool b_draw_loadscreen, bool b_wait_user_input) = 0;
    virtual void Clear()                                                              = 0;
    BOOL         m_bNearer;
    IC void      SetNearer(BOOL enabled)
    {
        if (enabled && !m_bNearer)
        {
            m_bNearer = TRUE;
            get_mProject()._43 -= EPS_L;
        }
        else if (!enabled && m_bNearer)
        {
            m_bNearer = FALSE;
            get_mProject()._43 += EPS_L;
        }
        m_pRender->SetCacheXform(get_mView(), get_mProject());
        // R_ASSERT(0);
        //	TODO: re-implement set projection
        // RCache.set_xform_project			(mProject);
    }
    virtual bool Begin() = 0;
    virtual void End()   = 0;

public:
    virtual bool get_dwMaximized() const = 0;
    virtual void set_dwMaximized(bool dwMaximized) = 0;
    virtual u32 get_dwWidth() const = 0;
    virtual void set_dwWidth(u32 dwWidth) = 0;
    virtual u32 get_dwHeight() const = 0;
    virtual void set_dwHeight(u32 dwHeight) = 0;
    virtual u32 get_dwPrecacheFrame() const = 0;
    virtual void set_dwPrecacheFrame(u32 dwPrecacheFrame) = 0;
    virtual BOOL get_b_is_Ready() const = 0;
    virtual void set_b_is_Ready(BOOL b_is_Ready) = 0;
    virtual BOOL get_b_is_Active() const = 0;
    virtual void set_b_is_Active(BOOL b_is_Active) = 0;

public:
    // Engine flow-control

    virtual s32 get_dwFrame() const = 0;
    virtual void set_dwFrame(s32 dwFrame) = 0;

    virtual float get_fTimeDelta() const = 0;
    virtual void set_fTimeDelta(float dwFrame) = 0;
    virtual float get_fTimeGlobal() const = 0;
    virtual void set_fTimeGlobal(float dwFrame) = 0;
    virtual s32 get_dwTimeDelta() const = 0;;
    virtual void set_dwTimeDelta(s32 dwFrame) = 0;
    virtual u32 get_dwTimeGlobal() const = 0;
    virtual void set_dwTimeGlobal(u32 dwFrame) = 0;
    virtual u32 get_dwTimeContinual() const = 0;
    virtual void set_dwTimeContinual(u32 dwFrame) = 0;

    virtual Fvector& get_vCameraPosition() = 0;
    virtual const Fvector& get_vCameraPosition() const = 0;
    virtual Fvector& get_vCameraDirection() = 0;
    virtual const Fvector& get_vCameraDirection() const = 0;;
    virtual Fvector& get_vCameraTop() = 0;
    virtual const Fvector& get_vCameraTop() const = 0;
    virtual Fvector& get_vCameraRight() = 0;
    virtual const Fvector& get_vCameraRight() const = 0;

    virtual Fmatrix& get_mView() = 0;
    virtual const Fmatrix& get_mView() const = 0;
    virtual Fmatrix& get_mProject() = 0;
    virtual const Fmatrix& get_mProject() const = 0;
    virtual Fmatrix& get_mFullTransform() = 0;
    virtual const Fmatrix& get_mFullTransform() const = 0;

    // Copies of corresponding members. Used for synchronization.
    virtual Fvector& get_vCameraPosition_saved() = 0;
    virtual const Fvector& get_vCameraPosition_saved() const = 0;

    virtual Fmatrix& get_mView_saved() = 0;
    virtual const Fmatrix& get_mView_saved() const = 0;
    virtual Fmatrix& get_mProject_saved() = 0;
    virtual const Fmatrix& get_mProject_saved() const = 0;
    virtual Fmatrix& get_mFullTransform_saved() = 0;
    virtual const Fmatrix& get_mFullTransform_saved() const = 0;

    virtual float get_fFOV() const = 0;
    virtual void set_fFOV(float fFOV) = 0;
    virtual float get_fASPECT() const = 0;
    virtual void set_fASPECT(float dwFrame) = 0;

protected:

    virtual u32 get_Timer_MM_Delta() const = 0;
    virtual void set_Timer_MM_Delta(u32 Timer_MM_Delta) = 0;

    virtual const CTimer_paused& get_Timer() const = 0;
    virtual CTimer_paused& get_Timer() = 0;
    virtual const CTimer_paused& get_TimerGlobal() const = 0;
    virtual CTimer_paused& get_TimerGlobal() = 0;


public:
    // Registrators
    virtual const CRegistrator<pureRender>& get_seqRender() const = 0;
    virtual CRegistrator<pureRender>& get_seqRender() = 0;
    virtual const CRegistrator<pureAppActivate>& get_seqAppActivate() const = 0;
    virtual CRegistrator<pureAppActivate>& get_seqAppActivate() = 0;
    virtual const CRegistrator<pureAppDeactivate>& get_seqAppDeactivate() const = 0;
    virtual CRegistrator<pureAppDeactivate>& get_seqAppDeactivate() = 0;
    virtual const CRegistrator<pureAppStart>& get_seqAppStart() const = 0;
    virtual CRegistrator<pureAppStart>& get_seqAppStart() = 0;
    virtual const CRegistrator<pureAppEnd>& get_seqAppEnd() const = 0;
    virtual CRegistrator<pureAppEnd>& get_seqAppEnd() = 0;
    virtual const CRegistrator<pureFrame>& get_seqFrame() const = 0;
    virtual CRegistrator<pureFrame>& get_seqFrame() = 0;
    virtual const CRegistrator<pureScreenResolutionChanged>& get_seqResolutionChanged() const = 0;
    virtual CRegistrator<pureScreenResolutionChanged>& get_seqResolutionChanged() = 0;
    virtual const CRegistrator<pureDrawUI>& get_seqDrawUI() const = 0;
    virtual CRegistrator<pureDrawUI>& get_seqDrawUI() = 0;

    virtual HWND get_m_hWnd() const = 0;
    virtual void set_m_hWnd(HWND m_hWnd) = 0;
    //	CStats*									Statistic;

public:
    virtual CStatsPhysics* _BCL StatPhysics()                      = 0;
    virtual void _BCL           AddSeqFrame(pureFrame* f, bool mt) = 0;
    virtual void _BCL           RemoveSeqFrame(pureFrame* f)       = 0;
};
