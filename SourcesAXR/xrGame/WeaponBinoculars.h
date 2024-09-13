#pragma once

#include "WeaponCustomPistol.h"
#include "script_export_space.h"

class CUIFrameWindow;
class CUIStatic;
class CBinocularsVision;

class CWeaponBinoculars: public CWeaponCustomPistol
{
private:
	typedef CWeaponCustomPistol inherited;
protected:
	bool			m_bVision;
public:
					CWeaponBinoculars	();
	~CWeaponBinoculars	() override;

	void			Load				(LPCSTR section) override;

	void	OnZoomIn			() override;
	void	OnZoomOut			() override;
	void	ZoomInc				() override;
	void	ZoomDec				() override;
	virtual void	GetZoomData			(const float scope_factor, float& delta, float& min_zoom_factor);
	float	CurrentZoomFactor	() override { return m_fRTZoomFactor; }

	void	net_Destroy			() override;
	BOOL	net_Spawn			(CSE_Abstract* DC) override;
	bool			can_kill			() const override;
	void	save				(NET_Packet &output_packet) override;
	void	load				(NET_Packet&input_packet) override;

	bool	Action				(u16 cmd, u32 flags) override;
	void	UpdateCL			() override;
	void	render_item_ui		() override;
	bool	render_item_ui_query() override;
	bool	use_crosshair		()	const override {return false;}
	bool	GetBriefInfo		(II_BriefInfo& info) override;
	void	net_Relcase			(CObject *object) override;
protected:
	CBinocularsVision*					m_binoc_vision;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponBinoculars)
#undef script_type_list
#define script_type_list save_type_list(CWeaponBinoculars)
