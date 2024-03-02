#ifndef xr_device
#define xr_device
#pragma once

// Note:
// ZNear - always 0.0f
// ZFar  - always 1.0f

//class	ENGINE_API	CResourceManager;
//class	ENGINE_API	CGammaControl;

#include "pure.h"
//#include "hw.h"
#include "../xrcore/ftimer.h"
#include "stats.h"
//#include "shader.h"
//#include "R_Backend.h"

#define VIEWPORT_NEAR  0.2f
#define HUD_VIEWPORT_NEAR 0.005f
extern ENGINE_API int psSVPFrameDelay;

enum ViewPort;

#define DEVICE_RESET_PRECACHE_FRAME_COUNT 10


#include "../Include/xrRender/FactoryPtr.h"
#include "../Include/xrRender/RenderDeviceRender.h"
#include "../xrCore/Threading/Event.hpp"

#ifdef INGAME_EDITOR
#	include "../Include/editor/interfaces.hpp"
#endif // #ifdef INGAME_EDITOR


#include "xrDeviceInterface.h"

class engine_impl;

#pragma pack(push,4)

class IRenderDevice
{
public:
	virtual		CStatsPhysics*	_BCL		StatPhysics		()							= 0;								
	virtual				void	_BCL		AddSeqFrame		( pureFrame* f, bool mt )	= 0;
	virtual				void	_BCL		RemoveSeqFrame	( pureFrame* f )			= 0;
};

class ENGINE_API CRenderDeviceData
{

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
//	CStats*									Statistic;

};

class	ENGINE_API CRenderDeviceBase :
	public IRenderDevice,
	public CRenderDeviceData,
	public xrDeviceInterface
{
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
};

class ENGINE_API CSecondVPParams //--#SM+#-- +SecondVP+
{
	bool isActive;	// Флаг активации рендера во второй вьюпорт
	u8 frameDelay;  // На каком кадре с момента прошлого рендера во второй вьюпорт мы начнём новый
					//(не может быть меньше 2 - каждый второй кадр, чем больше тем более низкий FPS во втором вьюпорте)

public:
	bool isCamReady; // Флаг готовности камеры (FOV, позиция, и т.п) к рендеру второго вьюпорта

	u32 screenWidth;
	u32 screenHeight;

	bool isR1;

	IC bool IsSVPActive() { return isActive; }
	IC void SetSVPActive(bool bState);
	bool    IsSVPFrame();

	IC u8 GetSVPFrameDelay() { return frameDelay; }
	void  SetSVPFrameDelay(u8 iDelay)
	{
		frameDelay = iDelay;
		clamp<u8>(frameDelay, 1, u8(-1));
	}
};

#pragma pack(pop)
// refs
class ENGINE_API CRenderDevice : public CRenderDeviceBase
{
private:
    // Main objects used for creating and rendering the 3D scene
    u32										m_dwWindowStyle;
    RECT									m_rcWindowBounds;
    RECT									m_rcWindowClient;

	//u32										Timer_MM_Delta;
	//CTimer_paused							Timer;
	//CTimer_paused							TimerGlobal;
	CTimer_paused_ex						TimerMM;

	void									_Create		(LPCSTR shName);
	void									_Destroy	(BOOL	bKeepTextures);
	void									_SetupStates();
public:
 //   HWND									m_hWnd;
	LRESULT									MsgProc		(HWND,UINT,WPARAM,LPARAM);

//	u32										dwFrame;
//	u32										dwPrecacheFrame;
	u32										dwPrecacheTotal;

//	u32										dwWidth, dwHeight;
	float									fWidth_2, fHeight_2;
//	BOOL									b_is_Ready;
//	BOOL									b_is_Active;
	void									OnWM_Activate(WPARAM wParam, LPARAM lParam);
public:
	//ref_shader								m_WireShader;
	//ref_shader								m_SelectionShader;

	IRenderDeviceRender						*m_pRender;

	BOOL									m_bNearer;
	void									SetNearer	(BOOL enabled)
	{
		if (enabled&&!m_bNearer){
			m_bNearer						= TRUE;
			mProject._43					-= EPS_L;
		}else if (!enabled&&m_bNearer){
			m_bNearer						= FALSE;
			mProject._43					+= EPS_L;
		}
		m_pRender->SetCacheXform(mView, mProject);
		//R_ASSERT(0);
		//	TODO: re-implement set projection
		//RCache.set_xform_project			(mProject);
	}

	void									DumpResourcesMemoryUsage() { m_pRender->ResourcesDumpMemoryUsage();}
public:
	// Registrators
	CRegistrator	<pureFrame			>			seqFrameMT;
	CRegistrator	<pureDeviceReset	>			seqDeviceReset;
	xr_vector		<fastdelegate::FastDelegate0<> >	seqParallel;
	CSecondVPParams m_SecondViewport;	//--#SM+#-- +SecondVP+

	// Dependent classes

	CStats*	Statistic;
	Fmatrix	mInvFullTransform;

	bool m_bMakeLevelMap = false;
	Fbox curr_lm_fbox;

	// Saved main viewport params
	Fvector mainVPCamPosSaved;
	Fmatrix mainVPFullTrans;
	Fmatrix mainVPViewSaved;
	Fmatrix mainVPProjectSaved;

private:
	CRenderDevice			()
		:
		m_pRender(0)
#ifdef INGAME_EDITOR
		,m_editor_module(0),
		m_editor_initialize(0),
		m_editor_finalize(0),
		m_editor(0),
		m_engine(0)
#endif // #ifdef INGAME_EDITOR
#ifdef PROFILE_CRITICAL_SECTIONS
		,mt_csEnter(MUTEX_PROFILE_ID(CRenderDevice::mt_csEnter))
		,mt_csLeave(MUTEX_PROFILE_ID(CRenderDevice::mt_csLeave))
#endif // #ifdef PROFILE_CRITICAL_SECTIONS
	{
	    m_hWnd              = NULL;
		b_is_Active			= FALSE;
		b_is_Ready			= FALSE;
		Timer.Start			();
		m_bNearer			= FALSE;
		//--#SM+#-- +SecondVP+
		m_SecondViewport.SetSVPActive(false);
		m_SecondViewport.SetSVPFrameDelay((u8)psSVPFrameDelay); // Change it to 2-3, if you want to save perfomance. Will cause skips in updating image in scope
		m_SecondViewport.isCamReady = false;
		m_SecondViewport.isR1 = false;
	};
public:

	static CRenderDevice* GetInstance()
	{
		static CRenderDevice instance;
		return &instance;
	}

	virtual void	Pause							(BOOL bOn, BOOL bTimer, BOOL bSound, LPCSTR reason) override;
	virtual bool	Paused							() const override;

private:
	static void SecondaryThreadProc			(void* context);
public:
	// Scene control
	virtual void PreCache							(u32 amount, bool b_draw_loadscreen, bool b_wait_user_input) override;
	virtual bool Begin						() override;
	virtual void Clear								() override;
	virtual void End								() override;
	void FrameMove							();

	bool bMainMenuActive					();
	
	void overdrawBegin						();
	void overdrawEnd						();

	// Mode control
	void DumpFlags							();
	IC	 CTimer_paused* GetTimerGlobal		()	{ return &TimerGlobal;								}
	u32	 TimerAsync							()	{ return TimerGlobal.GetElapsed_ms();				}
	u32	 TimerAsync_MMT						()	{ return TimerMM.GetElapsed_ms() +	Timer_MM_Delta; }

	// Creation & Destroying
	void ConnectToRender();
	void Create								(void);
	void Run								(void);
	void Destroy							(void);
	void Reset								(bool precache = true);

	void Initialize							(void);
	void ShutDown							(void);

public:
	void time_factor						(const float &time_factor)
	{
		Timer.time_factor		(time_factor);
		TimerGlobal.time_factor	(time_factor);
	}
	
	IC	const float &time_factor			() const
	{
		VERIFY					(Timer.time_factor() == TimerGlobal.time_factor());
		return					(Timer.time_factor());
	}

private:
	Event syncProcessFrame, syncFrameDone, syncThreadExit;
public:
	volatile BOOL		mt_bMustExit;

	ICF		void			remove_from_seq_parallel	(const fastdelegate::FastDelegate0<> &delegate)
	{
		xr_vector<fastdelegate::FastDelegate0<> >::iterator I = std::find(
			seqParallel.begin(),
			seqParallel.end(),
			delegate
		);
		if (I != seqParallel.end())
			seqParallel.erase	(I);
	}

public:
			void xr_stdcall		on_idle				();
			bool xr_stdcall		on_message			(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT &result);

private:
			void					message_loop		();
virtual		void			_BCL	AddSeqFrame			( pureFrame* f, bool mt );
virtual		void			_BCL	RemoveSeqFrame		( pureFrame* f );
virtual		CStatsPhysics*	_BCL	StatPhysics			()	{ return  Statistic ;}
#ifdef INGAME_EDITOR
public:
	IC		editor::ide			*editor				() const { return m_editor; }

private:
			void				initialize_editor	();
			void				message_loop_editor	();

private:
	typedef editor::initialize_function_ptr			initialize_function_ptr;
	typedef editor::finalize_function_ptr			finalize_function_ptr;

private:
	HMODULE						m_editor_module;
	initialize_function_ptr		m_editor_initialize;
	finalize_function_ptr		m_editor_finalize;
	editor::ide					*m_editor;
	engine_impl					*m_engine;
#endif // #ifdef INGAME_EDITOR
};

//#ifdef ENGINE_BUILD
//extern CRenderDevice* EngineDevice;
//#endif

//extern		ENGINE_API		CRenderDevice*		EngineDevice;
extern		ENGINE_API		bool				prefetching_in_progress;

#ifndef	_EDITOR
#define	RDEVICE	(*CRenderDevice::GetInstance())
#else
#define RDEVICE	EDevice
#endif


extern		ENGINE_API		bool				g_bBenchmark;

typedef fastdelegate::FastDelegate0<bool>		LOADING_EVENT;
extern	ENGINE_API xr_list<LOADING_EVENT>		g_loading_events;

class ENGINE_API CLoadScreenRenderer :public pureRender
{
public:
					CLoadScreenRenderer	();
	void			start				(bool b_user_input);
	void			stop				();
	virtual void	OnRender			();
	bool IsActive() const { return b_registered; }

	bool			b_registered;
	bool			b_need_user_input;
};
extern ENGINE_API CLoadScreenRenderer load_screen_renderer;
extern ENGINE_API float fps_limit;

#endif