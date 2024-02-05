#ifndef PHYSICS_SKELETON_OBJECT_H
#define PHYSICS_SKELETON_OBJECT_H
#include "physicsshellholder.h"
#include "PHSkeleton.h"


class CSE_ALifePHSkeletonObject;
class CPhysicsSkeletonObject : 
	public CPhysicsShellHolder,
	public CPHSkeleton

{
typedef CPhysicsShellHolder inherited;

public:
	CPhysicsSkeletonObject(void);
~CPhysicsSkeletonObject(void) override;


BOOL					net_Spawn			( CSE_Abstract* DC) override;
void					net_Destroy			() override;
void					Load				(LPCSTR section) override;
void					UpdateCL			( ) override;// Called each frame, so no need for dt
void					shedule_Update		(u32 dt) override;	//
void					net_Save			(NET_Packet& P) override;
BOOL					net_SaveRelevant	() override;
BOOL					UsedAI_Locations	() override;
protected:
CPhysicsShellHolder		*PPhysicsShellHolder() override {return PhysicsShellHolder();}
CPHSkeleton				*PHSkeleton			() override {return this;}
void					SpawnInitPhysics	(CSE_Abstract	*D) override;
	virtual void					PHObjectPositionUpdate()																			;
	virtual	void					CreatePhysicsShell	(CSE_Abstract	*e)																;
};



#endif