#pragma once

#include "eatable_item_object.h"

class CRepairKit :
	public CEatableItemObject,
	public IMetaClass
{
	DECLARE_METACLASS1(CRepairKit, CEatableItemObject)
	using inherited = CEatableItemObject;

public:
	CRepairKit();
	~CRepairKit() override;
	CRepairKit*		cast_repair_kit() override {return this;}

	void			Load(LPCSTR section) override;
	bool			Useful() const override;

	BOOL			net_Spawn(CSE_Abstract* DC) override;

	bool			UseBy(CEntityAlive* npc) override;
	bool			Empty() override { return m_iPortionsNum == 0; };
	int						m_iUseFor;
	float					m_fRestoreCondition;
	void					ChangeInOutfit();
	void					ChangeInHelmet();
	void					ChangeInSecondHelmet();
	void					ChangeInKnife();
	void					ChangeInWpn1();
	void					ChangeInWpn2();
	void					ChangeInWpn3();
	void					ChangeRepairKitCondition(float val);
	float					GetRepairKitCondition(void) const;
  
	bool					UseAllowed();
  
protected:
	int						m_iPortionsNum;
};