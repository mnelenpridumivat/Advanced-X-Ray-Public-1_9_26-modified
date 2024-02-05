#pragma once
#include "missile.h"
#include "explosive.h"
#include "../xrEngine/feel_touch.h"

class CGrenade :
	public CMissile,
	public CExplosive
{
	typedef CMissile		inherited;
public:
							CGrenade							();
	~CGrenade							() override;


	void			Load								(LPCSTR section) override;

	BOOL 			net_Spawn							(CSE_Abstract* DC) override;
	void 			net_Destroy							() override;
	void 			net_Relcase							(CObject* O ) override;

	void 			OnH_B_Independent					(bool just_before_destroy) override;
	void 			OnH_A_Independent					() override;
	void 			OnH_A_Chield						() override;
	void			DiscardState						() override;

	void 			OnEvent								(NET_Packet& P, u16 type) override;
	virtual bool			DropGrenade							();			//in this case if grenade state is eReady, it should Throw

	void 			OnAnimationEnd						(u32 state) override;
	void 			UpdateCL							() override;

	void 			Throw() override;
	void 			Destroy() override;


	bool			Action								(u16 cmd, u32 flags) override;
	bool			Useful								() const override;
	void			State								(u32 state) override;

	void			OnH_B_Chield						() override {inherited::OnH_B_Chield();}

	void			Hit									(SHit* pHDS) override;

	bool			NeedToDestroyObject					() const override;
	ALife::_TIME_ID	TimePassedAfterIndependant			() const override;

			void			PutNextToSlot						();

	void			DeactivateItem						() override;
	bool			GetBriefInfo						(II_BriefInfo& info) override;

	void			SendHiddenItem						() override;	//same as OnHiddenItem but for client... (sends message to a server)...
protected:
	ALife::_TIME_ID			m_dwGrenadeRemoveTime;
	ALife::_TIME_ID			m_dwGrenadeIndependencyTime;
protected:
	ESoundTypes				m_eSoundCheckout;
private:
	float					m_grenade_detonation_threshold_hit;
	bool					m_thrown;

protected:
	void			UpdateXForm							() override { CMissile::UpdateXForm(); };
public:
	BOOL			UsedAI_Locations					() override;
	CExplosive		*cast_explosive						() override {return this;}
	CMissile		*cast_missile						() override {return this;}
	CHudItem		*cast_hud_item						() override {return this;}
	CGameObject		*cast_game_object					() override {return this;}
	IDamageSource	*cast_IDamageSource					() override {return CExplosive::cast_IDamageSource();}

	typedef					fastdelegate::FastDelegate< void (CGrenade*) >	destroy_callback;
	void					set_destroy_callback				(destroy_callback callback) 
																{ m_destroy_callback = callback; }
private:
	destroy_callback		m_destroy_callback;
};
