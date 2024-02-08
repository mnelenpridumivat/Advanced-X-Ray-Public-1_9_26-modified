#pragma once

#include "script_object.h"

class CFryupZone :
	public CScriptObject,
	public IMetaClass
{
	DECLARE_METACLASS1(CFryupZone, CScriptObject)
	typedef	CScriptObject	inherited;

public:
	CFryupZone	();
	~CFryupZone	() override;

#ifdef DEBUG
	void	OnRender				( ) override;
#endif

};