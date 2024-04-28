#pragma once

#include "../xrEngine/CameraBase.h"

class CCameraLook	: public CCameraBase
{
	typedef CCameraBase inherited;

	Fvector2		lim_zoom;

protected:
	float			dist, prev_d;
public:
					CCameraLook		( CObject* p, u32 flags=0);
	~CCameraLook	( ) override;
	void	Load			(LPCSTR section) override;
	void	Move			( int cmd, float val=0, float factor=1.0f ) override;

	void	OnActivate		( CCameraBase* old_cam ) override;
	void	Update			( Fvector& point, Fvector& noise_dangle ) override;

	float	GetWorldYaw		( ) override { return -yaw;	};
	float	GetWorldPitch	( ) override { return pitch; };

			void	save			(NET_Packet& output_packet) override;
			void	load			(IReader& input_packet) override;
protected:
			void	UpdateDistance	( Fvector& point );
};

class CCameraLook2	: public CCameraLook
{
public:
	static Fvector	m_cam_offset;
protected:
	CObject*		m_locked_enemy;
public:
					CCameraLook2	( CObject* p, u32 flags=0):CCameraLook(p, flags){m_locked_enemy=NULL;};
	~CCameraLook2	() override {}
	void	OnActivate		( CCameraBase* old_cam ) override;
	void	Update			( Fvector& point, Fvector& noise_dangle ) override;
	void	Load			(LPCSTR section) override;
};

class CCameraFixedLook : public CCameraLook
{
	typedef CCameraLook inherited;
public:
					CCameraFixedLook(CObject* p, u32 flags=0) : CCameraLook(p, flags) {};
	~CCameraFixedLook() override {};
	void	Load			(LPCSTR section) override;
	void	Move			(int cmd, float val=0, float factor=1.0f) override;
	void	OnActivate		(CCameraBase* old_cam) override;
	void	Update			(Fvector& point, Fvector& noise_dangle) override;
	void	Set				(float Y, float P, float R) override;
private:
	Fquaternion		m_final_dir;
	Fquaternion		m_current_dir;
};

