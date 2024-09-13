#pragma once

#include "inventory_item_object.h"

struct SBoneProtections;

class CHelmet: public CInventoryItemObject {
private:
    typedef	CInventoryItemObject inherited;
public:
							CHelmet					();
    ~CHelmet				() override;

    void			Load					(LPCSTR section) override;
	
	virtual void			Hit						(float P, ALife::EHitType hit_type);
    void			UpdateCL				() override;

	shared_str				m_BonesProtectionSect;
	shared_str				m_NightVisionSect;

	xr_vector<shared_str>	m_SuitableFilters;
	xr_vector<shared_str>	m_SuitableRepairKits;
	xr_vector<std::pair<shared_str, int>> m_ItemsForRepair;

    void			OnMoveToSlot			(const SInvItemPlace& previous_place) override;
    void			OnMoveToRuck			(const SInvItemPlace& previous_place) override;
    BOOL			net_Spawn				(CSE_Abstract* DC) override;
    void			net_Export				(NET_Packet& P) override;
    void			net_Import				(NET_Packet& P) override;
    void			OnH_A_Chield			() override;
    void			save					(NET_Packet& output_packet) override;
    void			load					(NET_Packet& input_packet) override;
			void			UpdateFilterCondition	(void);
			float			GetFilterCondition		(void) const;
			void			SetFilterCondition		(float val);
			float			GetDegradationSpeed		(void) const;
			void			FilterReplace			(float val);
			bool			IsNecessaryItem			(const shared_str& item_sect, xr_vector<shared_str> item);

			IC int			GetHelmetNV_Type		() const { return m_NightVisionType; }

	float					GetDefHitTypeProtection	(ALife::EHitType hit_type);
	float					GetHitTypeProtection	(ALife::EHitType hit_type, s16 element);
	float					GetBoneArmor			(s16 element);

	float					HitThroughArmor			(float hit_power, s16 element, float ap, bool& add_wound, ALife::EHitType hit_type);

	virtual bool				CheckInventoryIconItemSimilarity(CInventoryItem* other) override;

	float					m_fPowerLoss;
	float					m_fHealthRestoreSpeed;
	float 					m_fRadiationRestoreSpeed;
	float 					m_fSatietyRestoreSpeed;
	float					m_fPowerRestoreSpeed;
	float					m_fBleedingRestoreSpeed;
	float					m_fFilterDegradation;
	float					m_fMaxFilterCondition;
	float					m_fFilterCondition;

	float					m_fShowNearestEnemiesDistance;

	bool					m_bSecondHelmetEnabled;
	bool					m_b_HasGlass;
	bool					m_bUseFilter;

	shared_str				m_sShaderNightVisionSect;
	u32						m_NightVisionType;
	float					m_fNightVisionLumFactor;

	void					ReloadBonesProtection	();
	void					AddBonesProtection		(LPCSTR bones_section);
protected:
	HitImmunity::HitTypeSVec	m_ConstHitTypeProtection;
	HitImmunity::HitTypeSVec	m_HitTypeProtection;
	SBoneProtections*		m_boneProtection;	

protected:
    bool			install_upgrade_impl	( LPCSTR section, bool test ) override;
};
