#include "stdafx.h"
#include "HeliFlare.h"

#include "physics_shell_scripted.h"

void CHeliFlare::Launch(Fvector Direction)
{
	CPhysicsShell* shell = cast_physics_shell_holder()->PPhysicsShell();
	shell->applyImpulse(Direction.GetNormalizedCopy(), Direction.magnitude());
}
