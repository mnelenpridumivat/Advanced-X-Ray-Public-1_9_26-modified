#pragma once

#include "../xrGame/Metaclass.h"

class	ENGINE_API	ICollisionForm;

class	ENGINE_API	ICollidable : public IMetaClass {
	DECLARE_METACLASS(ICollidable)
public:
	struct 
	{
		ICollisionForm*			model;
	}							collidable;
public:
	ICollidable();
	virtual ~ICollidable();
};
