#pragma once

#include "weaponShotgun.h"
#include "script_export_space.h"

class CWeaponBM16 :
	public CWeaponShotgun,
	public IMetaClass
{
	DECLARE_METACLASS1(CWeaponBM16, CWeaponShotgun)
	typedef CWeaponShotgun inherited;

public:
	~CWeaponBM16					() override;
	void	Load							(LPCSTR section) override;

protected:
	void	PlayAnimShoot					() override;
	void	PlayAnimReload					() override;
	void	PlayReloadSound					() override;
	void	PlayAnimIdle					() override;
	void	PlayAnimIdleMoving				() override;
	void	PlayAnimIdleSprint				() override;
	void	PlayAnimShow					() override;
	void	PlayAnimHide					() override;
	void	PlayAnimBore					() override;
	void	PlayAnimIdleMovingSlow			() override;
	void	PlayAnimIdleMovingCrouch		() override;
	void	PlayAnimIdleMovingCrouchSlow	() override;
	void	PlayAnimSprintStart				() override;
	void	PlayAnimSprintEnd				() override;
	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponBM16)
#undef script_type_list
#define script_type_list save_type_list(CWeaponBM16)
