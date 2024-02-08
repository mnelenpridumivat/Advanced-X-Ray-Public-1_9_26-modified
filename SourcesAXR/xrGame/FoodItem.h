#pragma once

#include "eatable_item_object.h"

class CFoodItem:
	public CEatableItemObject,
	public IMetaClass
{
	DECLARE_METACLASS1(CFoodItem, CEatableItemObject)
public:
						CFoodItem			();
						~CFoodItem			() override;

};
