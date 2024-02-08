#pragma once
#include "customzone.h"
#include "script_export_space.h"

class CRadioactiveZone :
	public CCustomZone,
	public IMetaClass
{
	DECLARE_METACLASS1(CRadioactiveZone, CCustomZone)
private:
	typedef	CCustomZone	inherited;
public:
	CRadioactiveZone(void);
	~CRadioactiveZone(void) override;

	void Load					(LPCSTR section) override;
	void Affect					(SZoneObjectInfo* O) override;
	void feel_touch_new			(CObject* O	) override;
	void UpdateWorkload			(u32	dt	) override;				// related to fast-mode optimizations
	BOOL feel_touch_contact		(CObject* O	) override;
			float nearest_shape_radius	(SZoneObjectInfo* O);

protected:
	bool BlowoutState			() override;
	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CRadioactiveZone)
#undef script_type_list
#define script_type_list save_type_list(CRadioactiveZone)
