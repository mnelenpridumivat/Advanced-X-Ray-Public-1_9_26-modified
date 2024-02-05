////////////////////////////////////////////////////////////////////////////
//	Module 		: physic_item.h
//	Created 	: 11.02.2004
//  Modified 	: 11.02.2004
//	Author		: Dmitriy Iassenev
//	Description : Physic item
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "gameobject.h"
#include "PHShellCreator.h"
#include "PhysicsShellHolder.h"
class CPhysicItem : 
			public CPhysicsShellHolder,
			public CPHShellSimpleCreator
{
	typedef CPhysicsShellHolder inherited;
public:
	bool			m_ready_to_destroy;

public:
					CPhysicItem						();
	~CPhysicItem					() override;
			void	init							();
	void	reinit							() override;
	void	Load							(LPCSTR section) override;
	void	reload							(LPCSTR section) override;
	void	OnH_B_Independent				(bool just_before_destroy) override;
	void	OnH_B_Chield					() override;
	void	UpdateCL						() override;
	BOOL	net_Spawn						(CSE_Abstract* DC) override;
	void	net_Destroy						() override;
	void	activate_physic_shell			() override;
	void	setup_physic_shell				() override;
	virtual void	create_box_physic_shell			();
	virtual void	create_box2sphere_physic_shell	();
	void	create_physic_shell				() override;
};

#include "physic_item_inline.h"
