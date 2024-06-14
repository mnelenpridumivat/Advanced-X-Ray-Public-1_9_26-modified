#pragma once
#include "inventory_item_object.h"
#include "../xrEngine/Feel_Touch.h"
#include "hudsound.h"
#include "Battery.h"

class CCustomZone;
//�������� ���� ����
struct ZONE_TYPE
{
	//�������� ������ ����������� �����
	float		min_freq;
	float		max_freq;
	//���� ������� ��������� �� ���������� ����
	HUD_SOUND_ITEM	detect_snds;

	shared_str	zone_map_location;
};

//�������� ����, ������������ ����������
struct ZONE_INFO
{
	u32								snd_time;
	//������� ������� ������ �������
	float							cur_freq;
	//particle for night-vision mode
	CParticlesObject*				pParticle;

	ZONE_INFO	();
	~ZONE_INFO	();
};

class CInventoryOwner;

class CDetectorAnomaly :
	public CInventoryItemObject,
	public Feel::Touch
{
	//typedef	CInventoryItemObject	inherited;
	using inherited = CInventoryItemObject;
public:
	CDetectorAnomaly(void);
	~CDetectorAnomaly(void) override;

	BOOL net_Spawn			(CSE_Abstract* DC) override;
	void Load				(LPCSTR section) override;

	void OnH_A_Chield		() override;
	void OnH_B_Independent	(bool just_before_destroy) override;

	void shedule_Update		(u32 dt) override;
	void UpdateCL			() override;

	void feel_touch_new		(CObject* O) override;
	void feel_touch_delete	(CObject* O) override;
	BOOL feel_touch_contact	(CObject* O) override;

			void TurnOn				();
			void TurnOff			();
			bool IsWorking			() {return m_bWorking;}

	void OnMoveToSlot(const SInvItemPlace& prev) override;
	void OnMoveToRuck(const SInvItemPlace& prev) override;

			void UpdateChargeLevel	(void);
	void save				(NET_Packet &output_packet) override;
	void load				(IReader &input_packet) override;
			float GetCurrentChargeLevel(void) const;
			void SetCurrentChargeLevel(float val);
			float GetUnchargeSpeed	(void) const;
			void Recharge			(float val);
			bool IsNecessaryItem	(const shared_str& item_sect, xr_vector<shared_str> item);

	virtual bool				CheckInventoryIconItemSimilarity(CInventoryItem* other) override;

			xr_vector<shared_str> m_SuitableBatteries;

protected:
	void StopAllSounds				();

	bool m_bWorking;

	float m_fRadius;

	//���� ������ ������� �����
	CActor*				m_pCurrentActor;
	CInventoryOwner*	m_pCurrentInvOwner;

	//���������� �� ������������� �����
	DEFINE_MAP(CLASS_ID, ZONE_TYPE, ZONE_TYPE_MAP, ZONE_TYPE_MAP_IT);
	ZONE_TYPE_MAP m_ZoneTypeMap;
	
	//������ ������������ ��� � ���������� � ���
	DEFINE_MAP(CCustomZone*, ZONE_INFO, ZONE_INFO_MAP, ZONE_INFO_MAP_IT);
	ZONE_INFO_MAP m_ZoneInfoMap;
	
	shared_str						m_nightvision_particle;

protected:
	u32					m_ef_detector_type;

public:
	u32			ef_detector_type	() const override;
};