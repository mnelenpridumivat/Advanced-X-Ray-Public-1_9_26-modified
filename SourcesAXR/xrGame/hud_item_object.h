#pragma once

#include "inventory_item_object.h"
#include "huditem.h"

class CHudItemObject : 
		public CInventoryItemObject,
		public CHudItem,
		public IMetaClass
{
	DECLARE_METACLASS2(CHudItemObject, CInventoryItemObject, CHudItem)

protected: //чтоб нельзя было вызвать на прямую
						CHudItemObject		();
						~CHudItemObject		() override;

public:
						DLL_Pure	*_construct			() override;

public:
						CHudItem	*cast_hud_item		() override {return this;}

public:
						void		Load				(LPCSTR section) override;
						bool		Action				(u16 cmd, u32 flags) override;
						void		SwitchState			(u32 S) override;
						void		OnStateSwitch		(u32 S) override;
						void		OnEvent				(NET_Packet& P, u16 type) override;
						void		OnH_A_Chield		() override;
						void		OnH_B_Chield		() override;
						void		OnH_B_Independent	(bool just_before_destroy) override;
						void		OnH_A_Independent	() override;
						BOOL		net_Spawn			(CSE_Abstract* DC) override;
						void		net_Destroy			() override;
						bool		ActivateItem		() override;
						void		DeactivateItem	() override;
						void		UpdateCL			() override;
						void		renderable_Render	() override;
						void		on_renderable_Render() override;
						void		OnMoveToRuck		(const SInvItemPlace& prev) override;

						bool			use_parent_ai_locations	() const override
						{
		return				CInventoryItemObject::use_parent_ai_locations	() && (Device.dwFrame != dwXF_Frame);
	}
};
