#pragma once

#include "hud_item_object.h"
#include "hit_immunity.h"
#include "../xrphysics/PHUpdateObject.h"
#include "script_export_space.h"
#include "patrol_path.h"

class SArtefactActivation;
class CInventoryItem;
struct SArtefactDetectorsSupport;

class CArtefact :	public CHudItemObject, 
					public CPHUpdateObject 
{
	typedef			CHudItemObject	inherited;
public:
									CArtefact						();
	~CArtefact						() override;

	void					Load							(LPCSTR section) override;
	BOOL					net_Spawn						(CSE_Abstract* DC) override;
	void					net_Destroy						() override;

	void					OnH_A_Chield					() override;
	void					OnH_B_Independent				(bool just_before_destroy) override;
	void					save							(NET_Packet &output_packet) override;
	void					load							(NET_Packet&input_packet) override;
	void					OnActiveItem					() override;
	void					OnHiddenItem					() override;

	void					UpdateCL						() override;
	void					shedule_Update					(u32 dt) override;	
			void					UpdateWorkload					(u32 dt);


	bool					CanTake							() const override;

	BOOL					renderable_ShadowGenerate		() override { return FALSE;	}
	BOOL					renderable_ShadowReceive		() override { return TRUE;	}
	void					create_physic_shell				() override;

	CArtefact*				cast_artefact					() override {return this;}
	u32						Cost							() const override;

	virtual bool				CheckInventoryIconItemSimilarity(CInventoryItem* other) override;

	virtual float					GetHealthPower() const { return m_fHealthRestoreSpeed; }
	virtual float					GetRadiationPower() const { return m_fRadiationRestoreSpeed; }
	virtual float					GetSatietyPower() const { return m_fSatietyRestoreSpeed; }
	virtual float					GetPowerPower() const { return m_fPowerRestoreSpeed; }
	virtual float					GetBleedingPower() const { return m_fBleedingRestoreSpeed; }
	virtual float					GetThirstPower() const { return m_fThirstRestoreSpeed; }
	virtual float					GetIntoxicationPower() const { return m_fIntoxicationRestoreSpeed; }
	virtual float					GetSleepenessPower() const { return m_fSleepenessRestoreSpeed; }
	virtual float					GetAlcoholismPower() const { return m_fAlcoholismRestoreSpeed; }
	virtual float					GetNarcotismPower() const { return m_fNarcotismRestoreSpeed; }
	virtual float					GetPsyHealthPower() const { return m_fPsyHealthRestoreSpeed; }
	virtual float					GetJumpPower() const { return m_fJumpSpeed; }
	virtual float					GetWalkPower() const { return m_fWalkAccel; }

	virtual void					SetHealthPower(float value) { m_fHealthRestoreSpeed = value; }
	virtual void					SetRadiationPower(float value) { m_fRadiationRestoreSpeed = value; }
	virtual void					SetSatietyPower(float value) { m_fSatietyRestoreSpeed = value; }
	virtual void					SetPowerPower(float value) { m_fPowerRestoreSpeed = value; }
	virtual void					SetBleedingPower(float value) { m_fBleedingRestoreSpeed = value; }
	virtual void					SetThirstPower(float value) { m_fThirstRestoreSpeed = value; }
	virtual void					SetIntoxicationPower(float value) { m_fIntoxicationRestoreSpeed = value; }
	virtual void					SetSleepenessPower(float value) { m_fSleepenessRestoreSpeed = value; }
	virtual void					SetAlcoholismPower(float value) { m_fAlcoholismRestoreSpeed = value; }
	virtual void					SetNarcotismPower(float value) { m_fNarcotismRestoreSpeed = value; }
	virtual void					SetPsyHealthPower(float value) { m_fPsyHealthRestoreSpeed = value; }
	virtual void					SetJumpPower(float value) { m_fJumpSpeed = value; }
	virtual void					SetWalkPower(float value) { m_fWalkAccel = value; }
	virtual float GetImmunity(ALife::EHitType hit_type) { return m_ArtefactHitImmunities.GetHitImmunity(hit_type); }
	virtual void SetImmunity(ALife::EHitType hit_type, float val) { m_ArtefactHitImmunities.SetHitImmunity(hit_type, val); }
	virtual float GetProtection(ALife::EInfluenceType hit_type) { return m_HitTypeProtection[hit_type]; }

	virtual float ArtAffectHit(float power, ALife::EHitType hit_type) { return m_ArtefactHitImmunities.AffectHit(power, hit_type); }

protected:
	virtual void					UpdateCLChild					()		{};
	virtual void					CreateArtefactActivation			();

	SArtefactActivation*			m_activationObj;
	SArtefactDetectorsSupport*		m_detectorObj;

	u16								m_CarringBoneID;
	shared_str						m_sParticlesName;

	ref_light						m_pTrailLight;
	Fcolor							m_TrailLightColor;
	float							m_fTrailLightRange;
	u8								m_af_rank;
	bool							m_bLightsEnabled;

	virtual void					UpdateLights					();
public:
	IC u8							GetAfRank						() const		{return m_af_rank;}
	IC bool							CanBeActivated					()				{return m_bCanSpawnZone;};
	void							ActivateArtefact				();
	void							FollowByPath					(LPCSTR path_name, int start_idx, Fvector magic_force);
	bool							CanBeInvisible					();
	void							SwitchVisibility				(bool);

	void							SwitchAfParticles				(bool bOn);
	virtual void					StartLights();
	virtual void					StopLights();

	void					PhDataUpdate					(float step) override;
	void					PhTune							(float step) override {};

	virtual float							AdditionalInventoryWeight		() const {return m_additional_weight;}

protected:

	float							m_additional_weight;
	bool							m_bCanSpawnZone;
	float							m_fHealthRestoreSpeed;
	float 							m_fRadiationRestoreSpeed;
	float 							m_fSatietyRestoreSpeed;
	float							m_fPowerRestoreSpeed;
	float							m_fBleedingRestoreSpeed;
	//float							m_fBleedingRestoreSpeed1;
	float 							m_fThirstRestoreSpeed;
	float 							m_fIntoxicationRestoreSpeed;
	float 							m_fSleepenessRestoreSpeed;
	float 							m_fAlcoholismRestoreSpeed;
	float 							m_fNarcotismRestoreSpeed;
	float 							m_fPsyHealthRestoreSpeed;
	float							m_fJumpSpeed;
	float							m_fWalkAccel;
	CHitImmunity 					m_ArtefactHitImmunities;
	xr_hash_map<ALife::EInfluenceType, float>		m_HitTypeProtection;

public:

	xr_hash_map<ALife::EInfluenceType, float>		m_ConstHitTypeProtection;

	//For Degradation
	float							m_fConstHealthRestoreSpeed;
	float							m_fConstRadiationRestoreSpeed;
	float							m_fConstSatietyRestoreSpeed;
	float							m_fConstPowerRestoreSpeed;
	float							m_fConstBleedingRestoreSpeed;
	float							m_fConstThirstRestoreSpeed;
	float							m_fConstIntoxicationRestoreSpeed;
	float							m_fConstSleepenessRestoreSpeed;
	float							m_fConstAlcoholismRestoreSpeed;
	float							m_fConstNarcotismRestoreSpeed;
	float 							m_fConstPsyHealthRestoreSpeed;
	float							m_fConstAdditionalWeight;
	float							m_fConstTrailLightRange;
	float							m_fConstVolumetricDistance;
	float							m_fConstVolumetricIntensity;
	float							m_fConstJumpSpeed;
	float							m_fConstWalkAccel;
	float							m_fChargeLevel;
	float							m_fCurrentChargeLevel;
	float							m_fDegradationSpeed;
	void							SetChargeLevel(float charge_level);
	float							GetCurrentChargeLevel(void) const;
	void							SetRank(int rank);
	int								GetCurrentAfRank(void) const;

	bool							m_bVolumetricLights;
	float							m_fVolumetricQuality;
	float							m_fVolumetricDistance;
	float							m_fVolumetricIntensity;

	int								m_iAfRank;

	bool							m_bInContainer;
public:
	enum EAFHudStates {
		eActivating = eLastBaseState+1,
	};

	void					Interpolate			() override;

	void					PlayAnimIdle		() override;
	void					MoveTo(Fvector const & position) override;
	virtual void					StopActivation		();

	void					ForceTransform		(const Fmatrix& m) override;

	virtual void					Hide				();
	virtual void					Show				();
	void					UpdateXForm			() override;
	bool					Action				(u16 cmd, u32 flags) override;
	void					OnStateSwitch		(u32 S) override;
	void					OnAnimationEnd		(u32 state) override;
	virtual bool					IsHidden			()	const	{return GetState()==eHidden;}

			void					UpdateDegradation	(void);

	bool							IsInContainer		();

	// optimization FAST/SLOW mode
	u32						o_render_frame				;
	BOOL					o_fastmode					;
	IC void					o_switch_2_fast				()	{
		if (o_fastmode)		return	;
		o_fastmode			= TRUE	;
		//processing_activate		();
	}
	IC void					o_switch_2_slow				()	{
		if (!o_fastmode)	return	;
		o_fastmode			= FALSE	;
		//processing_deactivate		();
	}

	DECLARE_SCRIPT_REGISTER_FUNCTION
};

struct SArtefactDetectorsSupport
{
	CArtefact*						m_parent;
	ref_sound						m_sound;

	Fvector							m_path_moving_force;
	u32								m_switchVisTime;
	const CPatrolPath*				m_currPatrolPath;
	const CPatrolPath::CVertex*		m_currPatrolVertex;
	Fvector							m_destPoint;

			SArtefactDetectorsSupport		(CArtefact* A);
			~SArtefactDetectorsSupport		();
	void	SetVisible						(bool);
	void	FollowByPath					(LPCSTR path_name, int start_idx, Fvector force);
	void	UpdateOnFrame					();
	void	Blink							();
};

add_to_type_list(CArtefact)
#undef script_type_list
#define script_type_list save_type_list(CArtefact)

