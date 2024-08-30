#pragma once

#include "inventory_item.h"

class CPhysicItem;
class CEntityAlive;
class CActor;

class CEatableItem : public CInventoryItem {
private:
	typedef CInventoryItem	inherited;

protected:
	CPhysicItem		*m_physic_item;

	u8 m_iMaxUses;
	u8 m_iRemainingUses;
	float m_fWeightFull;
	float m_fWeightEmpty;

public:
							CEatableItem				();
	~CEatableItem				() override;
	DLL_Pure*		_construct					() override;
	CEatableItem	*cast_eatable_item			() override {return this;}

	void			Load						(LPCSTR section) override;
	bool			Useful						() const override;

	BOOL			net_Spawn					(CSE_Abstract* DC) override;

	void			OnH_B_Independent			(bool just_before_destroy) override;
	void			OnH_A_Independent			() override;
	void			save						(NET_Packet &output_packet) override;
	void			load						(IReader &input_packet) override;
			void			UpdateInRuck				(CActor* actor);
			void			UpdateUseAnim				(CActor* actor);
			void			HideWeapon					();
			void			StartAnimation				();

			void SetRemainingUses(u8 value) { if (value > m_iMaxUses) return; m_iRemainingUses = value; };
	IC		u8 GetMaxUses() const { return m_iMaxUses; };
	IC		u8 GetRemainingUses() const { return m_iRemainingUses; };

	virtual	bool			UseBy						(CEntityAlive* npc);
	virtual	bool			Empty						()						{return m_iRemainingUses==0;};
	u32				Cost						()	const override;
	float			Weight						()	const override;

	virtual bool				CheckInventoryIconItemSimilarity(CInventoryItem* other) override;

			//u32				m_iConstPortions;
			//u32				m_iPortionsNum;
			bool			m_bHasAnimation;
			bool			m_bUnlimited;
			bool			m_bActivated;
			bool			m_bItmStartAnim;
			bool			m_bNeedDestroyNotUseful;
			int				m_iAnimHandsCnt;
			int				m_iAnimLength;
			float			m_fEffectorIntensity;
			float			m_fRadioactivity;
			float			m_fIrradiationCoef;
			float			m_fIrradiationZonePower;
			float			m_fSpoliage;
			float			m_fFoodRottingCoef;
			LPCSTR			anim_sect;
			shared_str		use_cam_effector;
			ref_sound		m_using_sound;
};

