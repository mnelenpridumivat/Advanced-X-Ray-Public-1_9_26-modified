#pragma once
#include "customzone.h"
#include "script_export_space.h"

class CEmiZone :
	public CCustomZone,
	public IMetaClass
{
	DECLARE_METACLASS1(CEmiZone, CCustomZone)
private:
	typedef		CCustomZone					inherited;

public:
	void	Load(LPCSTR section) override;

	void	enter_Zone(SZoneObjectInfo& io) override;
	void	exit_Zone(SZoneObjectInfo& io) override;

	DECLARE_SCRIPT_REGISTER_FUNCTION

};
add_to_type_list(CEmiZone)
#undef script_type_list
#define script_type_list save_type_list(CEmiZone)

