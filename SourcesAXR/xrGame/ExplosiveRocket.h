//////////////////////////////////////////////////////////////////////
// ExplosiveRocket.h:	ракета, которой стреляет RocketLauncher 
//						взрывается при столкновении
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CustomRocket.h"
#include "Explosive.h"
#include "inventory_item.h"

class CExplosiveRocket : 
			public CCustomRocket,
			public CInventoryItem,
			public CExplosive
{
private:
	typedef CCustomRocket inherited;
	friend CRocketLauncher;
public:
	CExplosiveRocket(void);
	~CExplosiveRocket(void) override;
	DLL_Pure	*_construct	() override;
public:
	CExplosive					*cast_explosive			() override {return this;}
	CInventoryItem				*cast_inventory_item	() override {return this;}
	CAttachableItem				*cast_attachable_item	() override {return this;}
	CWeapon						*cast_weapon			() override {return NULL;}
	CGameObject					*cast_game_object		() override {return this;}
	IDamageSource*				cast_IDamageSource() override {return CExplosive::cast_IDamageSource();}
	void						on_activate_physic_shell() override;
public:
	void Load				(LPCSTR section) override;
	BOOL net_Spawn			(CSE_Abstract* DC) override;
	void net_Destroy		() override;
	void net_Relcase		(CObject* O ) override;
	void OnH_A_Independent	() override;
	void OnH_B_Independent	(bool just_before_destroy) override;
	void UpdateCL			() override;

	void Contact(const Fvector &pos, const Fvector &normal) override;

	void OnEvent (NET_Packet& P, u16 type) override;

	void Hit	(SHit* pHDS) override
	{ inherited::Hit(pHDS); };

public:
	BOOL			UsedAI_Locations	() override {return inherited::UsedAI_Locations();}
	void			net_Import			(NET_Packet& P) override {inherited::net_Import(P);}
	void			net_Export			(NET_Packet& P) override {inherited::net_Export(P);}

	void			save				(NET_Packet &output_packet) override {inherited::save(output_packet);}
	void			load				(IReader &input_packet) override {inherited::load(input_packet);}
	BOOL			net_SaveRelevant	() override {return inherited::net_SaveRelevant();}

	void			OnH_A_Chield		() override {inherited::OnH_A_Chield();}
	void			OnH_B_Chield		() override {inherited::OnH_B_Chield();}
	void			renderable_Render	() override {inherited::renderable_Render();}
	void			make_Interpolation	() override;
	void			PH_B_CrPr			() override; // actions & operations before physic correction-prediction steps
	void			PH_I_CrPr			() override; // actions & operations after correction before prediction steps
#ifdef DEBUG
	void			PH_Ch_CrPr			() override; // 
	void			OnRender			() override;
#endif
	void			PH_A_CrPr			() override; // actions & operations after phisic correction-prediction steps
	void			reinit				() override;
	void			reload				(LPCSTR section) override;
	void			activate_physic_shell	() override;
	void			setup_physic_shell		() override;
	void			create_physic_shell		() override;

public:
	bool			Useful				() const override;
protected:
	bool	use_parent_ai_locations	() const override
	{
		return CAttachableItem::use_parent_ai_locations();
	}
};