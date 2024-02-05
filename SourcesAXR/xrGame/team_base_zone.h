////////////////////////////////////////////////////////////////////////////
//	Module 		: team_base_zone.h
//	Created 	: 27.04.2004
//  Modified 	: 27.04.2004
//	Author		: Dmitriy Iassenev
//	Description : Team base zone object
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "GameObject.h"
#include "../xrEngine/feel_touch.h"

class CTeamBaseZone : public CGameObject, public Feel::Touch {
protected:
	u8		m_Team;
public:
	typedef	CGameObject	inherited;

	CTeamBaseZone		();
	~CTeamBaseZone		() override;
	void	reinit				() override;
	BOOL	net_Spawn			(CSE_Abstract* DC) override;
	void	net_Destroy			() override;

	void	Center				(Fvector &C)	const override;
	float	Radius				() const override;

	void	shedule_Update		(u32 dt) override;
	void	feel_touch_new		(CObject* O) override;
	void	feel_touch_delete	(CObject* O) override;
	BOOL	feel_touch_contact	(CObject* O) override;

	virtual u8		GetZoneTeam			()	{ return m_Team; };
#ifdef DEBUG
	void	OnRender			() override;
#endif
};