#pragma once

#include "../xrphysics/physicsshell.h"

struct	CPHCaptureBoneCallback :
	public NearestToPointCallback
{
	virtual	bool operator() ( u16 bid )		= 0;

	bool operator() ( CPhysicsElement* e ) override
	{
		return (*this) ( e->m_SelfID );
	};
};