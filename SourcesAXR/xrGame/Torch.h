#pragma once

#include "inventory_item_object.h"
#include "hudsound.h"
#include "script_export_space.h"
#include "Battery.h"

class CLAItem;

class CTorch : public CInventoryItemObject {
private:
    typedef	CInventoryItemObject	inherited;

protected:
	float			fBrightness;
	CLAItem*		lanim;

	u16				guid_bone;
	shared_str		light_trace_bone;

	float			m_delta_h;
	Fvector2		m_prev_hp;
	bool			m_switched_on;
	ref_light		light_render;
	ref_light		light_omni;
	ref_glow		glow_render;
	Fvector			m_focus;
	shared_str		m_light_section;
	Fvector			m_torch_offset;
	Fvector			m_omni_offset;
	float			m_torch_inertion_speed_max;
	float			m_torch_inertion_speed_min;

private:
	inline	bool	can_use_dynamic_lights	();

public:
					CTorch					();
    ~CTorch					() override;

    void	Load					(LPCSTR section) override;
    BOOL	net_Spawn				(CSE_Abstract* DC) override;
    void	net_Destroy				() override;
    void	net_Export				(NET_Packet& P) override;				// export to server
    void	net_Import				(NET_Packet& P) override;				// import from server

    void	OnH_A_Chield			() override;
    void	OnH_B_Independent		(bool just_before_destroy) override;

    void	OnMoveToSlot			(const SInvItemPlace& prev) override;
    void	OnMoveToRuck			(const SInvItemPlace& prev) override;

    void	UpdateCL				() override;

			void	Switch					();
			void	ProcessSwitch			();
			void	Switch					(bool light_on);
			bool	torch_active			() const;
			void	UpdateChargeLevel		(void);
			void	UpdateUseAnim			();
    void	save					(NET_Packet &output_packet) override;
    void	load					(IReader &input_packet) override;
			float	GetCurrentChargeLevel	(void) const;
			void	SetCurrentChargeLevel	(float val);
			bool	IsSwitchedOn			(void) const;
			float	GetUnchargeSpeed		(void) const;
			void	Recharge				(float val);
			bool	IsNecessaryItem			(const shared_str& item_sect, xr_vector<shared_str> item);
			void	ReloadLights			();

    bool	can_be_attached			() const override;

			float	get_range				() const;

	virtual bool				CheckInventoryIconItemSimilarity(CInventoryItem* other) override;

	//CAttachableItem
    void	enable					(bool value) override;

	float			m_fMaxRange;
	float			m_fCurveRange;
	xr_vector<shared_str> m_SuitableBatteries;
	int				m_iActionTiming;
	int				m_iAnimLength;
	bool			m_bActivated;
	bool			m_bSwitched;

    CTorch* cast_torch				() override { return this; }
 
protected:
	HUD_SOUND_COLLECTION_LAYERED m_sounds;
	ref_sound		m_action_anim_sound;

	enum EStats{
		eTorchActive				= (1<<0),
		eNightVisionActive			= (1<<1),
		eAttached					= (1<<2)
	};

public:
    bool			use_parent_ai_locations	() const override
    {
		return				(!H_Parent());
	}

    void	create_physic_shell		() override;
    void	activate_physic_shell	() override;
    void	setup_physic_shell		() override;

    void	afterDetach				() override;
    void	renderable_Render		() override;

    bool	install_upgrade_impl	(LPCSTR section, bool test) override;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CTorch)
#undef script_type_list
#define script_type_list save_type_list(CTorch)
