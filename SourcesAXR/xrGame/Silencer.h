///////////////////////////////////////////////////////////////
// Silencer.h
// Silencer - апгрейд оружия глушитель 
///////////////////////////////////////////////////////////////

#pragma once
#include "inventory_item_object.h"

class CSilencer :
	public CInventoryItemObject,
	public IMetaClass
{
	DECLARE_METACLASS1(CSilencer, CInventoryItemObject)
private:
	typedef CInventoryItemObject inherited;
public:
	CSilencer (void);
	~CSilencer(void) override;

	BOOL net_Spawn			(CSE_Abstract* DC) override;
	void Load				(LPCSTR section) override;
	void net_Destroy		() override;

	void OnH_A_Chield		() override;
	void OnH_B_Independent	(bool just_before_destroy) override;

	void UpdateCL			() override;
	void renderable_Render	() override;

};