#pragma once

#include "weaponpistol.h"
#include "script_export_space.h"

class CWeaponWalther :
	public CWeaponPistol,
	public IMetaClass
{
	DECLARE_METACLASS1(CWeaponWalther, CWeaponPistol)
	typedef CWeaponPistol inherited;
public:
	CWeaponWalther(void);
	~CWeaponWalther(void) override;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponWalther)
#undef script_type_list
#define script_type_list save_type_list(CWeaponWalther)
