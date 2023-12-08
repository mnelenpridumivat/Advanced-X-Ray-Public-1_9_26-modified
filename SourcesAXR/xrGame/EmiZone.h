#pragma once
#include "customzone.h"
#include "script_export_space.h"

class CEmiZone :
	public CCustomZone
{
private:
	typedef		CCustomZone					inherited;

public:

	virtual void	Load(LPCSTR section);

	virtual		void	enter_Zone(SZoneObjectInfo& io);
	virtual		void	exit_Zone(SZoneObjectInfo& io);

	DECLARE_SCRIPT_REGISTER_FUNCTION

};
add_to_type_list(CEmiZone)
#undef script_type_list
#define script_type_list save_type_list(CEmiZone)

