#pragma once

#include "weaponcustompistol.h"
#include "script_export_space.h"

class CWeaponSVU :
	public CWeaponCustomPistol,
	public IMetaClass
{
	DECLARE_METACLASS1(CWeaponSVU, CWeaponCustomPistol)
	typedef CWeaponCustomPistol inherited;
public:
	CWeaponSVU(void);
	~CWeaponSVU(void) override;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponSVU)
#undef script_type_list
#define script_type_list save_type_list(CWeaponSVU)
