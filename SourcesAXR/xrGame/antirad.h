///////////////////////////////////////////////////////////////
// Antirad.h
// Antirad - таблетки выводящие радиацию
///////////////////////////////////////////////////////////////


#pragma once

#include "eatable_item_object.h"

class CAntirad:
	public CEatableItemObject,
	public IMetaClass
{
	DECLARE_METACLASS1(CAntirad, CEatableItemObject)

public:
				 CAntirad			();
				 ~CAntirad			() override;
};
