#include "StdAfx.h"
#include "EchoZone.h"

void CEchoZone::feel_sound_new(CObject* who, int type, CSound_UserDataPtr user_data, const Fvector& Position,
	float power)
{
	// Power: from 0.0 (no sound) to 1.0 (max loudness)
	Msg("EchoZone sound feel: power = [%f]", power);
}

void CEchoZone::Load(LPCSTR section)
{
	CCustomZone::Load(section);
	ISpatial* self = smart_cast<ISpatial*> (this);
	self->spatial.type |= STYPE_REACTTOSOUND;
	//spatial.type |= STYPE_REACTTOSOUND;
	//if (self) {
	//	self->spatial.type &= ~STYPE_REACTTOSOUND;
	//}
}
