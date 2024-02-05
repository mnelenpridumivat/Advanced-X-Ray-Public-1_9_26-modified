#pragma once

#include "inventory_item_object.h"

class CMPPlayersBag :
	public	CInventoryItemObject
{
public:
					CMPPlayersBag(void);
					~CMPPlayersBag(void) override;
					bool	NeedToDestroyObject	() const override;

					void OnEvent(NET_Packet& P, u16 type) override;
protected:
private:
};