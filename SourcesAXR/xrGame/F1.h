#pragma once

#include "grenade.h"
#include "script_export_space.h"

class CF1 :
	public CGrenade,
	public IMetaClass
{
	DECLARE_METACLASS1(CF1, CGrenade)
	typedef CGrenade inherited;
public:
	CF1(void);
	~CF1(void) override;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CF1)
#undef script_type_list
#define script_type_list save_type_list(CF1)
