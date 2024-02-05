#ifndef PHYSICSSHELL_HOLDER_H
#define PHYSICSSHELL_HOLDER_H

#include "GameObject.h"
#include "ParticlesPlayer.h"
#include "../xrEngine/iobjectphysicscollision.h"
#include "../xrphysics/iphysicsshellholder.h"

class CPHDestroyable;
class CPHCollisionDamageReceiver;
class CPHSoundPlayer;
class IDamageSource;
class CPHSkeleton;
class CCharacterPhysicsSupport;
class ICollisionDamageInfo;
class CIKLimbsController;



class CPhysicsShellHolder:  public CGameObject,
							public CParticlesPlayer,
							public IObjectPhysicsCollision,
							public IPhysicsShellHolder
	
{
	bool				b_sheduled;
public:
	void	SheduleRegister		(){if(!IsSheduled())shedule_register();b_sheduled=true;}
	void	SheduleUnregister	(){if(IsSheduled())shedule_unregister();b_sheduled=false;}
IC	bool	IsSheduled			(){return b_sheduled;}	
public:

	typedef CGameObject inherited;
	

	CPhysicsShell			*m_pPhysicsShell;


			CPhysicsShellHolder							();
	~CPhysicsShellHolder						() override;

	virtual bool		ActivationSpeedOverriden (Fvector& dest, bool clear_override) { return false; }

	IC CPhysicsShell	*&PPhysicsShell				()		
	{
		return m_pPhysicsShell;
	}

	IC CPhysicsShellHolder*	PhysicsShellHolder	()
	{
		return this;
	}

	const IObjectPhysicsCollision*physics_collision			() override;
	const IPhysicsShell			*physics_shell				()const override;
	IPhysicsShell			*physics_shell				() override;
	const IPhysicsElement		*physics_character			()const override;
	virtual CPHDestroyable				*ph_destroyable				()							{return NULL;}
	virtual ICollisionDamageReceiver	*PHCollisionDamageReceiver	()							{return NULL;}
	virtual CPHSkeleton					*PHSkeleton					()							{return NULL;}
	CPhysicsShellHolder			*cast_physics_shell_holder	() override {return this;}
	CParticlesPlayer			*cast_particles_player		() override {return this;}
	virtual IDamageSource				*cast_IDamageSource			()							{return NULL;}
	virtual CPHSoundPlayer				*ph_sound_player			()  						{return NULL;}
	virtual	CCharacterPhysicsSupport	*character_physics_support	()							{return NULL;}
	virtual	const CCharacterPhysicsSupport	*character_physics_support	() const					{return NULL;}
	virtual	CIKLimbsController			*character_ik_controller	()							{return NULL;}
	virtual ICollisionHitCallback		*get_collision_hit_callback ()							{return NULL;}
	virtual void						set_collision_hit_callback	(ICollisionHitCallback *cc)	{;}
	void			_BCL			enable_notificate			() override {;}
public:

	virtual void			PHGetLinearVell		(Fvector& velocity);
	virtual void			PHSetLinearVell		(Fvector& velocity);
	virtual void			PHSetMaterial		(LPCSTR m);
	virtual void			PHSetMaterial		(u16 m);
			void			PHSaveState			(NET_Packet &P);
			void			PHLoadState			(IReader &P);
	virtual f32				GetMass				();
	virtual	void			PHHit				(SHit &H);
	void			Hit					(SHit* pHDS) override;
///////////////////////////////////////////////////////////////////////
	virtual u16				PHGetSyncItemsNumber();
	virtual CPHSynchronize*	PHGetSyncItem		(u16 item);
	virtual void			PHUnFreeze			();
	virtual void			PHFreeze			();
	virtual float			EffectiveGravity	();
///////////////////////////////////////////////////////////////
	virtual void			create_physic_shell		();
	virtual void			activate_physic_shell	();
	virtual void			setup_physic_shell		();
	virtual void			deactivate_physics_shell ();

	void			net_Destroy			() override;
	BOOL			net_Spawn			(CSE_Abstract*	DC) override;
	void			save				(NET_Packet &output_packet) override;
	void			load				(IReader &input_packet) override;
			void			init				();

	void			OnChangeVisual		() override;
	//для наследования CParticlesPlayer
	void			UpdateCL			() override;
			void			correct_spawn_pos	();
protected:
	virtual	bool			has_shell_collision_place( const CPhysicsShellHolder* obj ) const;
	virtual void			on_child_shell_activate	 ( CPhysicsShellHolder* obj );
public:
	bool			register_schedule	() const override;

public:
	void					_BCL					on_physics_disable					() override;
private://IPhysicsShellHolder
	Fmatrix&				_BCL					ObjectXFORM							() override;
	Fvector&				_BCL					ObjectPosition						() override;
	LPCSTR					_BCL					ObjectName							()		const override;
	LPCSTR					_BCL					ObjectNameVisual					()		const override;
	LPCSTR					_BCL					ObjectNameSect						()		const override;
	bool					_BCL					ObjectGetDestroy					()		const override;
	ICollisionHitCallback*	_BCL 					ObjectGetCollisionHitCallback		() override;
	u16						_BCL					ObjectID							()		const override;
	ICollisionForm*			_BCL					ObjectCollisionModel				() override;
	//virtual	IRenderVisual*			_BCL					ObjectVisual						()						;
	IKinematics*			_BCL					ObjectKinematics					() override;
	IDamageSource*			_BCL					ObjectCastIDamageSource				() override;
	void					_BCL					ObjectProcessingDeactivate			() override;
	void					_BCL					ObjectProcessingActivate			() override;
	void					_BCL					ObjectSpatialMove					() override;
	CPhysicsShell*&			_BCL					ObjectPPhysicsShell					() override;
//	virtual	void						enable_notificate					()						;
	bool					_BCL					has_parent_object					() override;
//	virtual	void						on_physics_disable					()						;
	IPHCapture*				_BCL					PHCapture							() override;
	bool					_BCL					IsInventoryItem						() override;
	bool					_BCL					IsActor								() override;
	bool					_BCL					IsStalker							() override;
	//virtual	void						SetWeaponHideState					( u16 State, bool bSet )=0;
	void					_BCL					HideAllWeapons						( bool v ) override;//(SetWeaponHideState(INV_STATE_BLOCK_ALL,true))
	void					_BCL					MovementCollisionEnable				( bool enable ) override;
	CPHSoundPlayer*			_BCL					ObjectPhSoundPlayer					() override {return ph_sound_player();}
	ICollisionDamageReceiver* _BCL				ObjectPhCollisionDamageReceiver		() override;
	void					_BCL					BonceDamagerCallback				(float &damage_factor) override;
#ifdef	DEBUG
	std::string				_BCL					dump								(EDumpType type) const override;
#endif
};

#endif