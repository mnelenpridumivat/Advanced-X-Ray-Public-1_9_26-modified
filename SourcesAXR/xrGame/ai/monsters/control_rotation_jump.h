#pragma once
#include "control_combase.h"
#include "../../../Include/xrRender/KinematicsAnimated.h"

struct SControlRotationJumpData : public ControlCom::IComData {
	MotionID		anim_stop_ls,anim_run_ls;
	MotionID		anim_stop_rs,anim_run_rs;
	float			turn_angle;

	enum EFlags {	
		eStopAtOnce	= static_cast<u32>(1) << 0,  // stop at once
		eRotateOnce	= static_cast<u32>(1) << 1,	// use only the first stage
	};

	flags32			flags;
};

class CControlRotationJump : public CControl_ComCustom<SControlRotationJumpData> {
	typedef CControl_ComCustom<SControlRotationJumpData> inherited;
	u32				m_time_next_rotation_jump;
	
	float			m_target_velocity;
	float			m_start_velocity;
	float			m_accel;
	float			m_dist;
	float			m_time;

	bool			m_right_side;

	enum EStage {
		eStop,
		eRun, 
		eNone
	} m_stage;

	IKinematicsAnimated	*m_skeleton_animated;

public:
	void	reinit					() override;

	void	on_event				(ControlCom::EEventType, ControlCom::IEventData*) override;
	void	activate				() override;
	void	on_release				() override;
	bool	check_start_conditions	() override;

private:	
			void	build_line_first		();
			void	build_line_second		();
			void	stop_at_once			();
};

