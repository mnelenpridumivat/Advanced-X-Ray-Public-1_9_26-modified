////////////////////////////////////////////////////////////////////////////
//	Module 		: object_actions.h
//	Created 	: 12.03.2004
//  Modified 	: 26.03.2004
//	Author		: Dmitriy Iassenev
//	Description : Object actions
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "action_base.h"

class CAI_Stalker;
class CInventoryItem;
class CFoodItem;
class CWeaponMagazined;
class CWeapon;
//////////////////////////////////////////////////////////////////////////
// CObjectActionBase
//////////////////////////////////////////////////////////////////////////

template <typename _item_type>
class CObjectActionBase : public CActionBase<CAI_Stalker> {
protected:
	typedef CActionBase<CAI_Stalker>					inherited;
	typedef GraphEngineSpace::_solver_condition_type	_condition_type;
	typedef GraphEngineSpace::_solver_value_type		_value_type;

protected:
	_item_type			*m_item;

public:
	IC					CObjectActionBase	(_item_type *item, CAI_Stalker *owner, CPropertyStorage *storage, LPCSTR action_name = "");
	void		initialize			() override;
	IC		void		set_property		(_condition_type condition_id, _value_type value);
	IC		CAI_Stalker &object				() const;
			void		prevent_weapon_state_switch_ugly	( );
			void		stop_hiding_operation_if_any		( ) const;
};

class CGameObject;

typedef CObjectActionBase<CGameObject> CSObjectActionBase;

//////////////////////////////////////////////////////////////////////////
// CObjectActionMember
//////////////////////////////////////////////////////////////////////////

template <typename _item_type>
class CObjectActionMember : public CObjectActionBase<_item_type> {
protected:
	typedef CObjectActionBase<_item_type>			inherited;

protected:
	_condition_type		m_condition_id;
	_value_type			m_value;

public:
	IC					CObjectActionMember	(_item_type *item, CAI_Stalker *owner, CPropertyStorage *storage, _condition_type condition_id, _value_type value, LPCSTR action_name = "");
	void		execute				() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionCommand
//////////////////////////////////////////////////////////////////////////

class CObjectActionCommand : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

protected:
	u32					m_command;

public:
						CObjectActionCommand(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, u32 command, LPCSTR action_name = "");
	void		initialize			() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionShow
//////////////////////////////////////////////////////////////////////////

class CObjectActionShow : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

private:
	CWeapon				*m_weapon;

public:
						CObjectActionShow	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, LPCSTR action_name = "");
	void		initialize			() override;
	void		execute				() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionHide
//////////////////////////////////////////////////////////////////////////

class CObjectActionHide : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

public:
						CObjectActionHide	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, LPCSTR action_name = "");
	void		execute				() override;
	void		finalize			() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionReload
//////////////////////////////////////////////////////////////////////////

class CObjectActionReload : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

protected:
	_condition_type		m_type;

public:
						CObjectActionReload	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, _condition_type type, LPCSTR action_name = "");
	void		initialize			() override;
	void		execute				() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionFire
//////////////////////////////////////////////////////////////////////////

class CObjectActionFire : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

protected:
	_condition_type		m_type;

public:
						CObjectActionFire	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, _condition_type type, LPCSTR action_name = "");
	void		initialize			() override;
	void		execute				() override;
	void		finalize			() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionFireNoReload
//////////////////////////////////////////////////////////////////////////

class CObjectActionFireNoReload : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

protected:
	_condition_type		m_type;
	bool				m_fired;

public:
						CObjectActionFireNoReload	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, _condition_type type, LPCSTR action_name = "");
	void		initialize					() override;
	void		execute						() override;
	void		finalize					() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionStrapping
//////////////////////////////////////////////////////////////////////////

class CObjectActionStrapping : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

private:
	bool				m_callback_removed;

private:
		void xr_stdcall	on_animation_end		();

public:
						CObjectActionStrapping	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, LPCSTR action_name = "");
	~CObjectActionStrapping	() override;
	void		initialize				() override;
	void		execute					() override;
	void		finalize				() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionStrappingToIdle
//////////////////////////////////////////////////////////////////////////

class CObjectActionStrappingToIdle : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

private:
	bool				m_callback_removed;

private:
		void xr_stdcall	on_animation_end		();

public:
						CObjectActionStrappingToIdle	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, LPCSTR action_name = "");
	~CObjectActionStrappingToIdle	() override;
	void		initialize						() override;
	void		execute							() override;
	void		finalize						() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionUnstrapping
//////////////////////////////////////////////////////////////////////////

class CObjectActionUnstrapping : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

private:
	bool				m_callback_removed;

private:
		void xr_stdcall	on_animation_end			();

public:
						CObjectActionUnstrapping	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, LPCSTR action_name = "");
	~CObjectActionUnstrapping	() override;
	void		initialize					() override;
	void		execute						() override;
	void		finalize					() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionUnstrappingToIdle
//////////////////////////////////////////////////////////////////////////

class CObjectActionUnstrappingToIdle : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

private:
	bool				m_callback_removed;

private:
		void xr_stdcall	on_animation_end		();

public:
						CObjectActionUnstrappingToIdle	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, LPCSTR action_name = "");
	~CObjectActionUnstrappingToIdle	() override;
	void		initialize						() override;
	void		execute							() override;
	void		finalize						() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionQueueWait
//////////////////////////////////////////////////////////////////////////

class CObjectActionQueueWait : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

protected:
	_condition_type		m_type;
	CWeaponMagazined	*m_magazined;

public:
						CObjectActionQueueWait	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, _condition_type type, LPCSTR action_name = "");
	void		initialize				() override;
	void		execute					() override;
	void		finalize				() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionSwitch
//////////////////////////////////////////////////////////////////////////

class CObjectActionSwitch : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

protected:
	_condition_type		m_type;

public:
						CObjectActionSwitch	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, _condition_type type, LPCSTR action_name = "");
	void		initialize			() override;
	void		execute				() override;
	void		finalize			() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionDrop
//////////////////////////////////////////////////////////////////////////

class CObjectActionDrop : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

public:
						CObjectActionDrop	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, LPCSTR action_name = "");
	void		initialize			() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionAim
//////////////////////////////////////////////////////////////////////////

class CObjectActionAim : public CObjectActionMember<CInventoryItem> {
protected:
	typedef CObjectActionMember<CInventoryItem> inherited;

private:
	CWeaponMagazined	*m_weapon;

public:
						CObjectActionAim		(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, _condition_type condition_id, _value_type value, LPCSTR action_name = "");
	void		initialize				() override;
	void		execute					() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionIdle
//////////////////////////////////////////////////////////////////////////

class CObjectActionIdle : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

public:
						CObjectActionIdle		(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, LPCSTR action_name = "");
	void		initialize				() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionIdleMissile
//////////////////////////////////////////////////////////////////////////

class CObjectActionIdleMissile : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

public:
						CObjectActionIdleMissile(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, LPCSTR action_name = "");
	void		initialize				() override;
};

//////////////////////////////////////////////////////////////////////////
// CObjectActionThrowMissile
//////////////////////////////////////////////////////////////////////////

class CObjectActionThrowMissile : public CObjectActionBase<CInventoryItem> {
protected:
	typedef CObjectActionBase<CInventoryItem> inherited;

public:
						CObjectActionThrowMissile	(CInventoryItem *item, CAI_Stalker *owner, CPropertyStorage *storage, LPCSTR action_name = "");
	void		initialize				() override;
	void		execute					() override;
};
#include "object_actions_inline.h"