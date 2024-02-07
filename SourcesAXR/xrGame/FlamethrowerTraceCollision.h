#pragma once
#include "GlobalFeelTouch.hpp"

class CFlamethrower;

class CFlamethrowerTraceCollision: public Feel::Touch
{

	CFlamethrower* m_flamethrower;

public:

	CFlamethrowerTraceCollision(CFlamethrower* flamethrower);
	~CFlamethrowerTraceCollision();

};
