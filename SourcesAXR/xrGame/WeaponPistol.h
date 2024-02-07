#pragma once
#include "weaponcustompistol.h"

class CWeaponPistol :
	public CWeaponCustomPistol,
	public IMetaClass
{
	DECLARE_METACLASS1(CWeaponPistol, CWeaponCustomPistol)
	typedef CWeaponCustomPistol inherited;
public:
					CWeaponPistol	();
	~CWeaponPistol	() override;

	void	switch2_Reload	() override;

	void	OnAnimationEnd	(u32 state) override;
	void	net_Destroy		() override;
	void	OnH_B_Chield	() override;

protected:
	bool	AllowFireWhileWorking() override {return true;}

	ESoundTypes			m_eSoundClose;
};
