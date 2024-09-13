#pragma once
#include "weaponmagazined.h"
#include "rocketlauncher.h"


class CWeaponFakeGrenade;


class CWeaponMagazinedWGrenade : public CWeaponMagazined,
								 public CRocketLauncher
{
	typedef CWeaponMagazined inherited;
public:
					CWeaponMagazinedWGrenade	(ESoundTypes eSoundType=SOUND_TYPE_WEAPON_SUBMACHINEGUN);
	~CWeaponMagazinedWGrenade	() override;

	void	Load				(LPCSTR section) override;

	BOOL	net_Spawn			(CSE_Abstract* DC) override;
	void	net_Destroy			() override;
	void	net_Export			(NET_Packet& P) override;
	void	net_Import			(NET_Packet& P) override;

	void	OnH_B_Independent	(bool just_before_destroy) override;

	void	save				(NET_Packet &output_packet) override;
	void	load				(NET_Packet&input_packet) override;

	// Mortan: Новые параметры здеся
	bool    bMarkCanShow		() override { return IsZoomed() && !m_bGrenadeMode; }
	void	UpdateSecondVP		(bool bInGrenade = false) override;
	bool	bInZoomRightNow		() const override { return (m_zoom_params.m_fZoomRotationFactor > 0.05) && !m_bGrenadeMode; }
	void    CheckMagazine		() override;
	//=========================================

	bool	Attach					(PIItem pIItem, bool b_send_event) override;
	bool	Detach					(const char* item_section_name, bool b_spawn_item) override;
	bool	CanAttach				(PIItem pIItem) override;
	bool	CanDetach				(const char* item_section_name) override;
	void	InitAddons				() override;
	bool	UseScopeTexture			() override;
	float	CurrentZoomFactor		() override;
	u8		GetCurrentHudOffsetIdx	() override;
	void	FireEnd					() override;
			void	LaunchGrenade			();

	void	OnStateSwitch	(u32 S) override;

	void	switch2_Reload	() override;
	void    switch2_Unmis	() override;
	void	state_Fire		(float dt) override;
	void	OnShot			() override;
	void	OnEvent			(NET_Packet& P, u16 type) override;
	void	ReloadMagazine	() override;
	void	OnMotionMark	(u32 state, const motion_marks& M) override;

	bool	Action			(u16 cmd, u32 flags) override;

	void	UpdateSounds	() override;

	//переключение в режим подствольника
	bool	SwitchMode		() override;
	void			PerformSwitchGL	();
	void			OnAnimationEnd	(u32 state) override;
	void	OnMagazineEmpty	() override;
	bool	GetBriefInfo			(II_BriefInfo& info) override;

	bool	IsNecessaryItem	    (const shared_str& item_sect) override;

	bool			IsGrenadeMode		() const override { return m_bGrenadeMode; }

	//виртуальные функции для проигрывания анимации HUD
	void	PlayAnimShow		() override;
	void	PlayAnimHide		() override;
	void	PlayAnimReload		() override;
	void	PlayAnimIdle		() override;
	void	PlayAnimShoot		() override;
	virtual void	PlayAnimModeSwitch	();
	void	PlayAnimBore		() override;
	void	PlayAnimFireMode	() override;
	void	PlayAnimLaserSwitch	() override;
	void	PlayAnimFlashlightSwitch() override;
	
private:
	void	net_Spawn_install_upgrades	( Upgrades_type saved_upgrades ) override;
	bool	install_upgrade_impl		( LPCSTR section, bool test ) override;
	bool	install_upgrade_ammo_class	( LPCSTR section, bool test ) override;
	
			int		GetAmmoCount2				( u8 ammo2_type ) const;

public:
	//дополнительные параметры патронов 
	//для подствольника
//-	CWeaponAmmo*			m_pAmmo2;
	xr_vector<shared_str>	m_ammoTypes2;
	u8						m_ammoType2;

	int						iMagazineSize2;
	xr_vector<CCartridge>	m_magazine2;

	bool					m_bGrenadeMode;

	CCartridge				m_DefaultCartridge2;
	u8						iAmmoElapsed2;

	int						iAmmoElapsedMain;

	bool					IsMainMagazineEmpty() { return iAmmoElapsedMain <= 0; }

	virtual void UpdateGrenadeVisibility(bool visibility);
};