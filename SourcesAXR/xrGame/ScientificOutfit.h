///////////////////////////////////////////////////////////////
// ScientificOutfit.h
// ScientificOutfit - защитный костюм ученого
///////////////////////////////////////////////////////////////


#pragma once

#include "customoutfit.h"
#include "script_export_space.h"

class CScientificOutfit:
	public CCustomOutfit,
	public IMetaClass
{
	DECLARE_METACLASS1(CScientificOutfit, CCustomOutfit)
private:
    typedef	CCustomOutfit inherited;
public:
	CScientificOutfit(void);
    ~CScientificOutfit(void) override;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CScientificOutfit)
#undef script_type_list
#define script_type_list save_type_list(CScientificOutfit)
