#pragma once
#include "game_cl_mp.h"

#include "ui\UIBuyWndShared.h"
#include "ui\UIBuyWndBase.h"


class CUISkinSelectorWnd;
class CUIDialogWnd;
class CUIGameDM;
class CUIPdaWnd;
class CUIInventoryWnd;
class CUIMapDesc;
class CWeaponMagazinedWGrenade;

class game_cl_Deathmatch :public game_cl_mp
{
typedef game_cl_mp inherited;
	CUIGameDM*						m_game_ui;
	shared_str						Actor_Spawn_Effect;
public :
									game_cl_Deathmatch();
~game_cl_Deathmatch() override;
	s32								m_s32FragLimit; //dm,tdm,ah
	s32								m_s32TimeLimit; //dm
	bool							m_bDamageBlockIndicators;
	xr_vector<game_TeamState>		teams;//dm,tdm,ah
	u32								m_u32ForceRespawn;

	u32								m_cl_dwWarmUp_Time;
	string64						WinnerName;

CUIGameCustom*		createGameUI			() override;
void				SetGameUI				(CUIGameCustom*) override;
void				net_import_state		(NET_Packet& P) override;
void				net_import_update		(NET_Packet& P) override;
void				Init					() override;

void				LoadSndMessages			() override;

bool				Is_Rewarding_Allowed	()  const override { return m_cl_dwWarmUp_Time == 0; };
protected:
	struct PresetItem
	{
		u8	SlotID;
		u8	ItemID;
		s16	BigID;
		PresetItem (u8 Slot, u8 Item) { set(Slot, Item); };
		PresetItem (s16 Big) { set(Big); };
		bool	operator ==		(const s16& ID) 
		{ 
			return (BigID) == (ID);
		}
		void		set(s16 Big) { SlotID = static_cast<u8>((Big >> 0x08) & 0x00ff); ItemID = static_cast<u8>(Big & 0x00ff); BigID = Big;}
		void		set(u8 Slot, u8 Item) { SlotID = Slot; ItemID = Item; BigID = (static_cast<s16>(SlotID) << 0x08) | static_cast<s16>(ItemID); };
	};

	DEF_VECTOR						(PRESET_ITEMS, PresetItem);

	PRESET_ITEMS					PresetItemsTeam0;
	PRESET_ITEMS					AdditionalPresetItems;
	PRESET_ITEMS*					pCurPresetItems;
	PRESET_ITEMS					PlayerDefItems;
	IBuyWnd*						pCurBuyMenu;

	CUISkinSelectorWnd*				pCurSkinMenu;
	BOOL							m_bFirstRun;
	BOOL							m_bMenuCalledFromReady;
	BOOL							m_bSkinSelected;
	
	BOOL							m_bBuyEnabled;
	s32								m_iCurrentPlayersMoney;

	u32								m_dwVoteEndTime;

	virtual const shared_str		GetBaseCostSect			() {return "deathmatch_base_cost";}
			void					CheckItem				(PIItem pItem, PRESET_ITEMS* pPresetItems,  BOOL OnlyPreset);

			void					ClearBuyMenu			();
			IBuyWnd*				InitBuyMenu				(const shared_str& BasePriceSection, s16 Team);
			CUISkinSelectorWnd*		InitSkinMenu			(s16 Team = -1);
			void					SetBuyMenuItems			(PRESET_ITEMS* pItems, BOOL OnlyPreset = FALSE);
bool					CanBeReady				() override;
	virtual BOOL					CanCallBuyMenu			();
	virtual BOOL					CanCallSkinMenu			();
	virtual	BOOL					CanCallInventoryMenu	();

			void					Check_Invincible_Players ();

void				shedule_Update			(u32 dt) override;
bool				OnKeyboardPress			(int key) override;
bool				OnKeyboardRelease		(int key) override;

	virtual		const shared_str	GetTeamMenu				(s16 team);
	virtual		void				LoadTeamDefaultPresetItems	(const shared_str& caSection, IBuyWnd* pBuyMenu, PRESET_ITEMS* pPresetItems);
	virtual		void				LoadPlayerDefItems			(char* TeamName, IBuyWnd* pBuyMenu);
	virtual		void				LoadDefItemsForRank			(IBuyWnd* pBuyMenu);
	virtual		void				ChangeItemsCosts			(IBuyWnd* pBuyMenu);
///	virtual		s16					GetBuyMenuItemIndex			(u8 SlotID, u8 ItemID);
				s16					GetBuyMenuItemIndex			(u8 Addons, u8 ItemID);

	virtual		void				ConvertTime2String		(string64* str, u32 Time);
	virtual		int					GetPlayersPlace			(game_PlayerState* ps);

	virtual		void				PlayParticleEffect		(LPCSTR EffName, Fvector& pos);

	virtual		void				ShowBuyMenu				();
	virtual		void				HideBuyMenu				();

public:
s16						ModifyTeam				(s16 Team) override;

char*				getTeamSection			(int Team) override;
	virtual	void					SetCurrentBuyMenu		();
	virtual	void					SetCurrentSkinMenu		();//	{pCurSkinMenu = pSkinMenuTeam0; };

void					OnSpectatorSelect		() override;

void					OnMapInfoAccept			() override;
void				OnSkinMenuBack			() override;
void					OnBuyMenu_Ok			() override;
	virtual	void					OnBuyMenu_DefaultItems	();
void					OnSkinMenu_Ok			() override;
void				OnSkinMenu_Cancel		() override;

void				OnGameMenuRespond_ChangeSkin	(NET_Packet& P) override;

	virtual CUIDialogWnd*			GetBuyWnd				()	{ return (CUIDialogWnd*) pCurBuyMenu; };
	virtual CUIDialogWnd*			GetSkinWnd				()	{ return (CUIDialogWnd*) pCurSkinMenu; };

void				OnVoteStart				(NET_Packet& P) override;
void				OnVoteStop				(NET_Packet& P) override;
void				OnVoteEnd				(NET_Packet& P) override;

void				GetMapEntities			(xr_vector<SZoneMapEntityData>& dst) override;

void				OnRender				() override;
bool				IsEnemy					(game_PlayerState* ps) override;
bool				IsEnemy					(CEntityAlive* ea1, CEntityAlive* ea2) override;

void				OnSpawn					(CObject* pObj) override;
void				OnSwitchPhase			(u32 old_phase, u32 new_phase) override;
void				OnRankChanged			(u8 OldRank) override;
	virtual		void				PlayRankChangesSndMessage ();
void				OnTeamChanged			() override;
void				OnMoneyChanged			() override;

	virtual		void				SetScore				();

void				OnSwitchPhase_InProgress() override;

u8					GetTeamCount			() override { return 1; };

void				OnPlayerFlagsChanged	(game_PlayerState* ps) override;
void				SendPickUpEvent			(u16 ID_who, u16 ID_what) override;

void				OnGameRoundStarted				() override;
void				UpdateMapLocations		() override;
bool				IsPlayerInTeam			(game_PlayerState* ps, ETeam team) override;
	virtual		bool				LocalPlayerCanBuyItem	(shared_str const & name_sect);
LPCSTR				GetGameScore			(string32&	score_dest) override;
void				OnConnected				() override;
private:
	//next methods for alife players in buy menu (artefacthunt)
	typedef buffer_vector<shared_str> aditional_ammo_t;
			void		TryToDefuseAllWeapons		(aditional_ammo_t & dest_ammo);
			void		AdditionalAmmoInserter		(aditional_ammo_t::value_type const & sect_name);
};

IC bool	DM_Compare_Players		(game_PlayerState* p1, game_PlayerState* p2);