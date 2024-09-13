////////////////////////////////////////////////////////////////////////////
//	Module 		: inventory_item_object.h
//	Created 	: 24.03.2003
//  Modified 	: 27.12.2004
//	Author		: Victor Reutsky, Yuri Dobronravin
//	Description : Inventory item object implementation
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "physic_item.h"
#include "inventory_item.h"

class CInventoryItemObject : 
			public CInventoryItem, 
			public CPhysicItem
{
public:
							CInventoryItemObject	();
							~CInventoryItemObject	() override;
							DLL_Pure		*_construct				() override;

public:
							CPhysicsShellHolder*cast_physics_shell_holder	() override {return this;}
							CInventoryItem	*cast_inventory_item			() override {return this;}
							CAttachableItem	*cast_attachable_item			() override {return this;}
							CWeapon			*cast_weapon					() override {return nullptr;}
							CFoodItem		*cast_food_item					() override {return nullptr;}
							CMissile		*cast_missile					() override {return nullptr;}
							CHudItem		*cast_hud_item					() override {return nullptr;}
							CWeaponAmmo		*cast_weapon_ammo				() override {return nullptr;}
							CGameObject		*cast_game_object				() override {return this;};
							virtual CFlamethrower* cast_flamethrower() override { return nullptr; }

public:
							void	Load					(LPCSTR section) override;
//*	virtual LPCSTR	Name					();
//*	virtual LPCSTR	NameShort				();
							void	Hit						(SHit* pHDS) override;

							void	OnH_B_Independent		(bool just_before_destroy) override;
							void	OnH_A_Independent		() override;
							void	OnH_B_Chield			() override;
							void	OnH_A_Chield			() override;
							void	UpdateCL				() override;
							void	OnEvent					(NET_Packet& P, u16 type) override;
							BOOL	net_Spawn				(CSE_Abstract* DC) override;
							void	net_Destroy				() override;
							void	net_Import				(NET_Packet& P) override;					// import from server
							void	net_Export				(NET_Packet& P) override;					// export to server
							void	save					(NET_Packet &output_packet) override;
							void	load					(NET_Packet&input_packet) override;
							BOOL	net_SaveRelevant		() override {return TRUE;}
							void	renderable_Render		() override;
							void	reload					(LPCSTR section) override;
							void	reinit					() override;
							void	activate_physic_shell	() override;
							void	on_activate_physic_shell() override;
							void	modify_holder_params			(float &range, float &fov) const override;
public:
	////////// network //////////////////////////////////////////////////
							void	make_Interpolation		() override;
							void	PH_B_CrPr				() override; // actions & operations before physic correction-prediction steps
							void	PH_I_CrPr				() override; // actions & operations after correction before prediction steps
#ifdef DEBUG
							void	PH_Ch_CrPr				() override; // 
#endif
							void	PH_A_CrPr				() override; // actions & operations after phisic correction-prediction steps
							bool	NeedToDestroyObject		() const override;

protected:
#ifdef DEBUG
							void	OnRender				() override;
#endif

public:
							bool	Useful					() const override;

public:
							u32		ef_weapon_type			() const override;
protected:
							bool	use_parent_ai_locations	() const override
							{
		return CAttachableItem::use_parent_ai_locations();
	}

};

#include "inventory_item_object_inline.h"
