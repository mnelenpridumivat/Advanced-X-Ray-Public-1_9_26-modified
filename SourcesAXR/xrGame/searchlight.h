#pragma once

#include "script_object.h"

class CLAItem;

class CProjector: public CScriptObject {
	typedef	CScriptObject		inherited;

	friend void		BoneCallbackX(CBoneInstance *B);
	friend void		BoneCallbackY(CBoneInstance *B);

	float			fBrightness;
	CLAItem*		lanim;
	Fvector			m_pos;
	ref_light		light_render;
	ref_glow		glow_render;

	u16				guid_bone;

	struct SBoneRot {
		float	velocity;
		u16		id;
	} bone_x, bone_y;
	
	struct {
		float	yaw;
		float	pitch;
	} _start, _current, _target;

public:
					CProjector		();
	~CProjector		() override;

	void	Load			( LPCSTR section) override;
	BOOL	net_Spawn		( CSE_Abstract* DC) override;
	void	shedule_Update	( u32 dt) override;							// Called by sheduler
	void	UpdateCL		( ) override;								// Called each frame, so no need for dt
	void	renderable_Render( ) override;

	BOOL	UsedAI_Locations() override;

	bool	bfAssignWatch(CScriptEntityAction	*tpEntityAction) override;
	bool	bfAssignObject(CScriptEntityAction *tpEntityAction) override;

			Fvector GetCurrentDirection	();
private:
			void	TurnOn			();
			void	TurnOff			();
	
	// Rotation routines
	static void	_BCL	BoneCallbackX(CBoneInstance *B);
	static void	_BCL	BoneCallbackY(CBoneInstance *B);

	void			SetTarget		(const Fvector &target_pos);
	
};


