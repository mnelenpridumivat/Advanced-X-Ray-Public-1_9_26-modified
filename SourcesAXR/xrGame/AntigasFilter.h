#pragma once

#include "eatable_item_object.h"

class CAntigasFilter : public CEatableItemObject
{
	using inherited = CEatableItemObject;

public:
	CAntigasFilter();
	~CAntigasFilter() override;
	CAntigasFilter  *cast_filter			() override {return this;}

	void			Load(LPCSTR section) override;
	bool			Useful() const override;

	BOOL			net_Spawn(CSE_Abstract* DC) override;

	bool			UseBy(CEntityAlive* npc) override;
	bool			Empty() override { return m_iPortionsNum == 0; };
	int						m_iUseFor;
	float					m_fCondition;
	void					ChangeInOutfit();
	void					ChangeInHelmet();
	void					ChangeInSecondHelmet();
	void					ChangeFilterCondition(float val);
	void					SetFilterCondition(float val);
	float					GetFilterCondition(void) const;
  
	bool					UseAllowed();
  
protected:
	int						m_iPortionsNum;
};