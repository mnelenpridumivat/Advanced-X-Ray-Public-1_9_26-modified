////////////////////////////////////////////////////////////////////////////
//	Module 		: xrServer_Object_Base.h
//	Created 	: 19.09.2002
//  Modified 	: 16.07.2004
//	Author		: Oles Shyshkovtsov, Alexander Maksimchuk, Victor Reutskiy and Dmitriy Iassenev
//	Description : Server base object
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "xrServer_Objects_Abstract.h"
#include "object_interfaces.h"
#include "script_value_container.h"
#include "alife_space.h"
#include "../xrCore/client_id.h"

class NET_Packet;
class xrClientData;
class CSE_ALifeGroupAbstract;
class CSE_ALifeSchedulable;
class CSE_ALifeInventoryItem;
class CSE_ALifeTraderAbstract;
class CSE_ALifeObject;
class CSE_ALifeDynamicObject;
class CSE_ALifeItemAmmo;
class CSE_ALifeItemFuel;
class CSE_ALifeItemWeapon;
class CSE_ALifeItemDetector;
class CSE_ALifeMonsterAbstract;
class CSE_ALifeHumanAbstract;
class CSE_ALifeAnomalousZone;
class CSE_ALifeTrader;
class CSE_ALifeCreatureAbstract;
class CSE_ALifeSmartZone;
class CSE_ALifeOnlineOfflineGroup;
class CSE_ALifeItemPDA;
class CSE_ALifeItemFlamethrower;

#pragma warning(push)
#pragma warning(disable:4005)

SERVER_ENTITY_DECLARE_BEGIN(CPureServerObject,IPureServerObject)
	virtual							~CPureServerObject(){}
void					load(IReader	&tFileStream) override;
void					save(IWriter	&tMemoryStream) override;
	virtual void					load(NET_Packet	&tNetPacket);
	virtual void					save(NET_Packet	&tNetPacket);
};
add_to_type_list(CPureServerObject)
#define script_type_list save_type_list(CPureServerObject)

SERVER_ENTITY_DECLARE_BEGIN3(CSE_Abstract,ISE_Abstract,CPureServerObject,CScriptValueContainer)
public:
	enum ESpawnFlags {
		flSpawnEnabled				= static_cast<u32>(1 << 0),
		flSpawnOnSurgeOnly			= static_cast<u32>(1 << 1),
		flSpawnSingleItemOnly		= static_cast<u32>(1 << 2),
		flSpawnIfDestroyedOnly		= static_cast<u32>(1 << 3),
		flSpawnInfiniteCount		= static_cast<u32>(1 << 4),
		flSpawnDestroyOnSpawn		= static_cast<u32>(1 << 5),
	};

private:
	LPSTR							s_name_replace;

public:
	BOOL							net_Ready;
	BOOL							net_Processed;	// Internal flag for connectivity-graph
	
	u16								m_wVersion;
	u16								m_script_version;
	u16								RespawnTime;

	u16								ID;				// internal ID
	u16								ID_Parent;		// internal ParentID, 0xffff means no parent
	u16								ID_Phantom;		// internal PhantomID, 0xffff means no phantom
	xrClientData*					owner;

	// spawn data
	shared_str						s_name;
//.	u8								s_gameid;
	GameTypeChooser					m_gameType;
	u8								s_RP;
	Flags16							s_flags;		// state flags
	xr_vector<u16>					children;

	// update data
	Fvector							o_Position;
	Fvector							o_Angle;
	CLASS_ID						m_tClassID;
	int								m_script_clsid;
	shared_str						m_ini_string;
	CInifile						*m_ini_file;

	// for ALife control
	bool							m_bALifeControl;
	ALife::_SPAWN_ID				m_tSpawnID;

	// ALife spawn params
	// obsolete, just because we hope to uncomment all this stuff
	Flags32							m_spawn_flags;

	//client object custom data serialization
	xr_vector<u8>					client_data;
void					load					(NET_Packet	&tNetPacket) override;

	//////////////////////////////////////////////////////////////////////////
	
									CSE_Abstract			(LPCSTR caSection);
~CSE_Abstract			() override;
	virtual void					OnEvent					(NET_Packet &tNetPacket, u16 type, u32 time, ClientID sender ){};
#ifndef XRGAME_EXPORTS
	virtual void					FillProps				(LPCSTR pref, PropItemVec &items);
	virtual void		__stdcall	FillProp				(LPCSTR pref, PropItemVec &items);
	virtual void 		__stdcall	on_render				(CDUInterface* du, ISE_AbstractLEOwner* owner, bool bSelected, const Fmatrix& parent,int priority, bool strictB2F){} 
	virtual	visual_data*__stdcall	visual_collection		() const { return 0; }
	virtual	u32			__stdcall	visual_collection_size	() const { return 0; }
	virtual	void		__stdcall	set_additional_info		(void* info) {};
#endif // #ifndef XRGAME_EXPORTS
	virtual BOOL					Net_Relevant			(){return FALSE;}; // !!!! WARNING!!!
	//
void		__stdcall	Spawn_Write				(NET_Packet &tNetPacket, BOOL bLocal) override;
BOOL		__stdcall	Spawn_Read				(NET_Packet &tNetPacket) override;
LPCSTR		__stdcall	name					() const override;
LPCSTR		__stdcall	name_replace			() const override;

void		__stdcall	set_name				(LPCSTR s) override
{
		s_name		= s;
	};
void		__stdcall	set_name_replace		(LPCSTR s) override
{xr_free(s_name_replace); s_name_replace = xr_strdup(s);};
Fvector&	__stdcall	position				() override;
Fvector&	__stdcall	angle					() override;
Flags16&	__stdcall	flags					() override;
CSE_Visual* __stdcall	visual					() override;
ISE_Shape*  __stdcall	shape					() override;
CSE_Motion* __stdcall	motion					() override;
bool		__stdcall	validate				() override;
	//

	IC		const Fvector			&Position				() const					{return o_Position;};
	// we need this to prevent virtual inheritance :-(
	virtual CSE_Abstract			*base					();
	virtual const CSE_Abstract		*base					() const;
	virtual CSE_Abstract			*init					();
	virtual bool					match_configuration		() const {return true;}
	// end of the virtual inheritance dependant code
	IC		int						script_clsid			() const					{VERIFY(m_script_clsid >= 0); return (m_script_clsid);}
			CInifile				&spawn_ini				();

// for smart cast
	virtual CSE_ALifeGroupAbstract		*cast_group_abstract		() {return nullptr;}
	virtual CSE_ALifeSchedulable		*cast_schedulable			() {return nullptr;}
	virtual CSE_ALifeInventoryItem		*cast_inventory_item		() {return nullptr;}
	virtual CSE_ALifeTraderAbstract		*cast_trader_abstract		() {return nullptr;}
																			   
	virtual CSE_ALifeObject				*cast_alife_object			() {return nullptr;}
	virtual CSE_ALifeDynamicObject		*cast_alife_dynamic_object	() {return nullptr;}
	virtual CSE_ALifeItemAmmo			*cast_item_ammo				() {return nullptr;}
	virtual CSE_ALifeItemFuel			*cast_item_fuel				() {return nullptr;}
	virtual CSE_ALifeItemWeapon			*cast_item_weapon			() {return nullptr;}
	virtual CSE_ALifeItemFlamethrower	*cast_item_flamethrower		() {return nullptr;}
	virtual CSE_ALifeItemDetector		*cast_item_detector			() {return nullptr;}
	virtual CSE_ALifeMonsterAbstract	*cast_monster_abstract		() {return nullptr;}
	virtual CSE_ALifeHumanAbstract		*cast_human_abstract		() {return nullptr;}
	virtual CSE_ALifeAnomalousZone		*cast_anomalous_zone		() {return nullptr;}
	virtual CSE_ALifeTrader				*cast_trader				() {return nullptr;}
																			   
	virtual CSE_ALifeCreatureAbstract	*cast_creature_abstract		() {return nullptr;}
	virtual CSE_ALifeSmartZone			*cast_smart_zone			() {return nullptr;}
	virtual CSE_ALifeOnlineOfflineGroup	*cast_online_offline_group	() {return nullptr;}
	virtual CSE_ALifeItemPDA			*cast_item_pda				() {return nullptr;}
};
add_to_type_list(CSE_Abstract)
#define script_type_list save_type_list(CSE_Abstract)

#pragma warning(pop)
