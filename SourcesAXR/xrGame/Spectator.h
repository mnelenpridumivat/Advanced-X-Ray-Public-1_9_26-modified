#ifndef __SPECTATOR_H__
#define __SPECTATOR_H__

#pragma once

#include "../xrEngine/feel_touch.h"
#include "../xrEngine/iinputreceiver.h"

#include "entity.h"
#include "actor_flags.h"

// refs
class CActor;

class CSpectator: 
	public CGameObject,
	public IInputReceiver
{
private:
	typedef CGameObject		inherited;
	CTimer			m_timer;			//for pause case (in demo mode)
	float			m_fTimeDelta;
protected:
public:
	enum EActorCameras {
		eacFreeFly		= 0,
		eacFirstEye		,
		eacLookAt		,
		eacFreeLook		,
		eacFixedLookAt	,
		eacMaxCam
	};
private:
	// Cameras
	CCameraBase*			cameras[eacMaxCam];
	EActorCameras			cam_active;

	int						look_idx;

	//------------------------------
	void					cam_Set					(EActorCameras style);
	void					cam_Update				(CActor* A=nullptr);

	CActor*					m_pActorToLookAt;
	bool					SelectNextPlayerToLook	(bool const search_next);

	void					FirstEye_ToPlayer		(CObject* pObject);

	static const float		cam_inert_value;
	float					prev_cam_inert_value;
	shared_str				m_last_player_name;
	EActorCameras			m_last_camera;
public:
							CSpectator				( );
	~CSpectator				( ) override;

	void			IR_OnMouseMove			(int x, int y) override;
	void			IR_OnKeyboardPress		(int dik) override;
	void			IR_OnKeyboardRelease	(int dik) override;
	void			IR_OnKeyboardHold		(int dik) override;
	void			shedule_Update			( u32 T ) override;
	void			UpdateCL				( ) override;
	BOOL			net_Spawn				( CSE_Abstract*	DC ) override;
	void			net_Destroy			() override;

	void			Center					(Fvector& C)	const override { C.Set(Position());	}
	float			Radius					()				const override { return EPS;}
//	virtual const Fbox&		BoundingBox				()				const	{ VERIFY2(renderable.visual,*cName()); return renderable.visual->vis.box;									}
	CGameObject*	cast_game_object		() override {return this;}
	IInputReceiver*	cast_input_receiver		() override {return this;}

	void			net_Relcase				(CObject *O) override;
			void			GetSpectatorString		(string1024& pStr);


	void			On_SetEntity			() override;
	void			On_LostEntity			() override;

	inline	EActorCameras	GetActiveCam			() const {return cam_active;};
};

#endif // __SPECTATOR_H__
