///////////////////////////////////////////////////////////////
// Medkit.h
// Medkit - аптечка, повышающая здоровье
///////////////////////////////////////////////////////////////


#pragma once

#include "eatable_item_object.h"

class CMedkit:
	public CEatableItemObject,
	public IMetaClass
{
	DECLARE_METACLASS1(CMedkit, CEatableItemObject)

public:
				 CMedkit			();
				 ~CMedkit			() override;
};
