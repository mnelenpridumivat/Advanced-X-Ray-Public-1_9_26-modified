#pragma once

#include "weaponmagazined.h"
#include "script_export_space.h"

class CWeaponVintorez :
	public CWeaponMagazined,
	public IMetaClass
{
	DECLARE_METACLASS1(CWeaponVintorez, CWeaponMagazined)
	typedef CWeaponMagazined inherited;
public:
	CWeaponVintorez(void);
	~CWeaponVintorez(void) override;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponVintorez)
#undef script_type_list
#define script_type_list save_type_list(CWeaponVintorez)
