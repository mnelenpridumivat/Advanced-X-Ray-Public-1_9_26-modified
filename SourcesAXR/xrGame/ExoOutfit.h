///////////////////////////////////////////////////////////////
// ExoOutfit.h
// ExoOutfit - �������� ������ � ���������
///////////////////////////////////////////////////////////////


#pragma once

#include "customoutfit.h"
#include "script_export_space.h"

class CExoOutfit:
	public CCustomOutfit,
	public IMetaClass
{
	DECLARE_METACLASS1(CExoOutfit, CCustomOutfit)
private:
    typedef	CCustomOutfit inherited;
public:
	CExoOutfit(void);
    ~CExoOutfit(void) override;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CExoOutfit)
#undef script_type_list
#define script_type_list save_type_list(CExoOutfit)

