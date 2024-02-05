#pragma once

#include "hud_item_object.h"

class CCustomBackpack : public CHudItemObject
{
	typedef	CHudItemObject	inherited;
public:
	CCustomBackpack();
	~CCustomBackpack() override;

	BOOL 	net_Spawn(CSE_Abstract* DC) override;
	void	Load(LPCSTR section) override;

	void 	OnH_A_Chield() override;
	void 	OnH_B_Independent(bool just_before_destroy) override;

	void 	shedule_Update(u32 dt) override;
	void 	UpdateCL() override;

	void 	OnMoveToSlot(const SInvItemPlace& prev) override;
	void 	OnMoveToRuck(const SInvItemPlace& prev) override;
	void	OnActiveItem() override;
	void	OnHiddenItem() override;

	void			ToggleBackpack();
	void			HideBackpack();
	void			ShowBackpack();

	void	OnStateSwitch(u32 S) override;
	void	OnAnimationEnd(u32 state) override;
	void	UpdateXForm() override;

	float			GetInventoryCapacity() const { return m_fInventoryCapacity; }

	float			m_fPowerLoss;
	float			m_additional_weight;
	float			m_additional_weight2;

	float			m_fHealthRestoreSpeed;
	float 			m_fRadiationRestoreSpeed;
	float 			m_fSatietyRestoreSpeed;
	float			m_fPowerRestoreSpeed;
	float			m_fBleedingRestoreSpeed;
	float 			m_fThirstRestoreSpeed;
	float 			m_fIntoxicationRestoreSpeed;
	float 			m_fSleepenessRestoreSpeed;
	float 			m_fAlcoholismRestoreSpeed;
	float 			m_fNarcotismRestoreSpeed;
	float 			m_fPsyHealthRestoreSpeed;

	float			m_fJumpSpeed;
	float			m_fWalkAccel;
	float			m_fOverweightWalkK;

	float			m_fInventoryCapacity;

protected:
	bool	install_upgrade_impl(LPCSTR section, bool test) override;
};

