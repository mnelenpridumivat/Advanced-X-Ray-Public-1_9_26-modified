#pragma once
#include "missile.h"
#include "../xrphysics/DamageSource.h"
class CBolt :
	public CMissile,
	public IDamageSource,
	public IMetaClass
{
	DECLARE_METACLASS2(CBolt, CMissile, IDamageSource)
	typedef CMissile inherited;
	u16			m_thrower_id;
public:
				CBolt				();
	~CBolt				() override;

	void Load				(LPCSTR section) override;
	void OnH_A_Chield		() override;

	void SetInitiator		(u16 id) override;
	u16	 Initiator			() override;

	void Throw				() override;
	bool Action				(u16 cmd, u32 flags) override;
	bool Useful				() const override;
	void activate_physic_shell	() override;

	void		 PutNextToSlot		();
	void State				(u32 state) override;
	void OnAnimationEnd		(u32 state) override;

	BOOL UsedAI_Locations	() override {return FALSE;}
	IDamageSource*	cast_IDamageSource			() override {return this;}
};
