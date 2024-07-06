#pragma once
#include "ExplosiveRocket.h"

class CMissileSam: public CExplosiveRocket
{
	using inherited = CExplosiveRocket;

	CGameObject* target = nullptr;

public:
	void SetTarget(CGameObject* target) { this->target = target; }

};
