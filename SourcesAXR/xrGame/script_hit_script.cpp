////////////////////////////////////////////////////////////////////////////
//	Module 		: script_hit_script.cpp
//	Created 	: 06.02.2004
//  Modified 	: 24.06.2004
//	Author		: Dmitriy Iassenev
//	Description : XRay Script hit class script export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "script_hit.h"
#include "script_game_object.h"

using namespace luabind;

#pragma optimize("s",on)
void CScriptHit::script_register(lua_State *L)
{
	module(L)
	[
		class_<CScriptHit>("hit")
			.enum_("hit_type")
			[
				value("burn",					static_cast<int>(ALife::eHitTypeBurn)),
				value("shock",					static_cast<int>(ALife::eHitTypeShock)),
				value("strike",					static_cast<int>(ALife::eHitTypeStrike)),
				value("wound",					static_cast<int>(ALife::eHitTypeWound)),
				value("radiation",				static_cast<int>(ALife::eHitTypeRadiation)),
				value("telepatic",				static_cast<int>(ALife::eHitTypeTelepatic)),
				value("chemical_burn",			static_cast<int>(ALife::eHitTypeChemicalBurn)),
				value("explosion",				static_cast<int>(ALife::eHitTypeExplosion)),
				value("fire_wound",				static_cast<int>(ALife::eHitTypeFireWound)),
				value("light_burn",				static_cast<int>(ALife::eHitTypeLightBurn)),
				value("dummy",					static_cast<int>(ALife::eHitTypeMax))
			]
			.def_readwrite("power",				&CScriptHit::m_fPower)
			.def_readwrite("direction",			&CScriptHit::m_tDirection)
			.def_readwrite("draftsman",			&CScriptHit::m_tpDraftsman)
			.def_readwrite("impulse",			&CScriptHit::m_fImpulse)
			.def_readwrite("type",				&CScriptHit::m_tHitType)
			.def(								constructor<>())
			.def(								constructor<const CScriptHit *>())
			.def("bone",						&CScriptHit::set_bone_name)
	];
}

SCRIPT_EXPORT(CScriptHit);
