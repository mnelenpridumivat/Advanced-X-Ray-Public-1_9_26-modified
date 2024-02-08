////////////////////////////////////////////////////////////////////////////
//	Module 		: eatable_item_object.h
//	Created 	: 24.03.2003
//  Modified 	: 29.01.2004
//	Author		: Yuri Dobronravin
//	Description : Eatable item object implementation
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "physic_item.h"
#include "eatable_item.h"

class CEatableItemObject : 
	public CEatableItem, 
	public CPhysicItem,
	public IMetaClass
{
	DECLARE_METACLASS2(CEatableItemObject, CEatableItem, CPhysicItem)
public:
							CEatableItemObject	();
							~CEatableItemObject	() override;
							DLL_Pure		*_construct			() override;

public:
							CPhysicsShellHolder	*cast_physics_shell_holder	() override {return this;}
							CInventoryItem		*cast_inventory_item		() override {return this;}
							CAttachableItem		*cast_attachable_item		() override {return this;}
							CWeapon				*cast_weapon				() override {return 0;}
							CFoodItem			*cast_food_item				() override {return 0;}
							CMissile			*cast_missile				() override {return 0;}
							CHudItem			*cast_hud_item				() override {return 0;}
							CWeaponAmmo			*cast_weapon_ammo			() override {return 0;}
							CGameObject			*cast_game_object			() override {return this;};

public:
							void	Load					(LPCSTR section) override;
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
							void	load					(IReader &input_packet) override;
							BOOL	net_SaveRelevant		() override {return TRUE;}
							void	renderable_Render		() override;
							void	reload					(LPCSTR section) override;
							void	reinit					() override;
							void	activate_physic_shell	() override;
							void	on_activate_physic_shell() override;
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

	DECLARE_SCRIPT_REGISTER_FUNCTION

protected:
							bool	use_parent_ai_locations	() const override
							{
		return CAttachableItem::use_parent_ai_locations();
	}
};

add_to_type_list(CEatableItemObject)
#undef script_type_list
#define script_type_list save_type_list(CEatableItemObject)
