///////////////////////////////////////////////////////////////
// GrenadeLauncher.h
// GrenadeLauncher - апгрейд оружия поствольный гранатомет
///////////////////////////////////////////////////////////////

#pragma once
#include "inventory_item_object.h"

class CGrenadeLauncher :
	public CInventoryItemObject,
	public IMetaClass
{
	DECLARE_METACLASS1(CGrenadeLauncher, CInventoryItemObject)
private:
	typedef CInventoryItemObject inherited;
public:
	CGrenadeLauncher (void);
	~CGrenadeLauncher(void) override;

	BOOL net_Spawn			(CSE_Abstract* DC) override;
	void Load				(LPCSTR section) override;
	void net_Destroy		() override;

	void OnH_A_Chield		() override;
	void OnH_B_Independent	(bool just_before_destroy) override;

	void UpdateCL			() override;
	void renderable_Render	() override;

	float	GetGrenadeVel() {return m_fGrenadeVel;}

protected:
	//стартовая скорость вылета подствольной гранаты
	float m_fGrenadeVel;
};