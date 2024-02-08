//////////////////////////////////////////////////////////////////////
// ExplosiveItem.h: класс для вещи которая взрывается под 
//					действием различных хитов (канистры,
//					балоны с газом и т.д.)
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Explosive.h"
#include "inventory_item_object.h"
#include "DelayedActionFuse.h"
class CExplosiveItem: 
	public CInventoryItemObject	,
	public CDelayedActionFuse	,
	public CExplosive,
	public IMetaClass
{
	DECLARE_METACLASS3(CExplosiveItem, CInventoryItemObject, CDelayedActionFuse, CExplosive)
private:
	typedef CInventoryItemObject inherited;

public:
	CExplosiveItem(void);
	~CExplosiveItem(void) override;

	void				Load					(LPCSTR section) override;
	BOOL				net_Spawn				(CSE_Abstract* DC) override {return CInventoryItemObject::net_Spawn(DC);}
	void				net_Destroy				() override;
	void				net_Export				(NET_Packet& P) override {CInventoryItemObject::net_Export(P);}
	void				net_Import				(NET_Packet& P) override {CInventoryItemObject::net_Import(P);}
	void				net_Relcase				(CObject* O ) override;
	CGameObject			*cast_game_object		() override {return this;}
	CExplosive*			cast_explosive			() override {return this;}
	IDamageSource*		cast_IDamageSource		() override {return CExplosive::cast_IDamageSource();}
	void				GetRayExplosionSourcePos(Fvector &pos) override;
	void				ActivateExplosionBox	(const Fvector &size,Fvector &in_out_pos) override;
	void				OnEvent					(NET_Packet& P, u16 type) override;
	void				Hit						(SHit* pHDS) override;
	void				shedule_Update			(u32 dt) override;
	bool				shedule_Needed			() override;

	void				UpdateCL				() override;
	void				renderable_Render		() override;
	void				ChangeCondition			(float fDeltaCondition) override {CInventoryItem::ChangeCondition(fDeltaCondition);};
	void				StartTimerEffects		() override;

};