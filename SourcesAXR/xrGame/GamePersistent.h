#ifndef GamePersistentH
#define GamePersistentH
#pragma once

#include "../xrEngine/IGame_Persistent.h"
class CMainMenu;
class CUICursor;
class CParticlesObject;
class CUISequencer;
class ui_core;

class CGamePersistent: 
	public IGame_Persistent, 
	public IEventReceiver
{
	enum
	{
		eDofDest = 0,
		eDofCurrent,
		eDofFrom,
		eDofOriginal,

		eDofParamsCount,
	};

	// ambient particles
	CParticlesObject*	ambient_particles; 
	u32					ambient_sound_next_time		[20]; //max snd channels
	u32					ambient_effect_next_time;
	u32					ambient_effect_stop_time;

	float				ambient_effect_wind_start;
	float				ambient_effect_wind_in_time;
	float				ambient_effect_wind_end;
	float				ambient_effect_wind_out_time;
	bool				ambient_effect_wind_on;

	bool				ls_tips_enabled;

	bool				m_bPickableDOF;

	CUISequencer*		m_intro;
	EVENT				eQuickLoad;
	Fvector 			m_dof[eDofParamsCount]; // 0-dest 1-current 2-from 3-original

	fastdelegate::FastDelegate0<> m_intro_event;

	void xr_stdcall		start_logo_intro		();
	void xr_stdcall		update_logo_intro		();

	void xr_stdcall		game_loaded				();
	void xr_stdcall		update_game_loaded		();

	void xr_stdcall		start_game_intro		();
	void xr_stdcall		update_game_intro		();

#ifdef DEBUG
	u32					m_frame_counter;
	u32					m_last_stats_frame;
#endif

	void				WeathersUpdate			();
	void				UpdateDof				();

public:
	ui_core*			m_pUI_core;
	IReader*			pDemoFile;
	u32					uTime2Change;
	EVENT				eDemoStart;

						CGamePersistent			();
	virtual				~CGamePersistent		();

			void		PreStart				(LPCSTR op) override;
	virtual void		Start					(LPCSTR op);
	virtual void		Disconnect				();

	virtual	void		OnAppActivate			();
	virtual void		OnAppDeactivate			();

	virtual void		OnAppStart				();
	virtual void		OnAppEnd				();
	virtual	void		OnGameStart				();
	virtual void		OnGameEnd				();

	virtual void	_BCL	OnFrame					();
	virtual void			OnEvent					(EVENT E, u64 P1, u64 P2);

	virtual void		UpdateGameType			();

	virtual void		RegisterModel			(IRenderVisual* V);
	virtual	float		MtlTransparent			(u32 mtl_idx);
	virtual	void		Statistics				(CGameFont* F);

	virtual bool		OnRenderPPUI_query		();
	virtual void		OnRenderPPUI_main		();
	virtual void		OnRenderPPUI_PP			();
	virtual	void		LoadTitle				(bool change_tip = false, shared_str map_name = "");
	void				SetLoadStageTitle		(const char* ls_title = nullptr) override;

	virtual bool		CanBePaused				();

			void		SetPickableEffectorDOF	(bool bSet);
			void		SetEffectorDOF			(const Fvector& needed_dof);
			void		RestoreEffectorDOF		();

	virtual void		GetCurrentDof			(Fvector3& dof);
	virtual void		SetBaseDof				(const Fvector3& dof);
	virtual void		OnSectorChanged			(int sector);
	virtual void		OnAssetsChanged			();
			int			GetHudGlassElement		();
			int			GetNightvisionType		();
			bool		GetHudGlassEnabled		();
			bool		GetActorNightvision		();
			float		GetActorMaxHealth		() override;
			float		GetActorHealth			() override;
			float		GetActorMaxPower		() override;
			float		GetActorPower			() override;
			float		GetActorBleeding		() override;
			float		GetActorIntoxication	() override;
			bool		GetClearMaskProcess		() override;
			bool		GetActorAliveStatus		();
			bool		GetActor				();
			bool		IsCamFirstEye			();
			bool		GetActorHelmetStatus	();
			bool		GetFogInfluenceVolumetricLight();
			std::string	GetMoonPhase			() override;
			u32			GetTimeHours			() override;

	virtual void		EditorOnFrame			();

	xr_vector<fastdelegate::FastDelegate0<>>    GameLoadedCallback;
};

IC CGamePersistent&		GamePersistent()		{ return *static_cast<CGamePersistent*>(g_pGamePersistent);			}

#endif //GamePersistentH

