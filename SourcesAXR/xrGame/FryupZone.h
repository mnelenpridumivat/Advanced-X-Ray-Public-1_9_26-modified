#pragma once

#include "script_object.h"

class CFryupZone : public CScriptObject {
	typedef	CScriptObject	inherited;

public:
	CFryupZone	();
	~CFryupZone	() override;

#ifdef DEBUG
	void	OnRender				( ) override;
#endif

};