////////////////////////////////////////////////////////////////////////////
//	Module 		: ai_trader.h
//	Created 	: 16.04.2003
//  Modified 	: 16.04.2003
//	Author		: Jim
//	Description : Trader class
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../CustomMonster.h"
#include "../../inventoryowner.h"
#include "../../script_entity.h"
#include "../../sound_player.h"
#include "../../AI_PhraseDialogManager.h"
#include "../../../xrServerEntities/script_export_space.h"

class CInventoryItem;
class CArtefact;
class CMotionDef;
class CBlend;
class CSoundPlayer;
class CTraderAnimation;

class CAI_Trader : public CEntityAlive, 
	public CInventoryOwner, 
	public CScriptEntity,
	public CAI_PhraseDialogManager,
	public IMetaClass
{
	DECLARE_METACLASS4(CAI_Trader, CEntityAlive, CInventoryOwner, CScriptEntity, CAI_PhraseDialogManager)
	typedef CEntityAlive inherited;

private:
	bool				m_busy_now;

public:
	CAI_Trader		();
	~CAI_Trader		() override;

	CAttachmentOwner*			cast_attachment_owner	() override {return this;}
	CInventoryOwner*			cast_inventory_owner	() override {return this;}
	CEntityAlive*				cast_entity_alive		() override {return this;}
	CEntity*					cast_entity				() override {return this;}
	CGameObject*				cast_game_object		() override {return this;}
	CPhysicsShellHolder*		cast_physics_shell_holder	() override {return this;}
	CParticlesPlayer*			cast_particles_player	() override {return this;}
	CScriptEntity*				cast_script_entity		() override {return this;}

	DLL_Pure	*_construct		() override;
	void		Load			( LPCSTR section ) override;
	BOOL		net_Spawn		( CSE_Abstract* DC ) override;
	void		net_Export		(NET_Packet& P) override;
	void		net_Import		(NET_Packet& P) override;
	void		net_Destroy		() override;

	void		save			(NET_Packet &output_packet) override;
	void		load			(IReader &input_packet) override;
	BOOL		net_SaveRelevant() override {return inherited::net_SaveRelevant();}

	void		Die				(CObject* who) override;
	virtual void		Think			();
	void		HitSignal		(float /**P/**/, Fvector &/**local_dir/**/,	CObject* /**who/**/, s16 /**element/**/) override {};
	void		HitImpulse		(float /**P/**/, Fvector &/**vWorldDir/**/, 	Fvector& /**vLocalDir/**/) override {};
	void		Hit				(SHit* pHDS) override {inherited::Hit(pHDS);}
	void		UpdateCL		() override;

	void		g_fireParams			(CHudItem* pHudItem, Fvector& P, Fvector& D) override;
	void		g_WeaponBones			(int &L, int &R1, int &R2) override;
	float		ffGetFov				()	const override {return 150.f;}
	float		ffGetRange				()	const override {return 30.f;}
	void		OnEvent					(NET_Packet& P, u16 type) override;
	virtual	void		feel_touch_new			(CObject* O);
	virtual	void		DropItemSendMessage		(CObject *O);
	void		shedule_Update			(u32 dt) override;

	BOOL		UsedAI_Locations		() override;

	///////////////////////////////////////////////////////////////////////
	u16					PHGetSyncItemsNumber	() override {return inherited ::PHGetSyncItemsNumber();}
	CPHSynchronize*		PHGetSyncItem			(u16 item) override {return inherited ::PHGetSyncItem(item);}
	void				PHUnFreeze				() override {return inherited ::PHUnFreeze();}
	void				PHFreeze				() override {return inherited ::PHFreeze();}
	///////////////////////////////////////////////////////////////////////

	void			reinit					() override;
	void			reload					(LPCSTR section) override;

static	void	_BCL		BoneCallback			(CBoneInstance *B);

	void			LookAtActor				(CBoneInstance *B);

	void			OnStartTrade			();
	void			OnStopTrade				();

	//игровое имя 
	LPCSTR			Name					() const override {return CInventoryOwner::Name();}

	bool			can_attach				(const CInventoryItem *inventory_item) const override;
	bool			use_bolts				() const override;
	void			spawn_supplies			() override;


	bool			bfAssignSound			(CScriptEntityAction *tpEntityAction) override;

	ALife::ERelationType tfGetRelationType	(const CEntityAlive *tpEntityAlive) const override;

	//////////////////////////////////////////////////////////////////////////
	//генерируемые задания
public:
	//проверяет список артефактов в заказах
	virtual	u32				ArtefactPrice			(CArtefact* pArtefact);
	//продажа артефакта, с последуещим изменением списка заказов  (true - если артефакт был в списке)
	virtual	bool			BuyArtefact				(CArtefact* pArtefact);

public:
	IC		bool			busy_now				() const
	{
		return				(m_busy_now);
	}

private:
	CSoundPlayer			*m_sound_player;

public:
	IC		CSoundPlayer	&sound					() const
	{
		VERIFY				(m_sound_player);
		return				(*m_sound_player);
	}

	bool			unlimited_ammo			() override {return false;};
	bool			natural_weapon			() const override {return false;}
	bool			natural_detector		() const override {return false;}
	bool			AllowItemToTrade 		(CInventoryItem const * item, const SInvItemPlace& place) const override;

			void			dialog_sound_start		(LPCSTR phrase);
			void			dialog_sound_stop		();

private:
	CTraderAnimation	*AnimMan;
public:
	CTraderAnimation	&animation					() {return (*AnimMan);}
	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CAI_Trader)
#undef script_type_list
#define script_type_list save_type_list(CAI_Trader)
