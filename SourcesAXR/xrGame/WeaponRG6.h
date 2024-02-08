#pragma once

#include "rocketlauncher.h"
#include "weaponShotgun.h"
#include "script_export_space.h"

class CWeaponRG6 :
	public CRocketLauncher,
	public CWeaponShotgun,
	public IMetaClass
{
	DECLARE_METACLASS2(CWeaponRG6, CRocketLauncher, CWeaponShotgun)
	typedef CRocketLauncher		inheritedRL;
	typedef CWeaponShotgun		inheritedSG;
	
public:
	~CWeaponRG6				() override;
	BOOL	net_Spawn				(CSE_Abstract* DC) override;
	void	Load					(LPCSTR section) override;
	void	OnEvent					(NET_Packet& P, u16 type) override;
protected:
	void	FireStart				() override;
	u8		AddCartridge			(u8 cnt) override;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponRG6)
#undef script_type_list
#define script_type_list save_type_list(CWeaponRG6)
