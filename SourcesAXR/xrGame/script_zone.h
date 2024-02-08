////////////////////////////////////////////////////////////////////////////
//	Module 		: script_zone.h
//	Created 	: 10.10.2003
//  Modified 	: 10.10.2003
//	Author		: Dmitriy Iassenev
//	Description : Script zone object
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "space_restrictor.h"
#include "../xrEngine/feel_touch.h"
#include "script_space_forward.h"
#include "script_export_space.h"

class CScriptGameObject;

class CScriptZone :
	public CSpaceRestrictor,
	public Feel::Touch,
	public IMetaClass
{
	DECLARE_METACLASS2(CScriptZone, CSpaceRestrictor, Feel::Touch)
public:
	typedef	CSpaceRestrictor inherited;

					CScriptZone			();
	~CScriptZone		() override;
	void	reinit				() override;
	BOOL	net_Spawn			(CSE_Abstract* DC) override;
	void	net_Destroy			() override;
	void	net_Relcase			(CObject* O) override;
	void	shedule_Update		(u32 dt) override;
	void	feel_touch_new		(CObject* O) override;
	void	feel_touch_delete	(CObject* O) override;
	BOOL	feel_touch_contact	(CObject* O) override;
			bool	active_contact		(u16 id) const;
	bool	IsVisibleForZones	() override {return false;}
	bool	register_schedule	() const override {return true;}
#ifdef DEBUG
	void	OnRender			() override;
#endif
	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CScriptZone)
#undef script_type_list
#define script_type_list save_type_list(CScriptZone)
