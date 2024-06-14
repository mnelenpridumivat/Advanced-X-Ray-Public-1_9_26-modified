#pragma once

#include "customzone.h"
#include "../xrEngine/feel_sound.h"

class CEchoZone : public CCustomZone, public Feel::Sound
{
	typedef	CCustomZone	inherited;

public:
	void feel_sound_new(CObject* who, int type, CSound_UserDataPtr user_data, const Fvector& Position, float power) override;

};
