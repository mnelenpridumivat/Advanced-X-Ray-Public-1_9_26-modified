#pragma once
#include "physicsshellholder.h"
#include "../xrphysics/iclimableobject.h"
class IPHStaticGeomShell;
class CPHCharacter;
struct dContact;
struct SGameMtl;

class CClimableObject: 
public CPhysicsShellHolder,
public IClimableObject
#ifdef DEBUG
,public pureRender
#endif
{
	typedef	CPhysicsShellHolder		inherited;
	//CPHLeaderGeomShell* m_pStaticShell;
	IPHStaticGeomShell* m_pStaticShell;
	Fobb				m_box;
	Fvector				m_axis;
	Fvector				m_side;
	Fvector				m_norm;
	float				m_radius;
	u16					m_material;
public:
					CClimableObject		();
					~CClimableObject	() override;
	void	Load				( LPCSTR section) override;
	BOOL	net_Spawn			( CSE_Abstract* DC) override;
	void	net_Destroy			() override;
	void	shedule_Update		( u32 dt) override;							// Called by sheduler
	void	UpdateCL			( ) override;								// Called each frame, so no need for dt
	void	Center				(Fvector &C) const override;
	float	Radius				() const override;
////////////////////////////////////////////////////////////////////
	IPhysicsShellHolder			*cast_IPhysicsShellHolder	() override { return this; }

#ifdef DEBUG
	void	OnRender			() override;
#endif
protected:
	BOOL	UsedAI_Locations	() override;
public:
			const Fvector&	Axis				()const		{return m_axis;}
	float			DDAxis				(Fvector& dir)const override;

	virtual const Fvector&	Side				()const {return m_side;}
	float			DDSide				(Fvector& dir)const override;

	const Fvector&	Norm				()const override {return m_norm;}
	float			DDNorm				(Fvector &dir)const override;
	bool			BeforeLadder		(CPHCharacter *actor,float tolerance=0.f)const override;
	float			DDLowerP			(CPHCharacter	*actor,Fvector &out_dir)const override;//returns distance and dir to lover point
	float			DDUpperP			(CPHCharacter	*actor,Fvector &out_dir)const override;//returns distance and dir to upper point

			void			DToAxis				(CPHCharacter	*actor,Fvector &dir)const;
	float			DDToAxis			(CPHCharacter	*actor,Fvector &out_dir)const override;//returns distance and dir to ladder axis
			void			POnAxis				(CPHCharacter	*actor,Fvector	&P)const;

	float			AxDistToUpperP		(CPHCharacter	*actor)const override;
	float			AxDistToLowerP		(CPHCharacter	*actor)const override;

			void			DSideToAxis			(CPHCharacter	*actor,Fvector	&dir)const;
			float			DDSideToAxis		(CPHCharacter	*actor,Fvector	&dir)const;

	void			DToPlain			(CPHCharacter	*actor,Fvector	&dist)const override;
	float			DDToPlain			(CPHCharacter	*actor,Fvector	&dir)const override;
			bool			InRange				(CPHCharacter	*actor)const;
	bool			InTouch				(CPHCharacter	*actor)const override;
	u16				Material			()const override {return m_material; }
			void			LowerPoint			(Fvector	&P)const;
			void			UpperPoint			(Fvector	&P)const;
			void			DefineClimbState	(CPHCharacter	*actor)const;
	static 	void			ObjectContactCallback(bool& /**do_colide/**/,bool bo1,dContact& c,SGameMtl * /*material_1*/,SGameMtl * /*material_2*/);

public:
	bool	register_schedule	() const override {return false;}
};
