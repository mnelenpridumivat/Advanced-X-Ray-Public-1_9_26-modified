////////////////////////////////////////////////////////////////////////////
//	Module 		: ai_crow.h
//	Description : AI Behaviour for monster "Crow"
////////////////////////////////////////////////////////////////////////////

#ifndef __XRAY_AI_CROW__
#define __XRAY_AI_CROW__

#include "../../entity_alive.h"
#include "../../../Include/xrRender/KinematicsAnimated.h"

class CMotionDef;
class CBlend;
class IKinematicsAnimated;

class CAI_Crow : public CEntity
{
	typedef	CEntity inherited;
	enum ECrowStates 	{
		eUndef		= -1,
		eDeathFall	= 0,
		eDeathDead,
		eFlyIdle,
		eFlyUp
	};

	// constants and types
	enum			{ MAX_ANIM_COUNT = 8	};
	enum			{ MAX_SND_COUNT = 8		};

	// animations
	struct SAnim
	{
		typedef			svector<MotionID,MAX_ANIM_COUNT> MotionSVec;
		MotionSVec		m_Animations;
		const MotionID	&GetRandom	(){return m_Animations[Random.randI(0,m_Animations.size())];}
		void			Load		(IKinematicsAnimated* visual, LPCSTR prefix);
	};

	struct SSound
	{
		typedef			svector<ref_sound,MAX_SND_COUNT>		SoundSVec;
		SoundSVec		m_Sounds;
		ref_sound&		GetRandom		()	{return m_Sounds[Random.randI(0,m_Sounds.size())];}
		void			Load			(LPCSTR prefix);
		void			SetPosition		(const Fvector& pos);
		void			Unload			();
	};
public:
	void				OnHitEndPlaying	(CBlend* B);
protected:
	
	struct SCrowAnimations
	{
		SAnim		m_idle;
		SAnim		m_fly;
		SAnim		m_death;
		SAnim		m_death_idle;
		SAnim		m_death_dead;
	};
	SCrowAnimations	m_Anims;
	struct SCrowSounds
	{
		SSound		m_idle;
	};
	SCrowSounds		m_Sounds;

	Fvector			vOldPosition;
	ECrowStates		st_current, st_target;
	// parameters block
	Fvector			vGoalDir;
	Fvector			vCurrentDir;
	Fvector			vHPB;
	float			fDHeading;

	// constants
	float			fGoalChangeDelta;
	float			fSpeed;
	float			fASpeed;
	float			fMinHeight;
	Fvector			vVarGoal;
	float			fIdleSoundDelta;

	// variables
	float			fGoalChangeTime;
	float			fIdleSoundTime;

	// 
	bool			bPlayDeathIdle;

	void			switch2_FlyUp				();
	void			switch2_FlyIdle				();
	void			switch2_DeathFall			();
	void			switch2_DeathDead			();

	void			state_DeathFall				();
	void			state_Flying				(float dt);

	void			CreateSkeleton				();
	
	void			UpdateWorkload				(float DT);

public:						
	u32				o_workload_frame	;
	u32				o_workload_rframe	;
public:
					CAI_Crow();
	~CAI_Crow() override;
	void	Load						( LPCSTR section ) override;
			void	init						();
	BOOL	net_Spawn					( CSE_Abstract* DC ) override;
	void	net_Destroy					() override;
	BOOL	renderable_ShadowGenerate	() override { return FALSE;	}
	BOOL	renderable_ShadowReceive	() override { return FALSE;	}
	void	renderable_Render			() override;
	void	shedule_Update				(u32 DT) override;
	void	UpdateCL					() override;

	CEntity*cast_entity					() override {return this;}

	void	net_Export					(NET_Packet& P) override;
	void	net_Import					(NET_Packet& P) override;

	void	g_fireParams				(CHudItem* /**pHudItem/**/, Fvector& /**P/**/, Fvector& /**D/**/) override {};
	virtual void	g_WeaponBones				(int &/**L/**/, int &/**R1/**/, int &/**R2/**/)	{};

	void	HitSignal					(float	HitAmount,	Fvector& local_dir, CObject* who, s16 element) override;
	void	HitImpulse					(float	amount,		Fvector& vWorldDir, Fvector& vLocalDir) override;
	void	Hit							(SHit* pHDS) override;
	void	Die							(CObject* who) override;
	virtual	float	ffGetFov					() const {return 150.f;	}
	virtual	float	ffGetRange					() const {return 30.f;	}

	BOOL	IsVisibleForHUD	() override { return FALSE;		}
	bool	IsVisibleForZones() override { return false;		}
	BOOL	UsedAI_Locations() override;
	void	create_physic_shell	() override;

public:
	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CAI_Crow)
#undef script_type_list
#define script_type_list save_type_list(CAI_Crow)

#endif