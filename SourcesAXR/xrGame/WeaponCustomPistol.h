#pragma once

#include "WeaponMagazined.h"

class CWeaponCustomPistol: public CWeaponMagazined
{
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
