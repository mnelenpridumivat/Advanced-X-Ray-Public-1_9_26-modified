#pragma once

#include "inventory_item_object.h"

class CSleepingBag :
	public CInventoryItemObject,
	public IMetaClass
{
	DECLARE_METACLASS1(CSleepingBag, CInventoryItemObject)
	typedef CInventoryItemObject inherited;

public:
	CSleepingBag();
	~CSleepingBag() override;

	void StartSleep();
};