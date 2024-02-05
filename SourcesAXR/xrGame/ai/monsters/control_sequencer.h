#pragma once

#include "control_combase.h"
#include "../../../Include/xrRender/KinematicsAnimated.h"

struct SAnimationSequencerData : public ControlCom::IComData {
	xr_vector<MotionID>	motions;
};
	
class CAnimationSequencer : public CControl_ComCustom<SAnimationSequencerData> {
	u32						m_index;
public:
	void	reset_data				() override;
	void	on_capture				() override;
	void	on_release				() override;
	void	on_event				(ControlCom::EEventType, ControlCom::IEventData*) override;

	bool	check_start_conditions	() override;

	void	activate				() override;
private:
			void	play_selected			();
};

