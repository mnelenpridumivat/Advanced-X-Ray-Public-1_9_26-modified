#pragma once

#include "../xrEngine/Effector.h"

// приседание после падения
class CEffectorFall : public CEffectorCam
{
	float	fPower;
	float	fPhase;
public:
					CEffectorFall	(float power, float life_time=1);
	BOOL	ProcessCam		(SCamEffectorInfo& info) override;
};

class CEffectorDOF : public CEffectorCam
{
	float			m_fPhase;
public:
					CEffectorDOF	(const Fvector4& dof);
	BOOL	ProcessCam		(SCamEffectorInfo& info) override;
};
