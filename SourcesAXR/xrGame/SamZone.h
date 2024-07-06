#pragma once
#include "hudsound.h"
#include "rocketlauncher.h"
#include "space_restrictor.h"

class CSamZone : public CSpaceRestrictor, public CRocketLauncher {
private:
	typedef CSpaceRestrictor			inherited;

protected:

	shared_str m_missile_section;

public:

	HUD_SOUND_COLLECTION_LAYERED	m_layered_sounds;

	void Load(LPCSTR		section) override;
	void LaunchMissile(CGameObject* target);

	virtual void OnEvent(NET_Packet& P, u16 type) override;

};
