#pragma once

#include "control_combase.h"

struct SControlMovementData : public ControlCom::IComData {
	float	velocity_target;
	float	acc;
};

class CControlMovement : public CControl_ComPure<SControlMovementData> {
	typedef CControl_ComPure<SControlMovementData> inherited;

	float		m_velocity_current;
	
public:
	void	reinit			() override;
	void	update_frame	() override;

			float	velocity_current	() {return m_velocity_current;}
			float	velocity_target		() {return m_data.velocity_target;}

			// return object's real velocity
			float	real_velocity	();
};