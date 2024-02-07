#ifndef PHSHELL_CREATOR_H
#define PHSHELL_CREATOR_H

#include "ph_shell_interface.h"

class CPHShellSimpleCreator: 
	public IPhysicShellCreator,
	public IMetaClass
{
	DECLARE_METACLASS1(CPHShellSimpleCreator, IPhysicShellCreator)
public:
	void CreatePhysicsShell() override;
protected:
private:
};
#endif