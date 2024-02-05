////////////////////////////////////////////////////////////////////////////
//	Module 		: smart_cover_object.h
//	Created 	: 28.08.2007
//  Modified 	: 28.08.2007
//	Author		: Dmitriy Iassenev
//	Description : smart cover object class
////////////////////////////////////////////////////////////////////////////

#ifndef SMART_COVER_OBJECT_H_INCLUDED
#define SMART_COVER_OBJECT_H_INCLUDED

#include "gameobject.h"
#include <boost/noncopyable.hpp>
#include "script_export_space.h"

namespace smart_cover {
	class cover;

class object : 
	public CGameObject,
	private boost::noncopyable
{
private:
	typedef CGameObject	inherited;

private:
	cover const			*m_cover;
	float				m_enter_min_enemy_distance;
	float				m_exit_min_enemy_distance;

public:
	void		Load							(LPCSTR section) override;
	BOOL		feel_touch_on_contact			(CObject *) override { return FALSE; }
	bool		use								(CGameObject* who_use) override { return false; }
	BOOL		net_Spawn						(CSE_Abstract* DC) override;
	void		UpdateCL						() override;
	void		shedule_Update					(u32 dt) override;
	bool		IsVisibleForZones				() override { return false; }
	BOOL		UsedAI_Locations				() override { return true; }
	bool		can_validate_position_on_spawn	() override { return false; }
	bool		use_parent_ai_locations			() const override { return false; }
	bool		is_ai_obstacle					() const override { return false; }
	bool		register_schedule				() const override { return false; }
	void		Center							(Fvector &result) const override;
	float		Radius							() const override;
#ifdef DEBUG
	void		OnRender						() override;
#endif // DEBUG
			bool		inside							(Fvector const &position) const;

	IC		float const&enter_min_enemy_distance		() const;
	IC		float const&exit_min_enemy_distance			() const;
	IC		cover const&cover							() const;

public:
	DECLARE_SCRIPT_REGISTER_FUNCTION
};

} // namespace smart_cover

typedef smart_cover::object	smart_cover__object;
add_to_type_list(smart_cover__object)
#undef script_type_list
#define script_type_list save_type_list(smart_cover__object)

#include "smart_cover_object_inline.h"

#endif // SMART_COVER_OBJECT_H_INCLUDED