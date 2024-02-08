#ifndef __XR_WEAPON_LR300_H__
#define __XR_WEAPON_LR300_H__
#pragma once

#include "WeaponMagazined.h"
#include "script_export_space.h"

class CWeaponLR300:
	public CWeaponMagazined,
	public IMetaClass
{
	DECLARE_METACLASS1(CWeaponLR300, CWeaponMagazined)
private:
	typedef CWeaponMagazined inherited;
public:
	/*
	virtual	void	UpdateCL			();
	virtual void	renderable_Render	();
	virtual void	spatial_move		();
	virtual void	spatial_register	();
	virtual void	spatial_unregister	();
	*/

					CWeaponLR300		();
	~CWeaponLR300		() override;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponLR300)
#undef script_type_list
#define script_type_list save_type_list(CWeaponLR300)

#endif //__XR_WEAPON_LR300_H__
