#pragma once

#include "eatable_item_object.h"

class CBattery : public CEatableItemObject
{
    using inherited = CEatableItemObject;

public:
							CBattery();
    ~CBattery() override;

    void			Load(LPCSTR section) override;
    bool			Useful() const override;

    BOOL			net_Spawn(CSE_Abstract* DC) override;

    bool			UseBy(CEntityAlive* npc) override;
    bool			Empty() override { return m_iPortionsNum == 0; };
			int				m_iUseFor;
			float			m_fBatteryChargeLevel;
			float			GetCurrentChargeLevel(void) const;
			void			ChargeTorch();
			void			ChargeArtifactDetector();
			void			ChargeAnomalyDetector();

protected:
			int				m_iPortionsNum;


};