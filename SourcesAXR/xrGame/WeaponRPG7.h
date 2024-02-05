#pragma once

#include "weaponpistol.h"
#include "rocketlauncher.h"
#include "script_export_space.h"

class CWeaponRPG7 :	public CWeaponCustomPistol,
					public CRocketLauncher
{
private:
	typedef CWeaponCustomPistol inherited;
public:
				CWeaponRPG7		();
	~CWeaponRPG7	() override;

	BOOL net_Spawn		(CSE_Abstract* DC) override;
	void OnStateSwitch	(u32 S) override;
	void OnEvent		(NET_Packet& P, u16 type) override;
	void ReloadMagazine	() override;
	void Load			(LPCSTR section) override;
	void switch2_Fire	() override;
	void FireTrace		(const Fvector& P, const Fvector& D) override;
	void on_a_hud_attach() override;

	void FireStart		() override;
	void SwitchState	(u32 S) override;

			void UpdateMissileVisibility	();
	void UnloadMagazine				(bool spawn_ammo = true) override;

	void net_Import			( NET_Packet& P) override;				// import from server
protected:
	bool	AllowBore		() override;
	void	PlayAnimReload	() override;

	shared_str	m_sRocketSection;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponRPG7)
#undef script_type_list
#define script_type_list save_type_list(CWeaponRPG7)
