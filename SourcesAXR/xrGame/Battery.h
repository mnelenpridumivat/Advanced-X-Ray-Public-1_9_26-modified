#pragma once

#include "eatable_item_object.h"

class CBattery : public CEatableItemObject
{
    using inherited = CEatableItemObject;

public:
							CBattery();
	virtual					~CBattery();

	virtual void			Load(LPCSTR section);
	virtual bool			Useful() const;

	virtual BOOL			net_Spawn(CSE_Abstract* DC);

	virtual	bool			UseBy(CEntityAlive* npc);
	virtual	bool			Empty() { return m_iPortionsNum == 0; };
			int				m_iUseFor;
			float			m_fBatteryChargeLevel;
			float			GetCurrentChargeLevel(void) const;
			void			ChargeTorch();
			void			ChargeArtifactDetector();
			void			ChargeAnomalyDetector();

			DECLARE_SCRIPT_REGISTER_FUNCTION

protected:
			int				m_iPortionsNum;


};

add_to_type_list(CBattery)
#undef script_type_list
#define script_type_list save_type_list(CBattery)