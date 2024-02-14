#pragma once

#include "../xrEngine/feel_touch.h"
#include "../xrEngine/feel_sound.h"
#include "../xrEngine/iinputreceiver.h"
#include "../Include/xrRender/KinematicsAnimated.h"
#include "actor_flags.h"
#include "actor_defs.h"
#include "fire_disp_controller.h"
#include "entity_alive.h"
#include "PHMovementControl.h"
#include "../xrphysics/PhysicsShell.h"
#include "InventoryOwner.h"
#include "../xrEngine/StatGraph.h"
#include "PhraseDialogManager.h"
#include "ui_defs.h"

#include "step_manager.h"
#include "script_export_space.h"
#include "xr_level_controller.h"

#include "ActorSkills.h"
#include "CustomTimer.h"

using namespace ACTOR_DEFS;

class CInfoPortion;
struct GAME_NEWS_DATA;
class CActorCondition;
class CCustomOutfit;
class CEncyclopediaRegistryWrapper;
class CGameTaskRegistryWrapper;
class CGameNewsRegistryWrapper;
class CCharacterPhysicsSupport;
class CActorCameraManager;
// refs
class ENGINE_API CCameraBase;
class ENGINE_API CBoneInstance;
class ENGINE_API CBlend;
class CWeaponList;
class CEffectorBobbing;
class CHolderCustom;
class CUsableScriptObject;

struct SShootingEffector;
struct SSleepEffector;
class  CSleepEffectorPP;
class CInventoryBox;

class	CHudItem;
class   CArtefact;

struct SActorMotions;
struct SActorVehicleAnims;
class  CActorCondition;
class SndShockEffector;
class CActorFollowerMngr;

struct CameraRecoil;
class CCameraShotEffector;
class CActorInputHandler;

class CActorMemory;
class CActorStatisticMgr;

class CLocationManager;

class CNightVisionEffector;

class	CActor: 
	public CEntityAlive, 
	public IInputReceiver,
	public Feel::Touch,
	public CInventoryOwner,
	public CPhraseDialogManager,
	public CStepManager,
	public Feel::Sound,
	public IMetaClass
#ifdef DEBUG
	,public pureRender
#endif
{
	DECLARE_METACLASS7(CActor, CEntityAlive, IInputReceiver, Feel::Touch, CInventoryOwner, CPhraseDialogManager, CStepManager, Feel::Sound)
	friend class CActorCondition;
private:
	typedef CEntityAlive	inherited;
public:
										CActor				();
	~CActor				() override;

public:
	BOOL						AlwaysTheCrow				() override { return TRUE; }

	CAttachmentOwner*			cast_attachment_owner		() override {return this;}
	CInventoryOwner*			cast_inventory_owner		() override {return this;}
	CActor*						cast_actor					() override {return this;}
	CGameObject*				cast_game_object			() override {return this;}
	IInputReceiver*				cast_input_receiver			() override {return this;}
	CCharacterPhysicsSupport*	character_physics_support	() override {return m_pPhysics_support;}
	CCharacterPhysicsSupport*	character_physics_support	() const override {return m_pPhysics_support;}
	CPHDestroyable*				ph_destroyable				() override;
			CHolderCustom*				Holder						()						{return m_holder;}
public:
	void						Load				( LPCSTR section ) override;

	void						shedule_Update		( u32 T ) override;
	void						UpdateCL			( ) override;

	void						OnEvent				( NET_Packet& P, u16 type		) override;

	// Render
	void						renderable_Render			() override;
	BOOL						renderable_ShadowGenerate	() override;
	void						feel_sound_new				(CObject* who, int type, CSound_UserDataPtr user_data, const Fvector& Position, float power) override;
	Feel::Sound*				dcast_FeelSound				() override { return this;	}
			float						m_snd_noise;
#ifdef DEBUG
	void						OnRender			() override;

#endif


public:
	bool OnReceiveInfo		(shared_str info_id) const override;
	void OnDisableInfo		(shared_str info_id) const override;

	void	 NewPdaContact		(CInventoryOwner*) override;
	void	 LostPdaContact		(CInventoryOwner*) override;

#ifdef DEBUG
	void			 DumpTasks();
#endif

protected:
	virtual void AddEncyclopediaArticle(const CInfoPortion* info_portion) const;

struct SDefNewsMsg{
		GAME_NEWS_DATA*	news_data;
		u32				time;
		bool operator < (const SDefNewsMsg& other) const {return time>other.time;}
	};
	xr_vector<SDefNewsMsg> m_defferedMessages;
	void UpdateDefferedMessages();	
public:	
	void			AddGameNews_deffered	 (GAME_NEWS_DATA& news_data, u32 delay);
	virtual void	AddGameNews				 (GAME_NEWS_DATA& news_data);
protected:
	CActorStatisticMgr*				m_statistic_manager;
public:
	virtual void StartTalk			(CInventoryOwner* talk_partner);
			void RunTalkDialog		(CInventoryOwner* talk_partner, bool disable_break);
	CActorStatisticMgr&				StatisticMgr()	{return *m_statistic_manager;}
	CEncyclopediaRegistryWrapper	*encyclopedia_registry;
	CGameNewsRegistryWrapper		*game_news_registry;
	CCharacterPhysicsSupport		*m_pPhysics_support;

	LPCSTR	Name        () const override {return CInventoryOwner::Name();}

public:
	//PhraseDialogManager
	void ReceivePhrase				(DIALOG_SHARED_PTR& phrase_dialog) override;
	void UpdateAvailableDialogs		(CPhraseDialogManager* partner) override;
	virtual void TryToTalk					();
			bool OnDialogSoundHandlerStart	(CInventoryOwner *inv_owner, LPCSTR phrase);
			bool OnDialogSoundHandlerStop	(CInventoryOwner *inv_owner);


	void reinit			() override;
	void reload			(LPCSTR section) override;
	bool use_bolts		() const override;

	void OnItemTake		(CInventoryItem *inventory_item) override;

	void OnItemRuck		(CInventoryItem *inventory_item, const SInvItemPlace& previous_place) override;
	void OnItemBelt		(CInventoryItem *inventory_item, const SInvItemPlace& previous_place) override;

	void OnItemDrop		(CInventoryItem *inventory_item, bool just_before_destroy) override;
	void OnItemDropUpdate () override;

	virtual	void OnPlayHeadShotParticle (NET_Packet P);


	void						Die				(CObject* who) override;
	void						Hit				(SHit* pHDS) override;
	void						PHHit			(SHit &H) override;
	void						HitSignal		(float P, Fvector &vLocalDir,	CObject* who, s16 element) override;
			void						HitSector		(CObject* who, CObject* weapon);
			void						HitMark			(float P, Fvector dir,			CObject* who, s16 element, Fvector position_in_bone_space, float impulse,  ALife::EHitType hit_type);

			void						Feel_Grenade_Update( float rad );

	float						GetMass				() override;
	float						Radius				() const override;
	virtual void						g_PerformDrop		();

	bool						use_default_throw_force	() override;
	float						missile_throw_force		() override;

	bool						unlimited_ammo			() override;

	bool						NeedToDestroyObject()  const override;
	virtual ALife::_TIME_ID				TimePassedAfterDeath() const;


public:

	//свойства артефактов
	virtual void		UpdateArtefactsOnBeltAndOutfit();
	virtual void		UpdateInventoryItems();
	virtual void		MoveArtefactBelt		(const CArtefact* artefact, bool on_belt);
			float		HitArtefactsOnBelt		(float hit_power, ALife::EHitType hit_type);
			float		GetProtection_ArtefactsOnBelt(ALife::EHitType hit_type);
			void		UpdateArtefactsOnBelt();
			void		UpdateArtefactsInRuck();
			void		UpdateSkills();
			void		UpdateNVGUseAnim();
			void		UpdateMaskUseAnim();
			void		UpdateQuickKickAnim();
			float		GetCamHeightFactor() { return m_fCamHeightFactor; }
			void		SetCamHeightFactor(float height) { m_fCamHeightFactor = height; }

	const xr_vector<const CArtefact*>& ArtefactsOnBelt() {return m_ArtefactsOnBelt;}
protected:
	//звук тяжелого дыхания
	ref_sound			m_HeavyBreathSnd;
	ref_sound			m_BloodSnd;
	ref_sound			m_DangerSnd;

	xr_vector<const CArtefact*> m_ArtefactsOnBelt;

protected:
	// Death
	float					m_hit_slowmo;
	float					m_hit_probability;
	s8						m_block_sprint_counter;

	// media
	SndShockEffector*		m_sndShockEffector;
	xr_vector<ref_sound>	sndHit[ALife::eHitTypeMax];
	ref_sound				sndDie[SND_DIE_COUNT];


	float					m_fLandingTime;
	float					m_fJumpTime;
	float					m_fFallTime;
	float					m_fCamHeightFactor;

	// Dropping
	BOOL					b_DropActivated;
	float					f_DropPower;

	//random seed для Zoom mode
	s32						m_ZoomRndSeed;
	//random seed для Weapon Effector Shot
	s32						m_ShotRndSeed;

	bool					m_bOutBorder;
	//сохраняет счетчик объектов в feel_touch, для которых необходимо обновлять размер колижена с актером 
	u32						m_feel_touch_characters;
private:
	void					SwitchOutBorder(bool new_border_state);
public:
	bool					m_bAllowDeathRemove;

	void					SetZoomRndSeed			(s32 Seed = 0);
	s32						GetZoomRndSeed			()	{ return m_ZoomRndSeed;	};
	void					SetShotRndSeed			(s32 Seed = 0);
	s32						GetShotRndSeed			()	{ return m_ShotRndSeed;	};

public:
	void					detach_Vehicle			();
	void					steer_Vehicle			(float angle);
	void					attach_Vehicle			(CHolderCustom* vehicle);
	bool					use_HolderEx			(CHolderCustom* object, bool bForce);

	bool			can_attach				(const CInventoryItem *inventory_item) const override;
protected:
	CHolderCustom*			m_holder;
	u16						m_holderID;
	bool					use_Holder				(CHolderCustom* holder);

	bool					use_Vehicle				(CHolderCustom* object);
	bool					use_MountedWeapon		(CHolderCustom* object);
	void					ActorUse				();

protected:
	BOOL					m_bAnimTorsoPlayed;
	static void				AnimTorsoPlayCallBack(CBlend* B);

	// Rotation
	SRotation				r_torso;
	float					r_torso_tgt_roll;
	//положение торса без воздействия эффекта отдачи оружия
	SRotation				unaffected_r_torso;

	//ориентация модели
	float					r_model_yaw_dest;
	float					r_model_yaw;			// orientation of model
	float					r_model_yaw_delta;		// effect on multiple "strafe"+"something"


public:
	SActorMotions*			m_anims;
	SActorVehicleAnims*		m_vehicle_anims;

	CBlend*					m_current_legs_blend;
	CBlend*					m_current_torso_blend;
	CBlend*					m_current_jump_blend;
	MotionID				m_current_legs;
	MotionID				m_current_torso;
	MotionID				m_current_head;

	// callback на анимации модели актера
	void					SetCallbacks		();
	void					ResetCallbacks		();
	static void		_BCL	Spin0Callback		(CBoneInstance*);
	static void		_BCL	Spin1Callback		(CBoneInstance*);
	static void		_BCL	ShoulderCallback	(CBoneInstance*);
	static void		_BCL	HeadCallback		(CBoneInstance*);
	static void		_BCL	VehicleHeadCallback	(CBoneInstance*);

	const SRotation	Orientation			()	const override { return r_torso; };
	SRotation				&Orientation		()			 { return r_torso; };

	void					g_SetAnimation		(u32 mstate_rl);
	void					g_SetSprintAnimation(u32 mstate_rl,MotionID &head,MotionID &torso,MotionID &legs);
public:
	void			OnHUDDraw			(CCustomHUD* hud) override;
			BOOL			HUDview				( )const ;

	//visiblity 
	float			ffGetFov			()	const override { return 90.f;		}
	float			ffGetRange			()	const override { return 500.f;		}

	
public:
	CActorCameraManager&	Cameras				() 	{VERIFY(m_pActorEffector); return *m_pActorEffector;}
	IC CCameraBase*			cam_Active			()	{return cameras[cam_active];}
	IC CCameraBase*			cam_FirstEye		()	{return cameras[eacFirstEye];}

	IC EActorCameras		active_cam			()  { return cam_active; } // KD: need to know which cam active outside actor methods

	virtual	void			cam_Set					(EActorCameras style);

protected:
	void					cam_Update				(float dt, float fFOV);
	void					cam_Lookout				( const Fmatrix &xform, float camera_height );
	void					camUpdateLadder			(float dt);
	void					cam_SetLadder			();
	void					cam_UnsetLadder			();
	float					currentFOV				();

	// Cameras
	CCameraBase*			cameras[eacMaxCam];
	EActorCameras			cam_active;
	float					fPrevCamPos;
	float					current_ik_cam_shift;
	Fvector					vPrevCamDir;
	float					fCurAVelocity;
	CEffectorBobbing*		pCamBobbing;


	//менеджер эффекторов, есть у каждого актрера
	CActorCameraManager*	m_pActorEffector;
	static float			f_Ladder_cam_limit;
public:
	float					fFPCamYawMagnitude;			//--#SM+#--
	float					fFPCamPitchMagnitude;		//--#SM+#--

public:
	void			feel_touch_new				(CObject* O) override;
	void			feel_touch_delete			(CObject* O) override;
	BOOL			feel_touch_contact			(CObject* O) override;
	BOOL			feel_touch_on_contact		(CObject* O) override;

	CGameObject*			ObjectWeLookingAt			() {return m_pObjectWeLookingAt;}
	CInventoryOwner*		PersonWeLookingAt			() {return m_pPersonWeLookingAt;}
	LPCSTR					GetDefaultActionForObject	() {return *m_sDefaultObjAction;}
protected:
	CUsableScriptObject*	m_pUsableObject;
	// Person we're looking at
	CInventoryOwner*		m_pPersonWeLookingAt;
	CHolderCustom*			m_pVehicleWeLookingAt;
	CGameObject*			m_pObjectWeLookingAt;
	CInventoryBox*			m_pInvBoxWeLookingAt;

	// Tip for action for object we're looking at
	shared_str				m_sDefaultObjAction;
	shared_str				m_sCharacterUseAction;
	shared_str				m_sDeadCharacterUseAction;
	shared_str				m_sDeadCharacterUseOrDragAction;
	shared_str				m_sDeadCharacterDontUseAction;
	shared_str				m_sCarCharacterUseAction;
	shared_str				m_sInventoryItemUseAction;
	shared_str				m_sInventoryBoxUseAction;

	//режим подбирания предметов
	bool					m_bPickupMode;
	//расстояние (в метрах) на котором актер чувствует гранату (любую)
	float					m_fFeelGrenadeRadius;
	float					m_fFeelGrenadeTime; 	//время гранаты (сек) после которого актер чувствует гранату
	//расстояние подсветки предметов
	float					m_fPickupInfoRadius;

	void					PickupModeUpdate	();
	void					PickupInfoDraw		(CObject* object);
	void					PickupModeUpdate_COD ();

	//////////////////////////////////////////////////////////////////////////
	// Motions (передвижения актрера)
	//////////////////////////////////////////////////////////////////////////
public:
	void					g_cl_CheckControls		(u32 mstate_wf, Fvector &vControlAccel, float &Jump, float dt);
	void					g_cl_ValidateMState		(float dt, u32 mstate_wf);
	void					g_cl_Orientate			(u32 mstate_rl, float dt);
	void					g_sv_Orientate			(u32 mstate_rl, float dt);
	void					g_Orientate				(u32 mstate_rl, float dt);
	bool					g_LadderOrient			() ;
//	void					UpdateMotionIcon		(u32 mstate_rl);

	bool					CanAccelerate			();
	bool					CanJump					();
	bool					CanMove					();
	float					CameraHeight			();
	float					CurrentHeight; 	// Alex ADD: for smooth crouch fix
	bool					CanSprint				();
	bool					CanRun					();
	void					StopAnyMove				();
	void					StopSprint				() {mstate_wishful &= ~mcSprint;}

	bool					AnyAction				()	{return (mstate_real & mcAnyAction) != 0;};
	bool					AnyMove					()	{return (mstate_real & mcAnyMove) != 0;};

	bool					is_jump					();
	u32						MovingState				() const {return mstate_real;}

	float					m_dropsIntensity{};
	float					m_dropsAnimIncrementor{};

	u32						mstate_wishful;
	u32						mstate_old;
	u32						mstate_real;

	BOOL					m_bJumpKeyPressed;

	float					m_fWalkAccel;
	float					m_fJumpSpeed;
	float					m_fRunFactor;
	float					m_fRunBackFactor;
	float					m_fWalkBackFactor;
	float					m_fCrouchFactor;
	float					m_fClimbFactor;
	float					m_fSprintFactor;

	float					m_fWalk_StrafeFactor;
	float					m_fRun_StrafeFactor;

	u32						m_iBaseArtefactCount;

	// For activating sprint when reloading
	u8						m_iTrySprintCounter;

public:
	Fvector					GetMovementSpeed		() {return NET_SavedAccel;};
	//////////////////////////////////////////////////////////////////////////
	// User input/output
	//////////////////////////////////////////////////////////////////////////
public:
	void			IR_OnMouseMove			(int x, int y) override;
	void			IR_OnKeyboardPress		(int dik) override;
	void			IR_OnKeyboardRelease	(int dik) override;
	void			IR_OnKeyboardHold		(int dik) override;
	void			IR_OnMouseWheel			(int direction) override;
	virtual	float			GetLookFactor			();

public:
	void						g_WeaponBones		(int &L, int &R1, int &R2) override;
	void						g_fireParams		(CHudItem* pHudItem, Fvector& P, Fvector& D) override;
	bool						g_stateFire			() override {return ! ((mstate_wishful & mcLookout) && !IsGameTypeSingle() );}

	BOOL						g_State				(SEntityState& state) const override;
	float						GetWeaponAccuracy	() const override;
			float						GetFireDispertion	() const {return m_fdisp_controller.GetCurrentDispertion();}
			bool						IsZoomAimingMode	() const {return m_bZoomAimingMode;}
	float						MaxCarryWeight		() const override;
			float						MaxWalkWeight		() const;
			float						get_additional_weight() const;
			u32							GetBaseArtefactCount() const { return m_iBaseArtefactCount; }

protected:
	CFireDispertionController			m_fdisp_controller;
	//если актер целится в прицел
	void								SetZoomAimingMode	(bool val)	{m_bZoomAimingMode = val;}
	bool								m_bZoomAimingMode;

	//настройки аккуратности стрельбы
	//базовая дисперсия (когда игрок стоит на месте)
	float								m_fDispBase;
	float								m_fDispAim;
	//коэффициенты на сколько процентов увеличится базовая дисперсия
	//учитывает скорость актера 
	float								m_fDispVelFactor;
	//если актер бежит
	float								m_fDispAccelFactor;
	//если актер сидит
	float								m_fDispCrouchFactor;
	//crouch+no acceleration
	float								m_fDispCrouchNoAccelFactor;

protected:
	//косточки используемые при стрельбе
	int									m_r_hand;
	int									m_l_finger1;
    int									m_r_finger2;
	int									m_head;
	int									m_eye_left;
	int									m_eye_right;

	int									m_l_clavicle;
	int									m_r_clavicle;
	int									m_spine2;
	int									m_spine1;
	int									m_spine;
	int									m_neck;



	//////////////////////////////////////////////////////////////////////////
	// Network
	//////////////////////////////////////////////////////////////////////////
			void						ConvState			(u32 mstate_rl, string128 *buf);
public:
	BOOL						net_Spawn			( CSE_Abstract* DC) override;
	void						net_Export			( NET_Packet& P) override;				// export to server
	void						net_Import			( NET_Packet& P) override;				// import from server
	void						net_Destroy			() override;
	BOOL						net_Relevant		() override;//	{ return getSVU() | getLocal(); };		// relevant for export to server
	void						net_Relcase			( CObject* O ) override;					//
	virtual void xr_stdcall				on_requested_spawn  (CObject *object);
	//object serialization
	void						save				(NET_Packet &output_packet) override;
	void						load				(IReader &input_packet) override;
	void						net_Save			(NET_Packet& P) override;
	BOOL						net_SaveRelevant	() override;
protected:
	xr_deque<net_update>	NET;
	Fvector					NET_SavedAccel;
	net_update				NET_Last;
	BOOL					NET_WasInterpolating;	// previous update was by interpolation or by extrapolation
	u32						NET_Time;				// server time of last update

	//---------------------------------------------
	void					net_Import_Base				( NET_Packet& P);
	void					net_Import_Physic			( NET_Packet& P);
	void					net_Import_Base_proceed		( );
	void					net_Import_Physic_proceed	( );
	//---------------------------------------------
	


////////////////////////////////////////////////////////////////////////////
	bool				can_validate_position_on_spawn	() override {return false;}
	///////////////////////////////////////////////////////
	// апдайт с данными физики
	xr_deque<net_update_A>	NET_A;
	
	//---------------------------------------------
//	bool					m_bHasUpdate;	
	/// spline coeff /////////////////////
	float			SCoeff[3][4];			//коэффициэнты для сплайна Бизье
	float			HCoeff[3][4];			//коэффициэнты для сплайна Эрмита
	Fvector			IPosS, IPosH, IPosL;	//положение актера после интерполяции Бизье, Эрмита, линейной

#ifdef DEBUG
	DEF_DEQUE		(VIS_POSITION, Fvector);

	VIS_POSITION	LastPosS;
	VIS_POSITION	LastPosH;
	VIS_POSITION	LastPosL;
#endif

	
	SPHNetState				LastState;
	SPHNetState				RecalculatedState;
	SPHNetState				PredictedState;
	
	InterpData				IStart;
	InterpData				IRec;
	InterpData				IEnd;
	
	bool					m_bInInterpolation;
	bool					m_bInterpolate;
	u32						m_dwIStartTime;
	u32						m_dwIEndTime;
	u32						m_dwILastUpdateTime;

	//---------------------------------------------
	DEF_DEQUE		(PH_STATES, SPHNetState);
	PH_STATES				m_States;
	u16						m_u16NumBones;
	void					net_ExportDeadBody		(NET_Packet &P);
	//---------------------------------------------
	void					CalculateInterpolationParams();
	//---------------------------------------------
	void			make_Interpolation () override;
#ifdef DEBUG
	//---------------------------------------------
	virtual void			OnRender_Network();
	//---------------------------------------------
#endif

// Igor	ref_geom 				hFriendlyIndicator;
	//////////////////////////////////////////////////////////////////////////
	// Actor physics
	//////////////////////////////////////////////////////////////////////////
public:
			void			g_Physics		(Fvector& accel, float jump, float dt);
	void			ForceTransform	(const Fmatrix &m) override;
			void			SetPhPosition	(const Fmatrix& pos);
	void			PH_B_CrPr		() override; // actions & operations before physic correction-prediction steps
	void			PH_I_CrPr		() override; // actions & operations after correction before prediction steps
	void			PH_A_CrPr		() override; // actions & operations after phisic correction-prediction steps
//	virtual void			UpdatePosStack	( u32 Time0, u32 Time1 );
	virtual void			MoveActor		(Fvector NewPos, Fvector NewDir);

	virtual void			SpawnAmmoForWeapon		(CInventoryItem *pIItem);
	virtual void			RemoveAmmoForWeapon		(CInventoryItem *pIItem);
	void			spawn_supplies			() override;

	bool			human_being				() const override
	{
		return				(true);
	}

	virtual	shared_str		GetDefaultVisualOutfit	() const {return m_DefaultVisualOutfit;};
	virtual	void			SetDefaultVisualOutfit	(shared_str DefaultOutfit) {m_DefaultVisualOutfit = DefaultOutfit;};

	virtual void			UpdateAnimation			() 	{ g_SetAnimation(mstate_real); };

	virtual void			ChangeVisual			( shared_str NewVisual );
	void			OnChangeVisual			() override;

	virtual void			RenderIndicator			(Fvector dpos, float r1, float r2, const ui_shader &IndShader);
	virtual void			RenderText				(LPCSTR Text, Fvector dpos, float* pdup, u32 color);

	//////////////////////////////////////////////////////////////////////////
	// Controlled Routines
	//////////////////////////////////////////////////////////////////////////

			void			set_input_external_handler			(CActorInputHandler *handler);
			bool			input_external_handler_installed	() const {return (m_input_external_handler != 0);}
			
	IC		void			lock_accel_for						(u32 time){m_time_lock_accel = Device.dwTimeGlobal + time;}

private:	
	CActorInputHandler		*m_input_external_handler;
	u32						m_time_lock_accel;

	/////////////////////////////////////////
	// DEBUG INFO
protected:
		CStatGraph				*pStatGraph;

		shared_str				m_DefaultVisualOutfit;

		LPCSTR					invincibility_fire_shield_3rd;
		LPCSTR					invincibility_fire_shield_1st;
		shared_str				m_sHeadShotParticle;
		u32						last_hit_frame;
#ifdef DEBUG
		friend class CLevelGraph;
#endif
		Fvector							m_AutoPickUp_AABB;
		Fvector							m_AutoPickUp_AABB_Offset;

		void							Check_for_AutoPickUp			();
		void							SelectBestWeapon				(CObject* O);
public:
		void							SetWeaponHideState				(u16 State, bool bSet);
private://IPhysicsShellHolder

	void	_BCL	HideAllWeapons					( bool v ) override { SetWeaponHideState(INV_STATE_BLOCK_ALL,v); }	

public:
		void							SetCantRunState					(bool bSet);
private:
	CActorCondition				*m_entity_condition;

protected:
	CEntityConditionSimple	*create_entity_condition	(CEntityConditionSimple* ec) override;

public:
	IC		CActorCondition		&conditions					() const;
	DLL_Pure			*_construct					() override;
	bool				natural_weapon				() const override {return false;}
	bool				natural_detector			() const override {return false;}
	bool				use_center_to_aim			() const override;

protected:
	u16							m_iLastHitterID;
	u16							m_iLastHittingWeaponID;
	s16							m_s16LastHittedElement;
	Fvector						m_vLastHitDir;
	Fvector						m_vLastHitPos;
	float						m_fLastHealth;
	bool						m_bWasHitted;
	bool						m_bWasBackStabbed;

	virtual		bool			Check_for_BackStab_Bone			(u16 element);
public:
	void				SetHitInfo						(CObject* who, CObject* weapon, s16 element, Fvector Pos, Fvector Dir) override;

	void				OnHitHealthLoss					(float NewHealth) override;
	void				OnCriticalHitHealthLoss			() override;
	void				OnCriticalWoundHealthLoss		() override;
	void				OnCriticalRadiationHealthLoss	() override;

	virtual	bool				InventoryAllowSprint			();
	virtual void				OnNextWeaponSlot				();
	virtual void				OnPrevWeaponSlot				();

			void				NVGAnimCheckDetector			();
			void				CleanMaskAnimCheckDetector		();
			void				StartNVGAnimation				();
			void				SwitchNightVision				();
			void				SwitchTorch						();
			void				CleanMask						();
			void				QuickKick						();
			bool				IsReloadingWeapon				();
#ifdef DEBUG
			void				NoClipFly						(int cmd);
#endif //DEBUG

public:
	void				on_weapon_shot_start			(CWeapon *weapon) override;
	void				on_weapon_shot_update			() override;
	void				on_weapon_shot_stop				() override;
	void				on_weapon_shot_remove			(CWeapon *weapon) override;
	void				on_weapon_hide					(CWeapon *weapon) override;
			Fvector				weapon_recoil_delta_angle		();
			Fvector				weapon_recoil_last_delta		();
protected:
	virtual	void				update_camera					(CCameraShotEffector* effector);
	//step manager
	bool				is_on_ground					() override;

private:
	CActorMemory				*m_memory;

public:
	IC		CActorMemory		&memory							() const {VERIFY(m_memory); return(*m_memory); };

	void						OnDifficultyChanged				();

	IC float					HitProbability					() {return m_hit_probability;}
	CVisualMemoryManager*visual_memory					() const override;

	BOOL				BonePassBullet					(int boneID) override;
	void				On_B_NotCurrentEntity			() override;

private:
	collide::rq_results			RQR;
			BOOL				CanPickItem						(const CFrustum& frustum, const Fvector& from, CObject* item);
	xr_vector<ISpatial*>		ISpatialResult;

private:
	CLocationManager				*m_location_manager;

public:
	IC		const CLocationManager	&locations					() const
	{
		VERIFY						(m_location_manager);
		return						(*m_location_manager);
	}

private:
	ALife::_OBJECT_ID	m_holder_id;

	xr_map<EGameActions, bool> m_blocked_actions;
public:
	bool				register_schedule				() const override {return false;}
	bool				is_ai_obstacle					() const override;
	
			float				GetRestoreSpeed					(ALife::EConditionRestoreType const& type);

			IC u32 get_state() const
			{
				return this->mstate_real;
			}

			IC u32 get_state_wishful() const
			{
				return this->mstate_wishful;
			}

			IC void set_state_wishful(u32 state)
			{
				mstate_wishful = state;
			}

public:
	void			On_SetEntity() override;
	void			On_LostEntity() override {};

			void			DisableHitMarks(bool disable)		{m_disabled_hitmarks = disable;};
			bool			DisableHitMarks()					{return m_disabled_hitmarks;};

			void			set_inventory_disabled (bool is_disabled) { m_inventory_disabled = is_disabled; }
			bool			inventory_disabled () const { return m_inventory_disabled; }
private:
			void			set_state_box(u32	mstate);
private:
	bool					m_disabled_hitmarks;
	bool					m_inventory_disabled;
//static CPhysicsShell		*actor_camera_shell;

public:
	void					SwitchNightVision(bool light_on, bool use_sounds = true, bool send_event = true);

	bool					GetNightVisionStatus() {return m_bNightVisionOn;}
	void					SetNightVisionAllowed(bool bAllow) {m_bNightVisionAllow = bAllow;}
	CNightVisionEffector*	GetNightVision() {return m_night_vision;}

	// Real Wolf. Start. 14.10.2014
	void					block_action(EGameActions cmd);
	void					unblock_action(EGameActions cmd);
	// Real Wolf. End. 14.10.2014

	bool					MaskClearInProcess() { return m_bMaskClear; }

	float					GetDevicesPsyFactor() { return m_fDevicesPsyFactor; }
	void					SetDevicesPsyFactor(float psy_factor) { m_fDevicesPsyFactor = psy_factor; }

	bool					m_bEatAnimActive;
	bool					m_bActionAnimInProcess;
	CActorSkills*			ActorSkills;
	CTimerManager*			TimerManager;

	bool					HasItemsForRepair(xr_vector<std::pair<shared_str, int>> item);
	void					RemoveItemsForRepair(xr_vector<std::pair<shared_str, int>> item);

	float					GetInventoryCapacity() const { return m_fInventoryCapacity; }
	float					GetInventoryFullness() const { return m_fInventoryFullness; }
	float					MaxCarryInvCapacity	() const;
	void					ChangeInventoryFullness(float val);
	u16						GetLastActiveSlot	() { return m_last_active_slot; }
protected:
	bool					m_bNightVisionOn;
	bool					m_bNightVisionAllow;
	bool					m_bNVGActivated;
	bool					m_bNVGSwitched;
	bool					m_bMaskAnimActivated;
	bool					m_bMaskClear;
	bool					m_bQuickKickActivated;
	bool					m_bQuickKick;
	int						m_iNVGAnimLength;
	int						m_iActionTiming;
	int						m_iMaskAnimLength;
	int						m_iQuickKickAnimLength;
	float					m_fInventoryCapacity;
	float					m_fInventoryFullness;
	float					m_fInventoryFullnessCtrl; // Для контроля эвента. Иначе эвент отправляется пачкой и дропает больше, чем нужно.

	u16						m_last_active_slot;

	float					m_fDevicesPsyFactor;

	ref_sound				m_action_anim_sound;

	CNightVisionEffector*	m_night_vision;

DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CActor)
#undef script_type_list
#define script_type_list save_type_list(CActor)

extern bool		isActorAccelerated			(u32 mstate, bool ZoomMode);

IC	CActorCondition	&CActor::conditions	() const{ VERIFY(m_entity_condition); return(*m_entity_condition);}

extern Fvector		g_start_position;
extern int			g_start_game_vertex_id;
extern CActor*		g_actor;
CActor*				Actor		();
extern const float	s_fFallTime;
