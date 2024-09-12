////////////////////////////////////////////////////////////////////////////
//	Module 		: script_sound_type_script.cpp
//	Created 	: 28.06.2004
//  Modified 	: 28.06.2004
//	Author		: Dmitriy Iassenev
//	Description : Script sound type script export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "script_sound_type.h"
#include "ai_sounds.h"

using namespace luabind;

#pragma optimize("s",on)
void CScriptSoundType::script_register(lua_State *L)
{
	module(L)
	[
		class_<enum_exporter<ESoundTypes> >("snd_type")
			.enum_("sound_types")
			[
				value("no_sound",				static_cast<int>(SOUND_TYPE_NO_SOUND)),
				value("weapon",					static_cast<int>(SOUND_TYPE_WEAPON)),
				value("item",					static_cast<int>(SOUND_TYPE_ITEM)),
				value("monster",				static_cast<int>(SOUND_TYPE_MONSTER)),
				value("anomaly",				static_cast<int>(SOUND_TYPE_ANOMALY)),
				value("world",					static_cast<int>(SOUND_TYPE_WORLD)),
				value("pick_up",				static_cast<int>(SOUND_TYPE_PICKING_UP)),
				value("drop",					static_cast<int>(SOUND_TYPE_DROPPING)),
				value("hide",					static_cast<int>(SOUND_TYPE_HIDING)),
				value("take",					static_cast<int>(SOUND_TYPE_TAKING)),
				value("use",					static_cast<int>(SOUND_TYPE_USING)),
				value("shoot",					static_cast<int>(SOUND_TYPE_SHOOTING)),
				value("empty",					static_cast<int>(SOUND_TYPE_EMPTY_CLICKING)),
				value("bullet_hit",				static_cast<int>(SOUND_TYPE_BULLET_HIT)),
				value("reload",					static_cast<int>(SOUND_TYPE_RECHARGING)),
				value("die",					static_cast<int>(SOUND_TYPE_DYING)),
				value("injure",					static_cast<int>(SOUND_TYPE_INJURING)),
				value("step",					static_cast<int>(SOUND_TYPE_STEP)),
				value("talk",					static_cast<int>(SOUND_TYPE_TALKING)),
				value("attack",					static_cast<int>(SOUND_TYPE_ATTACKING)),
				value("eat",					static_cast<int>(SOUND_TYPE_EATING)),
				value("idle",					static_cast<int>(SOUND_TYPE_IDLE)),
				value("object_break",			static_cast<int>(SOUND_TYPE_OBJECT_BREAKING)),
				value("object_collide",			static_cast<int>(SOUND_TYPE_OBJECT_COLLIDING)),
				value("object_explode",			static_cast<int>(SOUND_TYPE_OBJECT_EXPLODING)),
				value("ambient",				static_cast<int>(SOUND_TYPE_AMBIENT)),
				value("item_pick_up",			static_cast<int>(SOUND_TYPE_ITEM_PICKING_UP)),
				value("item_drop",				static_cast<int>(SOUND_TYPE_ITEM_DROPPING)),
				value("item_hide",				static_cast<int>(SOUND_TYPE_ITEM_HIDING)),
				value("item_take",				static_cast<int>(SOUND_TYPE_ITEM_TAKING)),
				value("item_use",				static_cast<int>(SOUND_TYPE_ITEM_USING)),
				value("weapon_shoot",			static_cast<int>(SOUND_TYPE_WEAPON_SHOOTING)),
				value("weapon_empty",			static_cast<int>(SOUND_TYPE_WEAPON_EMPTY_CLICKING)),
				value("weapon_bullet_hit",		static_cast<int>(SOUND_TYPE_WEAPON_BULLET_HIT)),
				value("weapon_reload",			static_cast<int>(SOUND_TYPE_WEAPON_RECHARGING)),
				value("monster_die",			static_cast<int>(SOUND_TYPE_MONSTER_DYING)),
				value("monster_injure",			static_cast<int>(SOUND_TYPE_MONSTER_INJURING)),
				value("monster_step",			static_cast<int>(SOUND_TYPE_MONSTER_STEP)),
				value("monster_talk",			static_cast<int>(SOUND_TYPE_MONSTER_TALKING)),
				value("monster_attack",			static_cast<int>(SOUND_TYPE_MONSTER_ATTACKING)),
				value("monster_eat",			static_cast<int>(SOUND_TYPE_MONSTER_EATING)),
				value("anomaly_idle",			static_cast<int>(SOUND_TYPE_ANOMALY_IDLE)),
				value("world_object_break",		static_cast<int>(SOUND_TYPE_WORLD_OBJECT_BREAKING)),
				value("world_object_collide",	static_cast<int>(SOUND_TYPE_WORLD_OBJECT_COLLIDING)),
				value("world_object_explode",	static_cast<int>(SOUND_TYPE_WORLD_OBJECT_EXPLODING)),
				value("world_ambient",			static_cast<int>(SOUND_TYPE_WORLD_AMBIENT))
			]
	];
}

SCRIPT_EXPORT1(CScriptSoundType);