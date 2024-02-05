#pragma once

#include "weaponcustompistol.h"
#include "script_export_space.h"

class CWeaponShotgun :	public CWeaponCustomPistol
{
	typedef CWeaponCustomPistol inherited;
public:
					CWeaponShotgun		();
	~CWeaponShotgun		() override;

	void	Load				(LPCSTR section) override;

	void	net_Destroy			() override;
	void	net_Export			(NET_Packet& P) override;
	void	net_Import			(NET_Packet& P) override;

	void	Reload				() override;
	void	switch2_Fire		() override;
	void			switch2_StartReload ();
	void			switch2_AddCartgidge();
	void			switch2_EndReload	();

	virtual void	PlayAnimOpenWeapon	();
	virtual void	PlayAnimAddOneCartridgeWeapon();
	void	PlayAnimAim			() override;
	void			PlayAnimCloseWeapon	();

	bool	Action(u16 cmd, u32 flags) override;

protected:
	void	OnAnimationEnd		(u32 state) override;
	void			TriStateReload		();
	void	OnStateSwitch		(u32 S) override;

	bool			HaveCartridgeInInventory(u8 cnt);
	virtual u8		AddCartridge		(u8 cnt);

	ESoundTypes		m_eSoundOpen;
	ESoundTypes		m_eSoundAddCartridge;
	ESoundTypes		m_eSoundClose_2;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponShotgun)
#undef script_type_list
#define script_type_list save_type_list(CWeaponShotgun)
