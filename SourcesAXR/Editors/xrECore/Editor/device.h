#pragma once

#include "../../../xrengine/xrDeviceInterface.h"
#include "ui_camera.h"
#include "../../../Layers/xrRender/hwcaps.h"
#include "../../../Layers/xrRender/hw.h"
#include "../../../xrEngine/pure.h"
#include "../../../xrCore/ftimer.h"
#include "estats.h"
#include "../../../xrEngine/shader_xrlc.h"
#include "../../../Layers/xrRender/shader.h"
#include "../../../Layers/xrRender/R_Backend.h"
#include "../../../xrEngine/_d3d_extensions.h"

//---------------------------------------------------------------------------
// refs
class CGameFont;
class CInifile;
class CResourceManager;
#undef CreateWindow
//------------------------------------------------------------------------------
class ECORE_API CEditorRenderDevice: public xrDeviceInterface
{
    friend class CUI_Camera;
    friend class TUI;
    HMODULE    hPSGP;
    float      m_fNearer;

    // u32						Timer_MM_Delta;
    // CTimer					Timer;
    // CTimer					TimerGlobal;

    ref_shader m_CurrentShader;

    void       _SetupStates();
    void       _Create(IReader* F);
    void       _Destroy(BOOL bKeepTextures);
    xr_string  _GetWindowTitle();

public:
    ref_shader m_WireShader;
    ref_shader m_SelectionShader;

    Fmaterial  m_DefaultMat;

public:
    float RadiusRender;
    // u32 					dwWidth, dwHeight;
    u32   dwRealWidth, dwRealHeight;
    float m_RenderArea;
    float m_ScreenQuality;

    u32   dwFillMode;
    u32   dwShadeMode;

public:
    //   HWND 					m_hWnd;

    //	u32						dwFrame;
    //	u32						dwPrecacheFrame;

    //	BOOL					b_is_Ready;
    //	BOOL					b_is_Active;

    // Engine flow-control
    // float					fTimeDelta;
    // float					fTimeGlobal;
    // u32						dwTimeDelta;
    // u32						dwTimeGlobal;
    //   u32						dwTimeContinual;

    // camera
    CUI_Camera        m_Camera;

    //   Fvector					vCameraPosition;
    //   Fvector					vCameraDirection;
    //   Fvector					vCameraTop;
    //   Fvector					vCameraRight;
    //
    // Fmatrix					mView;
    // Fmatrix 				mProjection;
    // Fmatrix					mFullTransform;

    //   float					fFOV;
    // float					fASPECT;

    // Dependent classes
    CResourceManager* Resources;
    CEStats*          EStatistic;

    CGameFont*        pSystemFont;

    // registrators
    //	CRegistrator <pureDeviceDestroy>	seqDevDestroy;
    //	CRegistrator <pureDeviceCreate>		seqDevCreate;

    // CRegistrator <pureFrame>					seqFrame;
    // CRegistrator <pureRender>					seqRender;
    // CRegistrator <pureAppStart>					seqAppStart;
    // CRegistrator <pureAppEnd>					seqAppEnd;
    // CRegistrator <pureAppActivate	>			seqAppActivate;
    // CRegistrator <pureAppDeactivate	>			seqAppDeactivate;

public:
    CEditorRenderDevice();
    virtual ~CEditorRenderDevice();

    virtual bool Paused() const
    {
        return FALSE;
    };
    void         time_factor(float);
    bool         Create();
    void         Destroy();
    void         Resize(int w, int h, bool maximized);
    void         ReloadTextures();
    void         UnloadTextures();

    void         RenderNearer(float f_Near);
    void         ResetNearer();
    bool         Begin();
    void         End();

    void         Initialize(void);
    void         ShutDown(void);
    void         Reset(IReader* F, BOOL bKeepTextures);

    virtual void DumpResourcesMemoryUsage() {}
    IC float     GetRenderArea()
    {
        return m_RenderArea;
    }
    // Sprite rendering
    IC float _x2real(float x)
    {
        return (x + 1) * dwWidth * 0.5f;
    }
    IC float _y2real(float y)
    {
        return (y + 1) * dwHeight * 0.5f;
    }

    // draw
    void SetShader(ref_shader sh)
    {
        m_CurrentShader = sh;
    }
    void    DP(D3DPRIMITIVETYPE pt, ref_geom geom, u32 startV, u32 pc);
    void    DIP(D3DPRIMITIVETYPE pt, ref_geom geom, u32 baseV, u32 startV, u32 countV, u32 startI, u32 PC);

    IC void SetRS(D3DRENDERSTATETYPE p1, u32 p2)
    {
        VERIFY(b_is_Ready);
        CHK_DX(HW.pDevice->SetRenderState(p1, p2));
    }
    IC void SetSS(u32 sampler, D3DSAMPLERSTATETYPE type, u32 value)
    {
        VERIFY(b_is_Ready);
        CHK_DX(HW.pDevice->SetSamplerState(sampler, type, value));
    }

    // light&material
    IC void LightEnable(u32 dwLightIndex, BOOL bEnable)
    {
        CHK_DX(HW.pDevice->LightEnable(dwLightIndex, bEnable));
    }
    IC void SetLight(u32 dwLightIndex, Flight& lpLight)
    {
        CHK_DX(HW.pDevice->SetLight(dwLightIndex, (D3DLIGHT9*)&lpLight));
    }
    IC void SetMaterial(Fmaterial& mat)
    {
        CHK_DX(HW.pDevice->SetMaterial((D3DMATERIAL9*)&mat));
    }
    IC void ResetMaterial()
    {
        CHK_DX(HW.pDevice->SetMaterial((D3DMATERIAL9*)&m_DefaultMat));
    }

    // update
    void         UpdateView();
    void         FrameMove();

    bool         MakeScreenshot(U32Vec& pixels, u32 width, u32 height);

    void         InitTimer();
    // Mode control
    virtual void Pause(BOOL bOn, BOOL bTimer, BOOL bSound, LPCSTR reason) {}
    virtual void PreCache(u32 amount, bool b_draw_loadscreen, bool b_wait_user_input) {}
    virtual void Clear() {}

public:
    Shader_xrLC_LIB ShaderXRLC;

private:
    virtual CStatsPhysics* _BCL StatPhysics();
    virtual void _BCL           AddSeqFrame(pureFrame* f, bool mt);
    virtual void _BCL           RemoveSeqFrame(pureFrame* f);

private:
    WNDCLASSEX m_WC;

public:
    void         CreateWindow();
    void         DestryWindow();
    virtual bool IsEditorMode()
    {
        return true;
    }
    virtual void Reset(bool precache);

    //TODO: Maybe combine editor and game device classes?

protected:

    virtual u32 get_Timer_MM_Delta() const override { return Timer_MM_Delta; };
    virtual void set_Timer_MM_Delta(u32 Timer_MM_Delta) override { this->Timer_MM_Delta = Timer_MM_Delta; };

    virtual const CTimer_paused& get_Timer() const override { return Timer; };
    virtual CTimer_paused& get_Timer() override { return Timer; };
    virtual const CTimer_paused& get_TimerGlobal() const override { return TimerGlobal; };
    virtual CTimer_paused& get_TimerGlobal() override { return TimerGlobal; };

public:
    // Engine flow-control

    virtual s32 get_dwFrame() const override { return dwFrame; };
    virtual void set_dwFrame(s32 dwFrame) override { this->dwFrame = dwFrame; };

    virtual float get_fTimeDelta() const override { return fTimeDelta; };
    virtual void set_fTimeDelta(float fTimeDelta) override { this->fTimeDelta = fTimeDelta; };
    virtual float get_fTimeGlobal() const override { return fTimeGlobal; };
    virtual void set_fTimeGlobal(float fTimeGlobal) override { this->fTimeGlobal = fTimeGlobal; };
    virtual s32 get_dwTimeDelta() const override { return dwTimeDelta; };
    virtual void set_dwTimeDelta(s32 dwTimeDelta) override { this->dwTimeDelta = dwTimeDelta; };
    virtual u32 get_dwTimeGlobal() const override { return dwTimeGlobal; };
    virtual void set_dwTimeGlobal(u32 dwTimeGlobal) override { this->dwTimeGlobal = dwTimeGlobal; };
    virtual u32 get_dwTimeContinual() const override { return dwTimeContinual; };
    virtual void set_dwTimeContinual(u32 dwTimeContinual) override { this->dwTimeContinual = dwTimeContinual; };

    virtual Fvector& get_vCameraPosition() override { return vCameraPosition; };
    virtual const Fvector& get_vCameraPosition() const override { return vCameraPosition; };
    virtual Fvector& get_vCameraDirection() override { return vCameraDirection; };
    virtual const Fvector& get_vCameraDirection() const override { return vCameraDirection; };
    virtual Fvector& get_vCameraTop() override { return vCameraTop; };
    virtual const Fvector& get_vCameraTop() const override { return vCameraTop; };
    virtual Fvector& get_vCameraRight() override { return vCameraRight; };
    virtual const Fvector& get_vCameraRight() const override { return vCameraRight; };

    virtual Fmatrix& get_mView() override { return mView; };
    virtual const Fmatrix& get_mView() const override { return mView; };
    virtual Fmatrix& get_mProject() override { return mProject; };
    virtual const Fmatrix& get_mProject() const override { return mProject; };
    virtual Fmatrix& get_mFullTransform() override { return mFullTransform; };
    virtual const Fmatrix& get_mFullTransform() const override { return mFullTransform; };

    // Copies of corresponding members. Used for synchronization.
    virtual Fvector& get_vCameraPosition_saved() override { return vCameraPosition_saved; };
    virtual const Fvector& get_vCameraPosition_saved() const override { return vCameraPosition_saved; };

    virtual Fmatrix& get_mView_saved() override { return mView_saved; };
    virtual const Fmatrix& get_mView_saved() const override { return mView_saved; };
    virtual Fmatrix& get_mProject_saved() override { return mProject_saved; };
    virtual const Fmatrix& get_mProject_saved() const override { return mProject_saved; };
    virtual Fmatrix& get_mFullTransform_saved() override { return mFullTransform_saved; };
    virtual const Fmatrix& get_mFullTransform_saved() const override { return mFullTransform_saved; };

    virtual float get_fFOV() const override { return fFOV; };
    virtual void set_fFOV(float fFOV) override { this->fFOV = fFOV; };
    virtual float get_fASPECT() const override { return fASPECT; };
    virtual void set_fASPECT(float dwFrame) override { this->fASPECT = fASPECT; };

    virtual bool get_dwMaximized() const override { return dwMaximized; }
    virtual void set_dwMaximized(bool dwMaximized) override { this->dwMaximized = dwMaximized; }
    virtual u32 get_dwWidth() const override { return dwWidth; }
    virtual void set_dwWidth(u32 dwWidth) override { this->dwWidth = dwWidth; }
    virtual u32 get_dwHeight() const override { return dwHeight; }
    virtual void set_dwHeight(u32 dwHeight) override { this->dwHeight = dwHeight; }
    virtual u32 get_dwPrecacheFrame() const override { return dwPrecacheFrame; }
    virtual void set_dwPrecacheFrame(u32 dwPrecacheFrame) override { this->dwPrecacheFrame = dwPrecacheFrame; }
    virtual BOOL get_b_is_Ready() const override { return b_is_Ready; };
    virtual void set_b_is_Ready(BOOL b_is_Ready) override { this->b_is_Ready = b_is_Ready; };
    virtual BOOL get_b_is_Active() const override { return b_is_Active; };
    virtual void set_b_is_Active(BOOL b_is_Active) override { this->b_is_Active = b_is_Active; };

    virtual HWND get_m_hWnd() const override { return m_hWnd; };
    virtual void set_m_hWnd(HWND m_hWnd) override { this->m_hWnd = m_hWnd; };

    virtual const CRegistrator<pureRender>& get_seqRender() const override { return seqRender; };
    virtual CRegistrator<pureRender>& get_seqRender() override { return seqRender; };
    virtual const CRegistrator<pureAppActivate>& get_seqAppActivate() const override { return seqAppActivate; };
    virtual CRegistrator<pureAppActivate>& get_seqAppActivate() override { return seqAppActivate; };
    virtual const CRegistrator<pureAppDeactivate>& get_seqAppDeactivate() const override { return seqAppDeactivate; };
    virtual CRegistrator<pureAppDeactivate>& get_seqAppDeactivate() override { return seqAppDeactivate; };
    virtual const CRegistrator<pureAppStart>& get_seqAppStart() const override { return seqAppStart; };
    virtual CRegistrator<pureAppStart>& get_seqAppStart() override { return seqAppStart; };
    virtual const CRegistrator<pureAppEnd>& get_seqAppEnd() const override { return seqAppEnd; };
    virtual CRegistrator<pureAppEnd>& get_seqAppEnd() override { return seqAppEnd; };
    virtual const CRegistrator<pureFrame>& get_seqFrame() const override { return seqFrame; };
    virtual CRegistrator<pureFrame>& get_seqFrame() override { return seqFrame; };
    virtual const CRegistrator<pureScreenResolutionChanged>& get_seqResolutionChanged() const override { return seqResolutionChanged; };
    virtual CRegistrator<pureScreenResolutionChanged>& get_seqResolutionChanged() override { return seqResolutionChanged; };
    virtual const CRegistrator<pureDrawUI>& get_seqDrawUI() const override { return seqDrawUI; };
    virtual CRegistrator<pureDrawUI>& get_seqDrawUI() override { return seqDrawUI; };

public:
    bool									dwMaximized;
    u32										dwWidth;
    u32										dwHeight;

    u32										dwPrecacheFrame;
    BOOL									b_is_Ready;
    BOOL									b_is_Active;
public:

    // Engine flow-control
    u32										dwFrame;

    float									fTimeDelta;
    float									fTimeGlobal;
    u32										dwTimeDelta;
    u32										dwTimeGlobal;
    u32										dwTimeContinual;

    Fvector									vCameraPosition;
    Fvector									vCameraDirection;
    Fvector									vCameraTop;
    Fvector									vCameraRight;

    Fmatrix									mView;
    Fmatrix									mProject;
    Fmatrix									mFullTransform;

    // Copies of corresponding members. Used for synchronization.
    Fvector									vCameraPosition_saved;

    Fmatrix									mView_saved;
    Fmatrix									mProject_saved;
    Fmatrix									mFullTransform_saved;

    float									fFOV;
    float									fASPECT;
protected:

    u32										Timer_MM_Delta;
    CTimer_paused							Timer;
    CTimer_paused							TimerGlobal;
public:

    // Registrators
    CRegistrator	<pureRender			>			seqRender;
    CRegistrator	<pureAppActivate	>			seqAppActivate;
    CRegistrator	<pureAppDeactivate	>			seqAppDeactivate;
    CRegistrator	<pureAppStart		>			seqAppStart;
    CRegistrator	<pureAppEnd			>			seqAppEnd;
    CRegistrator	<pureFrame			>			seqFrame;
    CRegistrator	<pureScreenResolutionChanged>	seqResolutionChanged;
    CRegistrator	<pureDrawUI			>           seqDrawUI;

    HWND									m_hWnd;
};

extern ECORE_API CEditorRenderDevice* EDevice;

// video
enum
{
    rsFilterLinear   = (1ul << 20ul),
    rsEdgedFaces     = (1ul << 21ul),
    rsRenderTextures = (1ul << 22ul),
    rsLighting       = (1ul << 23ul),
    rsFog            = (1ul << 24ul),
    rsRenderRealTime = (1ul << 25ul),
    rsDrawGrid       = (1ul << 26ul),
    rsDrawSafeRect   = (1ul << 27ul),
    rsMuteSounds     = (1ul << 28ul),
    rsEnvironment    = (1ul << 29ul),
};

#define DEFAULT_CLEARCOLOR 0x00555555

#define REQ_CREATE()      \
    if (!EDevice->bReady) \
        return;
#define REQ_DESTROY()    \
    if (EDevice->bReady) \
        return;

#include "../../../xrCPU_Pipe/xrCPU_Pipe.h"
ENGINE_API extern xrDispatchTable PSGP;

#include "../../../Layers/xrRender/R_Backend_Runtime.h"
