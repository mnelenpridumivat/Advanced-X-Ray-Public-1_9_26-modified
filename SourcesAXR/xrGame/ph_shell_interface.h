#pragma once

interface IPhysicShellCreator :
	public IMetaClass
{
	DECLARE_METACLASS(IPhysicShellCreator)
public:
	virtual void CreatePhysicsShell() = 0;
};

