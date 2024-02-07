#pragma once
#include "inventory_item_object.h"
#include "anticheat_dumpable_object.h"
#include "CartrigeParam.h"

class CCartridge : public IAnticheatDumpable
{
public:
	CCartridge();
	void Load(LPCSTR section, u8 LocalAmmoType);
	float Weight() const;

	shared_str	m_ammoSect;
	enum{
		cfTracer				= (1<<0),
		cfRicochet				= (1<<1),
		cfCanBeUnlimited		= (1<<2),
		cfExplosive				= (1<<3),
		cfMagneticBeam			= (1<<4),
	};
	SCartridgeParam param_s;

	u8		m_LocalAmmoType;

	u16		bullet_material_idx;
	Flags8	m_flags;

	shared_str	m_InvShortName;
	void				DumpActiveParams		(shared_str const & section_name, CInifile & dst_ini) const override;
	shared_str const 	GetAnticheatSectionName	() const override { return m_ammoSect; };
};

class CWeaponAmmo :	
	public CInventoryItemObject {
	typedef CInventoryItemObject		inherited;
public:
									CWeaponAmmo			(void);
	~CWeaponAmmo		(void) override;

	CWeaponAmmo				*cast_weapon_ammo	() override {return this;}
	void					Load				(LPCSTR section) override;
	BOOL					net_Spawn			(CSE_Abstract* DC) override;
	void					net_Destroy			() override;
	void					net_Export			(NET_Packet& P) override;
	void					net_Import			(NET_Packet& P) override;
	void					OnH_B_Chield		() override;
	void					OnH_B_Independent	(bool just_before_destroy) override;
	void					UpdateCL			() override;
	void					renderable_Render	() override;

	bool					Useful				() const override;
	float					Weight				() const override;
	u32						Cost				() const override;

	bool							Get					(CCartridge &cartridge);

	SCartridgeParam cartridge_param;

	u16			m_boxSize;
	u16			m_boxCurr;
	bool		m_tracer;

public:
	CInventoryItem *can_make_killing	(const CInventory *inventory) const override;
};
