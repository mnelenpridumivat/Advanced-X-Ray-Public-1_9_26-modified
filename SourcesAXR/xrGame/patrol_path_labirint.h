#pragma once

#include "patrol_path_params.h"

struct LabirintNode
{
	
};

class CPatrolPathLabirint
{
	CPatrolPathParams* Path;
	xr_vector<std::shared_ptr<LabirintNode>> LabirintCorridors;

public:

	CPatrolPathLabirint(CPatrolPathParams* Path);


};

