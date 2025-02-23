#pragma once

#include "UIDialogWnd.h"
#include "UIWndCallback.h"
#include "../../XrServerEntitiesCS/inventory_space.h"
#include "UIHint.h"
#include "script_game_object.h" //Alundaio

class CUICharacterInfo;
class CUIDragDropListEx;
class CUICellItem;
class CUIDragItem;
class ui_actor_state_wnd;
class CUIItemInfo;
class CUIFrameLineWnd;
class CUIStatic;
class CUI3tButtonEx;
class CInventoryOwner;
class CInventoryBox;
class CCar;
class CUIInventoryUpgradeWnd;
class UIInvUpgradeInfo;
class CUIMessageBoxEx;
class CUIPropertiesBox;
class CTrade;

namespace inventory { namespace upgrade {
	class Upgrade;
} } // namespace upgrade, inventory

enum EDDListType{
		iInvalid,
		iActorSlot,
		iActorBag,
		iActorBelt,

		iActorTrade,
		iPartnerTradeBag,
		iPartnerTrade,
		iDeadBodyBag,
		iTrashSlot,
		iListTypeMax
};

enum EMenuMode{
		mmUndefined,
		mmInventory,
		mmTrade,
		mmUpgrade,
		mmDeadBodySearch,
		mmCarTrunk,
};

class CUIActorMenu :	public CUIDialogWnd, 
						public CUIWndCallback
{
	typedef CUIDialogWnd		inherited;
	typedef inventory::upgrade::Upgrade 	Upgrade_type;

protected:
	enum eActorMenuSndAction{	eSndOpen	=0,
								eSndClose,
								eItemToSlot,
								eItemToBelt,
								eItemToRuck,
								eProperties,
								eDropItem,
								eAttachAddon,
								eDetachAddon,
								eItemUse,
								eSndMax};

	EMenuMode					m_currMenuMode;
	ref_sound					sounds					[eSndMax];
	void						PlaySnd					(eActorMenuSndAction a);

	UIHint*						m_hint_wnd;
	CUIItemInfo*				m_ItemInfo;
	CUICellItem*				m_InfoCellItem;
	u32							m_InfoCellItem_timer;
	CUICellItem*				m_pCurrentCellItem;
	CUICellItem*				m_pCurrentConsumable;
	CUICellItem*				m_upgrade_selected;
	CUIPropertiesBox*			m_UIPropertiesBox;

	ui_actor_state_wnd*			m_ActorStateInfo;
	CUICharacterInfo*			m_ActorCharacterInfo;
	CUICharacterInfo*			m_PartnerCharacterInfo;

	CUIDragDropListEx*			m_pInventoryBeltList;
	CUIDragDropListEx*			m_pInventoryPistolList;
	CUIDragDropListEx*			m_pInventoryAutomaticList;
	CUIDragDropListEx*			m_pInventoryOutfitList;
	CUIDragDropListEx*			m_pInventoryDetectorList;
	CUIDragDropListEx*			m_pInventoryBagList;

	CUIDragDropListEx*			m_pTradeActorBagList;
	CUIDragDropListEx*			m_pTradeActorList;
	CUIDragDropListEx*			m_pTradePartnerBagList;
	CUIDragDropListEx*			m_pTradePartnerList;
	CUIDragDropListEx*			m_pDeadBodyBagList;
	CUIDragDropListEx*			m_pTrashList;
	CUIDragDropListEx*			m_pInventoryKnifeList;
	CUIDragDropListEx*			m_pInventoryBinocularList;
	CUIDragDropListEx*			m_pInventoryTorchList;
	CUIDragDropListEx*			m_pInventoryBackpackList;
	CUIDragDropListEx*			m_pInventoryDosimeterList;
	CUIDragDropListEx*			m_pInventoryPantsList;
	CUIDragDropListEx*			m_pInventoryPdaList;

	xr_vector<CUIStatic*>		m_belt_list_over;
	
	CUIStatic*					m_PistolSlotHighlight;
	CUIStatic*					m_RiffleSlotHighlight;
	CUIStatic*					m_OutfitSlotHighlight;
	CUIStatic*					m_DetectorSlotHighlight;
	xr_vector<CUIStatic*>		m_ArtefactSlotsHighlight;
	CUIStatic*					m_KnifeSlotHighlight;
	CUIStatic*					m_BinocularSlotHighlight;
	CUIStatic*					m_TorchSlotHighlight;
	CUIStatic*					m_BackpackSlotHighlight;
	CUIStatic*					m_DosimeterSlotHighlight;
	CUIStatic*					m_PantsSlotHighlight;
	CUIStatic*					m_PdaSlotHighlight;

	CUIInventoryUpgradeWnd*		m_pUpgradeWnd;
	
	CUIStatic*					m_LeftBackground;

	UIInvUpgradeInfo*			m_upgrade_info;
	CUIMessageBoxEx*			m_message_box_yes_no;
	CUIMessageBoxEx*			m_message_box_ok;

	CInventoryOwner*			m_pActorInvOwner;
	CInventoryOwner*			m_pPartnerInvOwner;
	CInventoryBox*				m_pInvBox;
	CCar*						m_pCar;

	CUIStatic*					m_ActorMoney;
	CUIStatic*					m_PartnerMoney;

	// bottom ---------------------------------
	CUIStatic*					m_ActorBottomInfo;
	CUIStatic*					m_ActorWeight;
	CUIStatic*					m_ActorWeightMax;
	
	CUIStatic*					m_PartnerBottomInfo;
	CUIStatic*					m_PartnerWeight;
	float						m_PartnerWeight_end_x;
//*	CUIStatic*					m_PartnerWeightMax;

	CUIStatic*					m_ActorInvCapacityInfo;
	CUIStatic*					m_ActorInvFullness;
	CUIStatic*					m_ActorInvCapacity;

	// delimiter ------------------------------
	CUIStatic*					m_LeftDelimiter;
	CUIStatic*					m_PartnerTradeCaption;
	CUIStatic*					m_PartnerTradePrice;
	CUIStatic*					m_PartnerTradeWeightMax;

	CUIStatic*					m_RightDelimiter;
	CUIStatic*					m_ActorTradeCaption;
	CUIStatic*					m_ActorTradePrice;
	CUIStatic*					m_ActorTradeWeightMax;

	CTrade*						m_actor_trade;
	CTrade*						m_partner_trade;

	CUI3tButtonEx*				m_trade_button;
	CUI3tButtonEx*				m_takeall_button;
	CUI3tButtonEx*				m_exit_button;
	CUIStatic*					m_clock_value;

	u32							m_last_time;
	bool						m_repair_mode;
	bool						m_item_info_view;
	bool						m_highlight_clear;
	u32							m_trade_partner_inventory_state;
	bool						m_bNeedMoveAfsToBag;
public:
	void						SetMenuMode					(EMenuMode mode);
	EMenuMode					GetMenuMode					() {return m_currMenuMode;};
	void						SetActor					(CInventoryOwner* io);
	void						SetPartner					(CInventoryOwner* io);
	CInventoryOwner*			GetPartner					() {return m_pPartnerInvOwner;};
	void						SetInvBox					(CInventoryBox* box);
	CInventoryBox*				GetInvBox					() {return m_pInvBox;};
	void						SetCarTrunk					(CCar* pCar);
	void						SetSimpleHintText			(LPCSTR text);

private:
	void						PropertiesBoxForSlots		(PIItem item, bool& b_show);
	void						PropertiesBoxForWeapon		(CUICellItem* cell_item, PIItem item, bool& b_show);
	void						PropertiesBoxForAddon		(PIItem item, bool& b_show);
	void						PropertiesBoxForUsing		(PIItem item, bool& b_show);
	void						PropertiesBoxForPlaying		(PIItem item, bool& b_show);
	void						PropertiesBoxForDrop		(CUICellItem* cell_item, PIItem item, bool& b_show);
	void						PropertiesBoxForRepair		(PIItem item, bool& b_show);

private:
	void						clear_highlight_lists		();
	void						set_highlight_item			(CUICellItem* cell_item);
	void						highlight_item_slot			(CUICellItem* cell_item);
	void						highlight_armament			(PIItem item, CUIDragDropListEx* ddlist);
	void						highlight_ammo_for_weapon	(PIItem weapon_item, CUIDragDropListEx* ddlist);
	void						highlight_weapons_for_ammo	(PIItem ammo_item, CUIDragDropListEx* ddlist);
	bool						highlight_addons_for_weapon	(PIItem weapon_item, CUICellItem* ci);
	void						highlight_weapons_for_addon	(PIItem addon_item, CUIDragDropListEx* ddlist);

public:
	void						Construct					();
	void						InitCallbacks				();

	void						InitCellForSlot				(u32 slot_idx);
	void						InitInventoryContents		(CUIDragDropListEx* pBagList);
	void						ClearAllLists				();
	void						BindDragDropListEvents		(CUIDragDropListEx* lst);
	
	EDDListType					GetListType					(CUIDragDropListEx* l);
	CUIDragDropListEx*			GetListByType				(EDDListType t);
	CUIDragDropListEx*			GetSlotList					(u32 slot_idx);
	
	xr_vector<EDDListType>		m_allowed_drops				[iListTypeMax];
	bool						AllowItemDrops				(EDDListType from, EDDListType to);

	bool		xr_stdcall		OnItemDrop					(CUICellItem* itm);
	bool		xr_stdcall		OnItemStartDrag				(CUICellItem* itm);
	bool		xr_stdcall		OnItemDbClick				(CUICellItem* itm);
	bool		xr_stdcall		OnItemSelected				(CUICellItem* itm);
	bool		xr_stdcall		OnItemRButtonClick			(CUICellItem* itm);
	bool		xr_stdcall		OnItemMButtonClick			(CUICellItem* itm);
	bool		xr_stdcall		OnItemFocusReceive			(CUICellItem* itm);
	bool		xr_stdcall		OnItemFocusLost				(CUICellItem* itm);
	bool		xr_stdcall		OnItemFocusedUpdate			(CUICellItem* itm);
	void		xr_stdcall		OnDragItemOnTrash			(CUIDragItem* item, bool b_receive);
	bool						OnItemDropped				(PIItem itm, CUIDragDropListEx* new_owner, CUIDragDropListEx* old_owner);

	void						ResetMode					();
	void						InitInventoryMode			();
	void						DeInitInventoryMode			();
	void						InitTradeMode				();
	void						DeInitTradeMode				();
	void						InitUpgradeMode				();
	void						DeInitUpgradeMode			();
	void						InitDeadBodySearchMode		();
	void						DeInitDeadBodySearchMode	();

	void						CurModeToScript				();
	void						RepairEffect_CurItem		();

public:
	void						SetCurrentItem				(CUICellItem* itm);
	CUICellItem*				CurrentItem					();
	PIItem						CurrentIItem				();

protected:
	void						InfoCurItem					(CUICellItem* cell_item); //on update item

	void						ActivatePropertiesBox		();
	void						TryHidePropertiesBox		();
	void		xr_stdcall		ProcessPropertiesBoxClicked	(CUIWindow* w, void* d);
	
	void						CheckDistance				();
	void						UpdateItemsPlace			();

	void						SetupUpgradeItem			();
	void						UpdateUpgradeItem			();
	void						TrySetCurUpgrade			();
	void						UpdateButtonsLayout			();

	// inventory
	bool						ToSlot						(CUICellItem* itm, bool force_place);
	bool						ToBag						(CUICellItem* itm, bool b_use_cursor_pos);
	bool						ToBelt						(CUICellItem* itm, bool b_use_cursor_pos);
	bool						TryUseItem					(CUICellItem* cell_itm);

	void						UpdateActorMP				();
	void						UpdateOutfit				();
	void						MoveArtefactsToBag			();
	bool						TryActiveSlot				(CUICellItem* itm);
	void		xr_stdcall		TryRepairItem				(CUIWindow* w, void* d);
	bool						CanUpgradeItem				(PIItem item);

	bool						ToActorTrade				(CUICellItem* itm, bool b_use_cursor_pos);
	bool						ToPartnerTrade				(CUICellItem* itm, bool b_use_cursor_pos);
	bool						ToPartnerTradeBag			(CUICellItem* itm, bool b_use_cursor_pos);
	bool						ToDeadBodyBag				(CUICellItem* itm, bool b_use_cursor_pos);

	void						AttachAddon					(PIItem item_to_upgrade);
	void						DetachAddon					(LPCSTR addon_name, PIItem itm = NULL);

	void						SendEvent_Item2Slot			(PIItem	pItem, u16 parent);
	void						SendEvent_Item2Belt			(PIItem	pItem, u16 parent);
	void						SendEvent_Item2Ruck			(PIItem	pItem, u16 parent);
	void						SendEvent_Item_Drop			(PIItem	pItem, u16 parent);
	void						SendEvent_Item_Eat			(PIItem	pItem, u16 parent);
	void						SendEvent_ActivateSlot		(u32 slot, u16 recipient);
	void						DropAllCurrentItem			();
	void						OnPressUserKey				();

	// trade
	void						InitPartnerInventoryContents();
	void						ColorizeItem				(CUICellItem* itm, bool colorize);
	float						CalcItemsWeight				(CUIDragDropListEx* pList);
	u32							CalcItemsPrice				(CUIDragDropListEx* pList, CTrade* pTrade, bool bBuying);
	void						UpdatePrices				();
	bool						CanMoveToPartner			(PIItem pItem);
	void						TransferItems				(CUIDragDropListEx* pSellList, CUIDragDropListEx* pBuyList, CTrade* pTrade, bool bBuying);

public:
								CUIActorMenu				();
	virtual						~CUIActorMenu				();

	virtual bool				StopAnyMove					();
	virtual void				SendMessage					(CUIWindow* pWnd, s16 msg, void* pData = NULL);
	virtual void				Draw						();
	virtual void				Update						();
	virtual void				Show						();
	virtual void				Hide						();

	virtual bool				OnKeyboardAction					(int dik, EUIMessages keyboard_action);
	virtual bool				OnMouseAction						(float x, float y, EUIMessages mouse_action);

	void						CallMessageBoxYesNo			(LPCSTR text);
	void						CallMessageBoxOK			(LPCSTR text);
	void		xr_stdcall		OnMesBoxYes					(CUIWindow*, void*);
	void		xr_stdcall		OnMesBoxNo					(CUIWindow*, void*);

	void						OnInventoryAction			(PIItem pItem, u16 action_type);
	void						ShowRepairButton			(bool status);
	bool						SetInfoCurUpgrade			(Upgrade_type* upgrade_type, CInventoryItem* inv_item );
	void						SeparateUpgradeItem			();
	PIItem						get_upgrade_item			();
	bool						DropAllItemsFromRuck		(bool quest_force = false); //debug func

	void						UpdateActor					();
	void						UpdatePartnerBag			();
	void						UpdateDeadBodyBag			();

	void		xr_stdcall		OnBtnPerformTrade			(CUIWindow* w, void* d);
	void		xr_stdcall		OnBtnExitClicked			(CUIWindow* w, void* d);
	void		xr_stdcall		TakeAllFromPartner			(CUIWindow* w, void* d);
	void						TakeAllFromInventoryBox		();
	CUICellItem*				GetCurrentConsumable		() { return m_pCurrentConsumable; };
	void						SetCurrentConsumable		(CUICellItem* ci) { m_pCurrentConsumable = ci; };
	void						RefreshConsumableCells		();

	CScriptGameObject*			GetCurrentItemAsGameObject	();

	void						RefreshCurrentItemCell		();

	IC	UIHint*					get_hint_wnd				() { return m_hint_wnd; }

	DECLARE_SCRIPT_REGISTER_FUNCTION
}; // class CUIActorMenu

add_to_type_list(CUIActorMenu)
#undef script_type_list
#define script_type_list save_type_list(CUIActorMenu)
