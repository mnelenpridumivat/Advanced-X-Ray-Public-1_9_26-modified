///////////////////////////////////////////////////////////////
// Scope.h
// Scope - апгрейд оружия снайперский прицел
///////////////////////////////////////////////////////////////

#pragma once

#include "inventory_item_object.h"
#include "script_export_space.h"

class CScope :
	public CInventoryItemObject,
	public IMetaClass
{
	DECLARE_METACLASS1(CScope, CInventoryItemObject)
private:
	typedef CInventoryItemObject inherited;
public:
			CScope ();
	~CScope() override;
	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CScope)
#undef script_type_list
#define script_type_list save_type_list(CScope)