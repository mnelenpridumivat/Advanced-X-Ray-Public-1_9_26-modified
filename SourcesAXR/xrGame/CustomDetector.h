#pragma once
#include "inventory_item_object.h"
#include "../xrEngine/feel_touch.h"
#include "hudsound.h"
#include "customzone.h"
#include "artefact.h"
#include "ai_sounds.h"
//#include "ui/ArtefactDetectorUI.h"

#include "Battery.h"

class CCustomZone;
class CInventoryOwner;
class CLAItem;

struct ITEM_TYPE
{
	Fvector2			freq; //min,max
	HUD_SOUND_ITEM		detect_snds;

	shared_str			zone_map_location;
	shared_str			nightvision_particle;
};

//описание зоны, обнаруженной детектором
struct ITEM_INFO
{
	ITEM_TYPE*						curr_ref;
	float							snd_time;
	//текущая частота работы датчика
	float							cur_period;
	//particle for night-vision mode
	CParticlesObject*				pParticle;

									ITEM_INFO		();
									~ITEM_INFO		();
};

template <typename K> 
class CDetectList : public Feel::Touch
{
protected:
	typedef xr_map<shared_str, ITEM_TYPE>	TypesMap;
	typedef typename TypesMap::iterator		TypesMapIt;
	TypesMap								m_TypesMap;
public:
	typedef xr_map<K*,ITEM_INFO>			ItemsMap;
	typedef typename ItemsMap::iterator		ItemsMapIt;
	ItemsMap								m_ItemInfos;

protected:
	void 	feel_touch_new		(CObject* O) override
	{
		K* pK							= smart_cast<K*>(O);
		R_ASSERT						(pK);
		TypesMapIt it					= m_TypesMap.find(O->cNameSect());
		R_ASSERT						(it!=m_TypesMap.end());
		m_ItemInfos[pK].snd_time		= 0.0f;
		m_ItemInfos[pK].curr_ref		= &(it->second);
	}

	void 	feel_touch_delete	(CObject* O) override
	{
		K* pK							= smart_cast<K*>(O);
		R_ASSERT						(pK);
		m_ItemInfos.erase				(pK);
	}
public:
	void			destroy				()
	{
		TypesMapIt it = m_TypesMap.begin();
		for(; it!=m_TypesMap.end(); ++it)
			HUD_SOUND_ITEM::DestroySound(it->second.detect_snds);
	}
	void			clear				()
	{
		m_ItemInfos.clear				();
		Feel::Touch::feel_touch.clear	();
	}
	virtual void	load				(LPCSTR sect, LPCSTR prefix)
	{
		u32 i					= 1;
		string256				temp;
		do{
			xr_sprintf			(temp, "%s_class_%d", prefix, i);
			if(pSettings->line_exist(sect,temp))
			{
				shared_str item_sect	= pSettings->r_string(sect,temp);

				m_TypesMap.insert		(std::make_pair(item_sect, ITEM_TYPE()));
				ITEM_TYPE& item_type	= m_TypesMap[item_sect];

				xr_sprintf				(temp, "%s_freq_%d", prefix, i);
				item_type.freq			= pSettings->r_fvector2(sect,temp);

				xr_sprintf				(temp, "%s_sound_%d_", prefix, i);
				HUD_SOUND_ITEM::LoadSound	(sect, temp	,item_type.detect_snds		, SOUND_TYPE_ITEM);

				++i;
			}else 
				break;

		} while(true);
	}
};

template <typename T>
class CAfList  :public CDetectList<T>
{
protected:
	BOOL 	feel_touch_contact	(CObject* O) override;
public:
					CAfList		():m_af_rank(0){}
	int				m_af_rank;
};

class CUIArtefactDetectorBase;

class CCustomDetector :		public CHudItemObject
{
	typedef	CHudItemObject	inherited;
protected:
	CUIArtefactDetectorBase*			m_ui;
	bool			m_bFastAnimMode;
	bool			m_bNeedActivation;

public:
					CCustomDetector		();
	~CCustomDetector	() override;

	BOOL 	net_Spawn			(CSE_Abstract* DC) override;
	void 	Load				(LPCSTR section) override;

	void 	OnH_A_Chield		() override;
	void 	OnH_B_Independent	(bool just_before_destroy) override;

	void 	shedule_Update		(u32 dt) override;
	void 	UpdateCL			() override;


			bool 	IsWorking			();

	void 	OnMoveToSlot		(const SInvItemPlace& prev) override;
	void 	OnMoveToRuck		(const SInvItemPlace& prev) override;

	void	OnActiveItem		() override;
	void	OnHiddenItem		() override;
	void	OnStateSwitch		(u32 S) override;
	void	OnAnimationEnd		(u32 state) override;
	void	UpdateXForm			() override;

	void			ToggleDetector		(bool bFastMode);
	void			HideDetector		(bool bFastMode);
	void			ShowDetector		(bool bFastMode);
	bool	CheckCompatibility	(CHudItem* itm) override;

	virtual bool				CheckInventoryIconItemSimilarity(CInventoryItem* other) override;

	u32		ef_detector_type	() const override {return 1;};

			void	UpdateChargeLevel	(void);
	void	save				(NET_Packet &output_packet) override;
	void	load				(NET_Packet&input_packet) override;
			float	GetCurrentChargeLevel(void) const;
			void	SetCurrentChargeLevel(float val);
			float	GetAfDetectRadius	() { return m_fAfDetectRadius;};
			float	GetAfVisRadius		() { return m_fAfVisRadius;};
			float	GetUnchargeSpeed	(void) const;
			void	Recharge			(float val);
			bool	IsNecessaryItem		(const shared_str& item_sect, xr_vector<shared_str> item);

			//Light
			bool		m_bLightsEnabled;
			bool		m_bLightsAlways;
			bool		m_bGlowEnabled;
			bool		m_bUseFlashLight;
			bool		m_bVolumetricLights;
			float		m_fVolumetricQuality;
			float		m_fVolumetricDistance;
			float		m_fVolumetricIntensity;
			float		m_fConstVolumetricDistance;
			float		m_fConstVolumetricIntensity;
			float		fBrightness{ 0.25f };
			float		m_fConstLightRange;
			float		m_fLightRange;
			int			m_iLightType;
			shared_str	flash_light_bone;
			xr_vector<shared_str> m_SuitableBatteries;
			u16			m_flash_bone_id;
			u32			m_turn_off_flash_time;
			ref_light	detector_light;
			ref_glow	detector_glow;
			CLAItem*	light_lanim;


	void processing_deactivate() override
			{
				UpdateLights();
				inherited::processing_deactivate();
			}

			void	UpdateLights();
			void	Flash(bool bOn, float fRelPower);

protected:
			bool	CheckCompatibilityInt		(CHudItem* itm, u16* slot_to_activate);
			void 	TurnDetectorInternal		(bool b);
	void 			UpdateNightVisionMode		(bool b_off);
	void			UpdateVisibility			();
	virtual void	UpfateWork					();
	virtual void 	UpdateAf					()				{};
	virtual void 	CreateUI					()				{};

	bool			m_bWorking;
	float			m_fAfVisRadius;
	float			m_fAfDetectRadius;

	CAfList<CObject>m_artefacts;

	bool			install_upgrade_impl(LPCSTR section, bool test) override;
};

class CZoneList : public CDetectList<CCustomZone>
{
protected:
	BOOL	feel_touch_contact( CObject* O ) override;
public:
					CZoneList();
	~CZoneList() override;
}; // class CZoneList
