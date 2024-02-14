#pragma once

#include "../../../../xrEngine/effectorPP.h"
#include "../../../CameraEffector.h"
#include "../../../../xrEngine/cameramanager.h"

class CVampirePPEffector :
	public CEffectorPP,
	public IMetaClass
{
	DECLARE_METACLASS1(CVampirePPEffector, CEffectorPP)

	typedef CEffectorPP inherited;	

	SPPInfo state;			//current state
	float	m_total;		// total PP time

public:
					CVampirePPEffector		(const SPPInfo &ppi, float life_time);
	BOOL	Process					(SPPInfo& pp) override;
};

//////////////////////////////////////////////////////////////////////////
// Vampire Camera Effector
//////////////////////////////////////////////////////////////////////////
class CVampireCameraEffector :
	public CEffectorCam,
	public IMetaClass
{
	DECLARE_METACLASS1(CVampireCameraEffector, CEffectorCam)

	typedef CEffectorCam inherited;	

	float	m_time_total;
	Fvector	dangle_target;
	Fvector dangle_current;

	float	m_dist;
	Fvector m_direction;

public:
					CVampireCameraEffector	(float time, const Fvector &src, const Fvector &tgt);
	BOOL	ProcessCam				(SCamEffectorInfo& info) override;
};



