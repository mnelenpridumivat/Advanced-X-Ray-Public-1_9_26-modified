#pragma once

class CDestroyablePhysicsObject :
public	 CPhysicObject,
public	 CPHDestroyable,
public	 CPHCollisionDamageReceiver,
public	 CHitImmunity,
public	 CDamageManager
{
typedef  CPhysicObject inherited;
	float m_fHealth;
	ref_sound							m_destroy_sound;
	shared_str							m_destroy_particles;
public:
										CDestroyablePhysicsObject									()																																			;
~CDestroyablePhysicsObject									() override;
CPhysicsShellHolder*		PPhysicsShellHolder											() override;
BOOL						net_Spawn													(CSE_Abstract* DC) override;
void						net_Destroy													() override;
void						Hit															(SHit* pHDS) override;
void						InitServerObject			(CSE_Abstract*				D) override;
ICollisionDamageReceiver	*PHCollisionDamageReceiver	() override {return (this);}
DLL_Pure					*_construct					() override;
CPhysicsShellHolder*		cast_physics_shell_holder	() override {return this;}
CParticlesPlayer*			cast_particles_player		() override {return this;}
CPHDestroyable*				ph_destroyable				() override {return this;}
void						shedule_Update				(u32 dt) override;
bool						CanRemoveObject				() override;
void						OnChangeVisual				() override;
protected:
			void						Destroy						()								;
private:
};