#pragma once

#include "WeaponMagazined.h"

class CWeaponCustomPistol: 
	public CWeaponMagazined, 
	public IMetaClass
{
	DECLARE_METACLASS1(CWeaponCustomPistol, CWeaponMagazined)
private:
	typedef CWeaponMagazined inherited;
public:
					CWeaponCustomPistol	();
	~CWeaponCustomPistol() override;
	int		GetCurrentFireMode() override;
protected:
	void	FireEnd				() override;
	void	switch2_Fire		() override;
};
