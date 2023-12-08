////////////////////////////////////////////////////////////////////////////
//	Module 		: script_game_object_script.cpp
//	Created 	: 25.09.2003
//  Modified 	: 29.06.2004
//	Author		: Dmitriy Iassenev
//	Description : XRay Script game object script export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "script_game_object.h"
#include "game_object_space.h"
#include "script_ini_file.h"
#include "sight_manager_space.h"

using namespace luabind;

extern class_<CScriptGameObject> script_register_game_object1(class_<CScriptGameObject> &&);
extern class_<CScriptGameObject> script_register_game_object2(class_<CScriptGameObject> &&);
extern class_<CScriptGameObject> script_register_game_object_trader(class_<CScriptGameObject> &&);

#pragma optimize("s",on)
void CScriptGameObject::script_register(lua_State *L)
{
	class_<CScriptGameObject>	instance("game_object");

	module(L)
	[
		class_<CSightParams>("CSightParams")
			.enum_("bla-bla")
			[
				value("eSightTypeCurrentDirection",		static_cast<int>(SightManager::eSightTypeCurrentDirection)),
				value("eSightTypePathDirection",		static_cast<int>(SightManager::eSightTypePathDirection)),
				value("eSightTypeDirection",			static_cast<int>(SightManager::eSightTypeDirection)),
				value("eSightTypePosition",				static_cast<int>(SightManager::eSightTypePosition)),
				value("eSightTypeObject",				static_cast<int>(SightManager::eSightTypeObject)),
				value("eSightTypeCover",				static_cast<int>(SightManager::eSightTypeCover)),
				value("eSightTypeSearch",				static_cast<int>(SightManager::eSightTypeSearch)),
				value("eSightTypeLookOver",				static_cast<int>(SightManager::eSightTypeLookOver)),
				value("eSightTypeCoverLookOver",		static_cast<int>(SightManager::eSightTypeCoverLookOver)),
				value("eSightTypeFireObject",			static_cast<int>(SightManager::eSightTypeFireObject)),
				value("eSightTypeFirePosition",			static_cast<int>(SightManager::eSightTypeFirePosition)),
				value("eSightTypeAnimationDirection",	static_cast<int>(SightManager::eSightTypeAnimationDirection)),
				value("eSightTypeDummy",				static_cast<int>(SightManager::eSightTypeDummy))
			]
			.def(							constructor<>())
			.def_readonly("m_object",		&CSightParams::m_object)
			.def_readonly("m_vector",		&CSightParams::m_vector)
			.def_readonly("m_sight_type",	&CSightParams::m_sight_type),
		
		script_register_game_object2(
			script_register_game_object1(
				script_register_game_object_trader(std::move(instance))
			)
		),

		class_<enum_exporter<GameObject::ECallbackType> >("callback")
			.enum_("callback_types")
			[
				value("trade_start",				static_cast<int>(GameObject::eTradeStart)),
				value("trade_stop",					static_cast<int>(GameObject::eTradeStop)),
				value("trade_sell_buy_item",		static_cast<int>(GameObject::eTradeSellBuyItem)),
				value("trade_perform_operation",	static_cast<int>(GameObject::eTradePerformTradeOperation)),
				value("trader_global_anim_request",	static_cast<int>(GameObject::eTraderGlobalAnimationRequest)),
				value("trader_head_anim_request",	static_cast<int>(GameObject::eTraderHeadAnimationRequest)),
				value("trader_sound_end",			static_cast<int>(GameObject::eTraderSoundEnd)),
				value("zone_enter",					static_cast<int>(GameObject::eZoneEnter)),
				value("zone_exit",					static_cast<int>(GameObject::eZoneExit)),
				value("level_border_exit",			static_cast<int>(GameObject::eExitLevelBorder)),
				value("level_border_enter",			static_cast<int>(GameObject::eEnterLevelBorder)),
				value("death",						static_cast<int>(GameObject::eDeath)),
				value("patrol_path_in_point",		static_cast<int>(GameObject::ePatrolPathInPoint)),
				value("inventory_pda",				static_cast<int>(GameObject::eInventoryPda)),
				value("inventory_info",				static_cast<int>(GameObject::eInventoryInfo)),
				value("article_info",				static_cast<int>(GameObject::eArticleInfo)),
				value("use_object",					static_cast<int>(GameObject::eUseObject)),
				value("hit",						static_cast<int>(GameObject::eHit)),
				value("sound",						static_cast<int>(GameObject::eSound)),
				value("action_removed",				static_cast<int>(GameObject::eActionTypeRemoved)),
				value("action_movement",			static_cast<int>(GameObject::eActionTypeMovement)),
				value("action_watch",				static_cast<int>(GameObject::eActionTypeWatch)),
				value("action_animation",			static_cast<int>(GameObject::eActionTypeAnimation)),
				value("action_sound",				static_cast<int>(GameObject::eActionTypeSound)),
				value("action_particle",			static_cast<int>(GameObject::eActionTypeParticle)),
				value("action_object",				static_cast<int>(GameObject::eActionTypeObject)),
				value("actor_sleep",				static_cast<int>(GameObject::eActorSleep)),
				value("helicopter_on_point",		static_cast<int>(GameObject::eHelicopterOnPoint)),
				value("helicopter_on_hit",			static_cast<int>(GameObject::eHelicopterOnHit)),
				value("on_item_take",				static_cast<int>(GameObject::eOnItemTake)),
				value("on_item_drop",				static_cast<int>(GameObject::eOnItemDrop)),
				value("script_animation",			static_cast<int>(GameObject::eScriptAnimation)),
				value("task_state",					static_cast<int>(GameObject::eTaskStateChange)),
				value("take_item_from_box",			static_cast<int>(GameObject::eInvBoxItemTake)),
				value("weapon_no_ammo",				static_cast<int>(GameObject::eWeaponNoAmmoAvailable)),

				// vehicle
				value("on_attach_vehicle",			static_cast<int>(GameObject::eAttachVehicle)),
				value("on_detach_vehicle",			static_cast<int>(GameObject::eDetachVehicle)),
				value("on_use_vehicle",				static_cast<int>(GameObject::eUseVehicle)),

				// anomal pseudogigant
				value("shield_on", static_cast<int>(GameObject::eShieldOn)),
				value("shield_off", static_cast<int>(GameObject::eShieldOff)),
				value("jump", static_cast<int>(GameObject::eJump)),

				// dangerous material touch
				value("dangerous_material_touch", static_cast<int>(GameObject::eDangerousMaterialTouch)),
				
				value("map_location_added",			static_cast<int>(GameObject::eMapLocationAdded))
			],

		def("buy_condition",				static_cast<void (*)(CScriptIniFile*, LPCSTR)>(&::buy_condition)),
		def("buy_condition",				static_cast<void (*)(float, float)>(&::buy_condition)),
		def("sell_condition",				static_cast<void (*)(CScriptIniFile*, LPCSTR)>(&::sell_condition)),
		def("sell_condition",				static_cast<void (*)(float, float)>(&::sell_condition)),
		def("show_condition",				&::show_condition)
	];
}