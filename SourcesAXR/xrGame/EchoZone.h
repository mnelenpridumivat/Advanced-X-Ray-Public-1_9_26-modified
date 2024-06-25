#pragma once

#include "customzone.h"
#include "Explosive.h"
#include "../xrEngine/feel_sound.h"

class CEchoZone : public CCustomZone, public Feel::Sound//, public CExplosive
{
	typedef	CCustomZone	inherited;

protected:

	float DamageMax = 0.0f;

public:
	void feel_sound_new(CObject* who, int type, CSound_UserDataPtr user_data, const Fvector& Position, float power) override;
	void Load(LPCSTR section) override;
	Feel::Sound* dcast_FeelSound() override { return this; }
};
