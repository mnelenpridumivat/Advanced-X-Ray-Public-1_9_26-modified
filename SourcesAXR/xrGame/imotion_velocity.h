#pragma once

#include "interactive_motion.h"

class imotion_velocity:
	public interactive_motion
{
	typedef			interactive_motion inherited;
	void	move_update	(  ) override;
	void	collide		(  ) override;
	void	state_end	(  ) override;
	void	state_start (  ) override;
};
