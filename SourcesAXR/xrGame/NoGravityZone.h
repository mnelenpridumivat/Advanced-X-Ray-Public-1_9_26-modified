#pragma once
#include "CustomZone.h"

class CNoGravityZone :
	public CCustomZone
{
typedef CCustomZone inherited;
public:
	void	Affect(SZoneObjectInfo* O) override;

#ifdef DEBUG
	virtual void				OnRender() override;
#endif

protected:
	void	enter_Zone						(SZoneObjectInfo& io) override;
	void	exit_Zone						(SZoneObjectInfo& io) override;

private:
	void	switchGravity					(SZoneObjectInfo& io,bool val)		;
	void	UpdateWorkload					(u32	dt	) override;

	enum class EAffectedObjectState
	{
		Raise,
		Pull,
		Idle,
	};
#ifdef DEBUG
	EAffectedObjectState PlayerState = EAffectedObjectState::Idle;
	Fvector PlayerPos{};
	Fvector NormDir{};
	float Power = 0.0f;
#endif

	Fvector GetMoveVector(Fvector ObjPos, EAffectedObjectState State);
	Fvector GetTargetPos(EAffectedObjectState State);

	struct FAffectedObject
	{
		EAffectedObjectState State;
		float Time = 0.0f;
	};

	xr_map<CGameObject*, FAffectedObject> AffectedObjects;
	float PullCurveCoeff = 1.0f;
	float m_fThrowInImpulseAlive = 60.0f;
	//float RaiseAcceleration = 1.226f;
	float RaiseAcceleration = 30.0f;
	float PullAcceleration = 19.62f;
	float RaiseTime = 20.0f;
	float PullTime = 1.0f;
	float IdleTime = 70.5f;

};