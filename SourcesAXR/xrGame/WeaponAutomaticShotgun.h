#pragma once
#include "WeaponMagazined.h"
#include "WeaponShotgun.h"
#include "script_export_space.h"

class CWeaponAutomaticShotgun :	public CWeaponMagazined
{
	typedef CWeaponMagazined inherited;
public:
					CWeaponAutomaticShotgun	();
	~CWeaponAutomaticShotgun() override;

	void	Load					(LPCSTR section) override;

	void	net_Export				(NET_Packet& P) override;
	void	net_Import				(NET_Packet& P) override;

	void	Reload					() override;
	void			switch2_StartReload		();
	void			switch2_AddCartgidge	();
	void			switch2_EndReload		();

	virtual void	PlayAnimOpenWeapon		();
	virtual void	PlayAnimAddOneCartridgeWeapon();
	void			PlayAnimCloseWeapon		();

	bool	Action					(u16 cmd, u32 flags) override;
	int		GetCurrentFireMode	() override { return m_aFireModes[m_iCurFireMode]; };

protected:
	void	OnAnimationEnd			(u32 state) override;
	void			TriStateReload			();
	void	OnStateSwitch			(u32 S) override;

	bool			HaveCartridgeInInventory(u8 cnt);
	virtual u8		AddCartridge			(u8 cnt);

	ESoundTypes		m_eSoundOpen;
	ESoundTypes		m_eSoundAddCartridge;
	ESoundTypes		m_eSoundClose_2;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
