// DummyObject.h: interface for the CHangingLamp class.
//
//////////////////////////////////////////////////////////////////////

#ifndef BreakableObjectH
#define BreakableObjectH

#pragma once

#include "physicsshellholder.h"
#include "../xrphysics/icollisiondamagereceiver.h"

class	IPHStaticGeomShell;
//struct	dContact;
//struct	SGameMtl;

class CBreakableObject: 
	public CPhysicsShellHolder,
	public ICollisionDamageReceiver
{
	typedef	CPhysicsShellHolder		inherited;
private:
		bool				b_resived_damage;
		float				m_max_frame_damage;
static	float				m_damage_threshold;
static	float				m_health_threshhold;
static	float				m_immunity_factor;
		Fvector				m_contact_damage_pos;
		Fvector				m_contact_damage_dir;

		float				fHealth;
		IPHStaticGeomShell	*m_pUnbrokenObject;
		CPhysicsShell		*m_Shell;
static	u32					m_remove_time;
		u32					m_break_time;
		bool				bRemoved;
//		Fbox				m_saved_box;
public:
					CBreakableObject	();
	~CBreakableObject	() override;

	void	Load				( LPCSTR section) override;
	BOOL	net_Spawn			( CSE_Abstract* DC) override;
	void	net_Destroy			() override;
	void	shedule_Update		( u32 dt) override;							// Called by sheduler
	void	UpdateCL			() override;
	BOOL	renderable_ShadowGenerate	( ) override { return FALSE;	}
	BOOL	renderable_ShadowReceive	( ) override { return TRUE;	}

	void	Hit					(SHit* pHDS) override;

	void	net_Export			(NET_Packet& P) override;
	void	net_Import			(NET_Packet& P) override;
	BOOL	UsedAI_Locations	() override;
private:
	void			Init				();
	void			CreateUnbroken		();
	void			CreateBroken		();
	void			DestroyUnbroken		();
	void			ActivateBroken		();
	void			Split				();
	void			Break				();
	void			ApplyExplosion		(const Fvector &dir,float impulse);
	void			CheckHitBreak		(float power,ALife::EHitType hit_type);
	void			ProcessDamage		();
	void			SendDestroy			();
	void	_BCL		enable_notificate	() override;
//	static 	void	ObjectContactCallback(bool& /**do_colide/**/,bool bo1,dContact& c,SGameMtl * /*material_1*/,SGameMtl * /*material_2*/);
private:
	ICollisionDamageReceiver	*PHCollisionDamageReceiver	() override {return (this);}
	void					CollisionHit				( u16 source_id, u16 bone_id, float power, const Fvector &dir, Fvector &pos ) override;
};

#endif //BreakableObjectH
