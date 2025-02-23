////////////////////////////////////////////////////////////////////////////
//	Module 		: UIActorMenu_script.cpp
//	Created 	: 18.04.2008
//	Author		: Evgeniy Sokolov
//	Description : UI ActorMenu script implementation
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "UIActorMenu.h"
#include "UIPdaWnd.h"
#include "../actor.h"
#include "../inventory_item.h"
#include "UICellItem.h"
#include "../ai_space.h"
#include "../../xrServerEntities/script_engine.h"
#include "UITabControl.h"
#include "UIMainIngameWnd.h"
#include "UIActorMenu.h"
#include "UIZoneMap.h"
#include "UIMotionIcon.h"
#include "UIHudStatesWnd.h"
#include "UIGameCustom.h"
#include "InventoryBox.h"

using namespace luabind;

void CUIActorMenu::TryRepairItem(CUIWindow* w, void* d)
{
	PIItem item = get_upgrade_item();
	if ( !item )
	{
		return;
	}
	if ( item->GetCondition() > 0.99f )
	{
		return;
	}
	LPCSTR item_name = item->m_section_id.c_str();
	LPCSTR partner = m_pPartnerInvOwner->CharacterInfo().Profile().c_str();

	luabind::functor<bool> funct;
	R_ASSERT2(
		ai().script_engine().functor( "inventory_upgrades.can_repair_item", funct ),
		make_string( "Failed to get functor <inventory_upgrades.can_repair_item>, item = %s", item_name )
		);
	bool can_repair = funct( item_name, item->GetCondition(), partner );

	luabind::functor<LPCSTR> funct2;
	R_ASSERT2(
		ai().script_engine().functor( "inventory_upgrades.question_repair_item", funct2 ),
		make_string( "Failed to get functor <inventory_upgrades.question_repair_item>, item = %s", item_name )
		);
	LPCSTR question = funct2( item_name, item->GetCondition(), can_repair, partner );

	if(can_repair)
	{
		m_repair_mode = true;
		CallMessageBoxYesNo( question );
	}
	else
	{
		CallMessageBoxOK( question );
	}
}

void CUIActorMenu::RepairEffect_CurItem()
{
	PIItem item = CurrentIItem();
	if ( !item )
	{
		return;	
	}
	LPCSTR item_name = item->m_section_id.c_str();

	luabind::functor<void>	funct;
	R_ASSERT( ai().script_engine().functor( "inventory_upgrades.effect_repair_item", funct ) );
	funct( item_name, item->GetCondition() );

	item->SetCondition( 1.0f );
	UpdateConditionProgressBars();
	SeparateUpgradeItem();
	CUICellItem* itm = CurrentItem();
	if(itm)
		itm->UpdateCellItemProgressBars();

}

bool CUIActorMenu::CanUpgradeItem( PIItem item )
{
	VERIFY( item && m_pPartnerInvOwner );
	LPCSTR item_name = item->m_section_id.c_str();
	LPCSTR partner = m_pPartnerInvOwner->CharacterInfo().Profile().c_str();
		
	luabind::functor<bool> funct;
	R_ASSERT2(
		ai().script_engine().functor( "inventory_upgrades.can_upgrade_item", funct ),
		make_string( "Failed to get functor <inventory_upgrades.can_upgrade_item>, item = %s, mechanic = %s", item_name, partner )
		);

	return funct( item_name, partner );
}

void CUIActorMenu::CurModeToScript()
{
	int mode = (int)m_currMenuMode;
	luabind::functor<void>	funct;
	R_ASSERT( ai().script_engine().functor( "actor_menu.actor_menu_mode", funct ) );
	funct( mode );
}

template<class T>
class enum_dummy {};

void CUIActorMenu::script_register(lua_State* L)
{
		module(L)
		[
			class_<enum_dummy<EDDListType>>("EDDListType")
				.enum_("EDDListType")
				[
					value("iActorBag",				static_cast<int>(EDDListType::iActorBag)),
					value("iActorBelt",				static_cast<int>(EDDListType::iActorBelt)),
					value("iActorSlot",				static_cast<int>(EDDListType::iActorSlot)),
					value("iActorTrade",			static_cast<int>(EDDListType::iActorTrade)),
					value("iDeadBodyBag",			static_cast<int>(EDDListType::iDeadBodyBag)),
					value("iInvalid",				static_cast<int>(EDDListType::iInvalid)),
					value("iPartnerTrade",			static_cast<int>(EDDListType::iPartnerTrade)),
					value("iPartnerTradeBag",		static_cast<int>(EDDListType::iPartnerTradeBag)),
					value("iQuickSlot",				static_cast<int>(EDDListType::iQuickSlot)),
					value("iTrashSlot",				static_cast<int>(EDDListType::iTrashSlot))
				],

			class_<CUIActorMenu, CUIDialogWnd>("CUIActorMenu")
				.def(constructor<>())
				.def("get_drag_item",				&CUIActorMenu::GetCurrentItemAsGameObject)
				.def("highlight_section_in_slot",	&CUIActorMenu::HighlightSectionInSlot)
				.def("highlight_for_each_in_slot",	&CUIActorMenu::HighlightForEachInSlot)
				.def("refresh_current_cell_item",	&CUIActorMenu::RefreshCurrentItemCell)
				.def("IsShown",						&CUIActorMenu::IsShown)
				.def("ShowDialog",					&CUIActorMenu::ShowDialog)
				.def("HideDialog",					&CUIActorMenu::HideDialog),

 			class_< CUIMainIngameWnd, CUIWindow>("CUIMainIngameWnd")
				.def(constructor<>())
				.def_readonly("UIStaticDiskIO",		&CUIMainIngameWnd::UIStaticDiskIO)
				.def_readonly("UIStaticQuickHelp",	&CUIMainIngameWnd::UIStaticQuickHelp)
				.def_readonly("UIMotionIcon",		&CUIMainIngameWnd::UIMotionIcon)
				.def_readonly("UIZoneMap",			&CUIMainIngameWnd::UIZoneMap)
				.def_readonly("m_ui_hud_states",	&CUIMainIngameWnd::m_ui_hud_states)
				.def_readonly("m_ind_bleeding",		&CUIMainIngameWnd::m_ind_bleeding)
				.def_readonly("m_ind_radiation",	&CUIMainIngameWnd::m_ind_radiation)
				.def_readonly("m_ind_starvation",	&CUIMainIngameWnd::m_ind_starvation)
				.def_readonly("m_ind_thirst",		&CUIMainIngameWnd::m_ind_thirst)
				.def_readonly("m_ind_intoxication", &CUIMainIngameWnd::m_ind_intoxication)
				.def_readonly("m_ind_sleepeness",	&CUIMainIngameWnd::m_ind_sleepeness)
				.def_readonly("m_ind_alcoholism",	&CUIMainIngameWnd::m_ind_alcoholism)
				.def_readonly("m_ind_narcotism",	&CUIMainIngameWnd::m_ind_narcotism)
				.def_readonly("m_ind_psy_health",	&CUIMainIngameWnd::m_ind_psy_health)
				.def_readonly("m_ind_filter_dirty", &CUIMainIngameWnd::m_ind_filter_dirty)
				.def_readonly("m_ind_weapon_broken", &CUIMainIngameWnd::m_ind_weapon_broken)
				.def_readonly("m_ind_helmet_broken", &CUIMainIngameWnd::m_ind_helmet_broken)
				.def_readonly("m_ind_outfit_broken", &CUIMainIngameWnd::m_ind_outfit_broken)
				.def_readonly("m_ind_overweight",	&CUIMainIngameWnd::m_ind_overweight)
				.def_readonly("m_ind_boost_psy",	&CUIMainIngameWnd::m_ind_boost_psy)
				.def_readonly("m_ind_boost_radia",	&CUIMainIngameWnd::m_ind_boost_radia)
				.def_readonly("m_ind_boost_chem",	&CUIMainIngameWnd::m_ind_boost_chem)
				.def_readonly("m_ind_boost_wound",	&CUIMainIngameWnd::m_ind_boost_wound)
				.def_readonly("m_ind_boost_weight", &CUIMainIngameWnd::m_ind_boost_weight)
				.def_readonly("m_ind_boost_health", &CUIMainIngameWnd::m_ind_boost_health)
				.def_readonly("m_ind_boost_power",	&CUIMainIngameWnd::m_ind_boost_power)
				.def_readonly("m_ind_boost_rad",	&CUIMainIngameWnd::m_ind_boost_rad)
				.def_readonly("m_ind_boost_satiety",	&CUIMainIngameWnd::m_ind_boost_satiety)
				.def_readonly("m_ind_boost_thirst",		&CUIMainIngameWnd::m_ind_boost_thirst)
				.def_readonly("m_ind_boost_psy_health", &CUIMainIngameWnd::m_ind_boost_psy_health)
				.def_readonly("m_ind_boost_intoxication", &CUIMainIngameWnd::m_ind_boost_intoxication)
				.def_readonly("m_ind_boost_sleepeness", &CUIMainIngameWnd::m_ind_boost_sleepeness)
				.def_readonly("m_ind_boost_alcoholism", &CUIMainIngameWnd::m_ind_boost_alcoholism)
				.def_readonly("m_ind_boost_hangover",	&CUIMainIngameWnd::m_ind_boost_hangover)
				.def_readonly("m_ind_boost_narcotism",	&CUIMainIngameWnd::m_ind_boost_narcotism)
				.def_readonly("m_ind_boost_withdrawal", &CUIMainIngameWnd::m_ind_boost_withdrawal),
 			class_< CUIZoneMap >("CUIZoneMap")
				.def(constructor<>())
				.def_readonly("visible",			&CUIZoneMap::visible)
				.def("MapFrame",					&CUIZoneMap::MapFrame)
				.def("Background",					&CUIZoneMap::Background),
 			class_< CUIMotionIcon, CUIWindow>("CUIMotionIcon")
				.def(constructor<>()),
 			class_< CUIHudStatesWnd, CUIWindow>("CUIHudStatesWnd")
				.def(constructor<>())
				.def_readonly("m_back",								&CUIHudStatesWnd::m_back)
				.def_readonly("m_ui_weapon_cur_ammo",				&CUIHudStatesWnd::m_ui_weapon_cur_ammo)
				.def_readonly("m_ui_weapon_fmj_ammo",				&CUIHudStatesWnd::m_ui_weapon_fmj_ammo)
				.def_readonly("m_ui_weapon_ap_ammo",				&CUIHudStatesWnd::m_ui_weapon_ap_ammo)
				.def_readonly("m_fire_mode",						&CUIHudStatesWnd::m_fire_mode)
				.def_readonly("m_ui_grenade",						&CUIHudStatesWnd::m_ui_grenade)
				.def_readonly("m_ui_weapon_icon",					&CUIHudStatesWnd::m_ui_weapon_icon)
				.def_readonly("m_ui_health_bar",					&CUIHudStatesWnd::m_ui_health_bar)
				.def_readonly("m_ui_stamina_bar",					&CUIHudStatesWnd::m_ui_stamina_bar)
				.def_readonly("m_radia_damage",						&CUIHudStatesWnd::m_radia_damage)
		];

		module(L, "ActorMenu")
		[
			def("get_pda_menu",						+[]() { return &CurrentGameUI()->PdaMenu(); }),
			def("get_actor_menu",					+[]() { return &CurrentGameUI()->ActorMenu(); }),
			def("get_menu_mode",					+[]() { return CurrentGameUI()->ActorMenu().GetMenuMode(); }),
			def("get_maingame",						+[]() { return CurrentGameUI()->UIMainIngameWnd; })
		];
};

SCRIPT_EXPORT2(CUIActorMenu, CUIWindow);

void CUIPdaWnd::script_register(lua_State* L)
{
		using namespace luabind;

		module(L)
		[
			class_<CUIPdaWnd, CUIDialogWnd>("CUIPdaWnd")
				.def(constructor<>())
				.def("IsShown",						&CUIPdaWnd::IsShown)
				.def("ShowDialog",					&CUIPdaWnd::ShowDialog)
				.def("HideDialog",					&CUIPdaWnd::HideDialog)
				.def("SetActiveSubdialog",			&CUIPdaWnd::SetActiveSubdialog_script)
				.def("GetActiveSection",			&CUIPdaWnd::GetActiveSection)
				.def("GetTabControl",				&CUIPdaWnd::GetTabControl)
		];
};

SCRIPT_EXPORT2(CUIPdaWnd, CUIWindow);