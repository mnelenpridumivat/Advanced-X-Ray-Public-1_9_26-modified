#pragma once
#include "UICellItem.h"
#include "../Weapon.h"


class CUIInventoryCellItem :public CUICellItem
{
	typedef  CUICellItem	inherited;
public:
								CUIInventoryCellItem		(CInventoryItem* itm);
	bool			EqualTo						(CUICellItem* itm) override;
	void			UpdateItemText				() override;
				CUIDragItem*	CreateDragItem				() override;
	bool			IsHelper					() override;
	void			SetIsHelper					(bool is_helper) override;
				bool			IsHelperOrHasHelperChild	();
				void			Update						() override;
				CInventoryItem* object						() {return static_cast<CInventoryItem*>(m_pData);}
};

class CUIAmmoCellItem :public CUIInventoryCellItem
{
	typedef  CUIInventoryCellItem	inherited;
protected:
	void			 UpdateItemText				() override;
public:
								 CUIAmmoCellItem			(CWeaponAmmo* itm);

				u32				 CalculateAmmoCount			();
	bool			 EqualTo						(CUICellItem* itm) override;
	CUIDragItem*	 CreateDragItem				() override;
				CWeaponAmmo*	 object						() {return static_cast<CWeaponAmmo*>(m_pData);}
};

class CUIWeaponCellItem :public CUIInventoryCellItem
{
	typedef  CUIInventoryCellItem	inherited;
public:
	enum eAddonType{	eSilencer=0, eScope, eLauncher, eLaser, eTorch, eMaxAddon};
protected:
	CUIStatic*					m_addons					[eMaxAddon];
	Fvector2					m_addon_offset				[eMaxAddon];
	void						CreateIcon					(eAddonType);
	void						DestroyIcon					(eAddonType);
	void						RefreshOffset				();
	CUIStatic*					GetIcon						(eAddonType);
	void						InitAddon					(CUIStatic* s, LPCSTR section, Fvector2 offset, bool use_heading, bool is_dragging = false, bool is_scope = false, bool is_silencer = false, bool is_gl = false);
	bool						is_scope					();
	bool						is_silencer					();
	bool						is_launcher					();
	bool						is_laser					();
	bool						is_torch					();
public:
								CUIWeaponCellItem			(CWeapon* itm);
	~CUIWeaponCellItem			() override;
	void			Update						() override;
	void			Draw						() override;
	void			SetTextureColor				(u32 color) override;

				CWeapon*		object						() {return static_cast<CWeapon*>(m_pData);}
	void			OnAfterChild				(CUIDragDropListEx* parent_list) override;
	CUIDragItem*	CreateDragItem				() override;
	bool			EqualTo						(CUICellItem* itm) override;
	CUIStatic*					get_addon_static			(u32 idx)				{return m_addons[idx];}
};

class CBuyItemCustomDrawCell :public ICustomDrawCellItem
{
	CGameFont*			m_pFont;
	string16			m_string;
public:
						CBuyItemCustomDrawCell	(LPCSTR str, CGameFont* pFont);
	void		OnDraw					(CUICellItem* cell) override;

};
