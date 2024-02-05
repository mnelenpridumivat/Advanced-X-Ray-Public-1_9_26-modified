#pragma once
#include "UIDragDropListEx.h"
#include "../../xrServerEntities/inventory_space.h"
class CInventoryOwner;

class CUIDragDropReferenceList : public CUIDragDropListEx
{
private:
	typedef CUIDragDropListEx inherited;
	typedef xr_vector<CUIStatic*> ITEMS_REFERENCES_VEC;
	typedef ITEMS_REFERENCES_VEC::iterator ITEMS_REFERENCES_VEC_IT;
	ITEMS_REFERENCES_VEC m_references;
public:
	CUIDragDropReferenceList();
	~CUIDragDropReferenceList() override;
	void SetItem(CUICellItem* itm) override;
	void SetItem(CUICellItem* itm, Fvector2 abs_pos) override;
	void SetItem(CUICellItem* itm, Ivector2 cell_pos) override;
	CUICellItem* RemoveItem(CUICellItem* itm, bool force_root) override;

	void Initialize();
	CUICellContainer* GetContainer() {return m_container;};
	void LoadItemTexture(LPCSTR section, Ivector2 cell_pos);
	void ReloadReferences(CInventoryOwner* pActor);

	void __stdcall	OnItemDBClick		(CUIWindow* w, void* pData) override;
	void __stdcall	OnItemDrop			(CUIWindow* w, void* pData) override;
};