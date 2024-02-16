#ifndef __CAMERA_FE_H__
#define __CAMERA_FE_H__

#include "../xrEngine/CameraBase.h"

class CCameraFirstEye :
	public CCameraBase,
	public IMetaClass
{
	DECLARE_METACLASS1(CCameraFirstEye, CCameraBase)
	typedef CCameraBase inherited;
	Fvector			lookat_point;
	bool			lookat_active;
	void			UpdateLookat	();
public:
					CCameraFirstEye	( CObject* p, u32 flags=0);
	~CCameraFirstEye( ) override;

	void	Load			(LPCSTR section) override;
	void	Move			( int cmd, float val=0, float factor=1.0f ) override;

	void	OnActivate		( CCameraBase* old_cam ) override;
	void	Update			( Fvector& point, Fvector& noise_angle ) override;

	float	GetWorldYaw		( ) override { return -yaw;	};
	float	GetWorldPitch	( ) override { return pitch; };
			void	LookAtPoint		(Fvector p){lookat_point=p;lookat_active=true;}

			void	save			(NET_Packet& output_packet) override;
			void	load			(IReader& input_packet) override;
};

#endif // __CAMERALOOK_H__
