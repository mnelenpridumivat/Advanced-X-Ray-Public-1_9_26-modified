#pragma once

#include "ai_sounds.h"
#include "weapon.h"


class CFlamethrower : public CWeapon
{
private:
	typedef CWeapon inherited;
protected:
	//звук текущего выстрела
	shared_str		m_sSndShotCurrent;

	ESoundTypes		m_eSoundShow;
	ESoundTypes		m_eSoundHide;
	ESoundTypes		m_eSoundShot;
	ESoundTypes		m_eSoundEmptyClick;
	ESoundTypes		m_eSoundReload;
	ESoundTypes		m_eSoundClose;
	ESoundTypes		m_eSoundReflect;
	bool			m_sounds_enabled;
	// General
	//кадр момента пересчета UpdateSounds
	u32				dwUpdateSounds_Frame;

	virtual void    CheckMagazine();

	bool            m_bNeedBulletInGun;

	bool            m_bCustomShotSounds;
protected:
	void	OnMagazineEmpty() override;

	virtual void	switch2_Idle();
	virtual void	switch2_Fire();
	virtual void	switch2_Empty();
	virtual void	switch2_Reload();
	virtual void	switch2_Hiding();
	virtual void	switch2_Hidden();
	virtual void	switch2_Showing();
	virtual void    switch2_Unmis();

	void	OnShot() override;

	virtual void	OnEmptyClick();

	void	OnAnimationEnd(u32 state) override;
	void	OnStateSwitch(u32 S) override;

	virtual void	UpdateSounds();

	bool			TryReload();

protected:
	virtual void	ReloadMagazine();

	virtual void	state_FireCharge(float dt);
	virtual void	state_Fire(float dt);
	virtual void	state_Idle(float dt);
	virtual void	state_MagEmpty(float dt);
	virtual void	state_Misfire(float dt);

public:
	CFlamethrower(ESoundTypes eSoundType = SOUND_TYPE_WEAPON_SUBMACHINEGUN);
	~CFlamethrower() override;

	void	Load(LPCSTR section) override;
	CFlamethrower* cast_flamethrower() override { return this; }

	bool    UseScopeTexture() override;
	void	SetDefaults() override;
	void	FireStart() override;
	void	FireEnd() override;
	void	Reload() override;


	void	UpdateCL() override;
	void	net_Destroy() override;
	void	net_Export(NET_Packet& P) override;
	void	net_Import(NET_Packet& P) override;

	void	OnH_A_Chield() override;

	bool	Attach(PIItem pIItem, bool b_send_event) override;
	bool	Detach(const char* item_section_name, bool b_spawn_item) override;
	bool	DetachScope(const char* item_section_name, bool b_spawn_item);
	bool	CanAttach(PIItem pIItem) override;
	bool	CanDetach(const char* item_section_name) override;

	void	InitAddons() override;

	bool	Action(u16 cmd, u32 flags) override;
	bool			IsAmmoAvailable();
	virtual void	UnloadMagazine(bool spawn_ammo = true);
	virtual int     CheckAmmoBeforeReload(u8& v_ammoType);
	void	OnMotionMark(u32 state, const motion_marks& M) override;

	bool	GetBriefInfo(II_BriefInfo& info) override;

protected:
	//скорость вылета остальных патронов
	float			m_fOldBulletSpeed;
	Fvector			m_vStartPos, m_vStartDir;
	//флаг того, что хотя бы один выстрел мы должны сделать
	//(даже если очень быстро нажали на курок и вызвалось FireEnd)
	bool			m_bFireSingleShot;

	//переменная блокирует использование
	//только разных типов патронов
	bool m_bLockType;
	bool m_bAutoreloadEnabled;
	bool m_opened;
	bool m_bUseFiremodeChangeAnim;

	// overheating
	bool m_is_overheated = false;
	float m_overheating_state = 0.0f;
	float m_overheating_decrease_speed = 0.0f;
	float m_overheating_increase_speed_min = 0.0f;
	float m_overheating_increase_speed_max = 0.0f;
	float m_overheating_reset_level_max = 0.0f;

	//shooting
	float m_charge_speed = 0.0f;
	float m_current_charge = 0.0f;

public:
	void	OnZoomIn() override;
	void	OnZoomOut() override;

	void	save(NET_Packet& output_packet) override;
	void	load(IReader& input_packet) override;

protected:
	bool	install_upgrade_impl(LPCSTR section, bool test) override;

protected:
	virtual bool	AllowFireWhileWorking() { return false; }

	//виртуальные функции для проигрывания анимации HUD
	virtual void	PlayAnimShow();
	virtual void	PlayAnimHide();
	virtual void	PlayAnimReload();
	void	PlayAnimIdle() override;
	virtual void	PlayAnimShoot();
	virtual void	PlayReloadSound();
	virtual void	PlayAnimAim();
	void	PlayAnimBore() override;
	void	PlayAnimIdleSprint() override;
	void	PlayAnimIdleMoving() override;

protected:

	virtual void    SetAnimFlag(u32 flag, LPCSTR anim_name);

	// Флаги наличия анимаций, будем их искать заранее, так будет намного проще мейби
	enum {
		ANM_SHOW_EMPTY = (1 << 0),
		ANM_HIDE_EMPTY = (1 << 1),
		ANM_AIM_EMPTY = (1 << 2),
		ANM_BORE_EMPTY = (1 << 3),
		ANM_SHOT_EMPTY = (1 << 4),
		ANM_SPRINT_EMPTY = (1 << 5),
		ANM_MOVING_EMPTY = (1 << 6),
		ANM_RELOAD_EMPTY = (1 << 7),
		ANM_RELOAD_EMPTY_GL = (1 << 8),
		ANM_SHOT_AIM = (1 << 9),
		ANM_SHOT_AIM_GL = (1 << 10),
		ANM_MISFIRE = (1 << 11),
		ANM_MISFIRE_GL = (1 << 12),
		ANM_IDLE_EMPTY = (1 << 13),
	};

	Flags32 psWpnAnimsFlag;

	bool WeaponSoundExist(LPCSTR section, LPCSTR sound_name, bool log = false) const;

	float	GetWeaponDeterioration() override;


	void	FireBullet(const Fvector& pos,
		const Fvector& dir,
		float fire_disp,
		const CCartridge& cartridge,
		u16 parent_id,
		u16 weapon_id,
		bool send_hit) override;
};