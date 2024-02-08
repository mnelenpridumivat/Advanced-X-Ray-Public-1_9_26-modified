////////////////////////////////////////////////////////////////////////////
//	Module 		: space_restrictor.h
//	Created 	: 17.08.2004
//  Modified 	: 17.08.2004
//	Author		: Dmitriy Iassenev
//	Description : Space restrictor
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "gameobject.h"
#include "restriction_space.h"
#include "script_export_space.h"

class CSpaceRestrictor :
	public CGameObject,
	public IMetaClass
{
	DECLARE_METACLASS1(CSpaceRestrictor, CGameObject)
private:
	typedef CGameObject			inherited;

private:
	enum {
		PLANE_COUNT = 6,
	};

private:
	typedef Fplane				CPlanesArray[PLANE_COUNT];

private:
	struct CPlanes {
		CPlanesArray			m_planes;
	};

private:
	typedef xr_vector<Fsphere>	SPHERES;
	typedef xr_vector<CPlanes>	BOXES;

private:
	mutable SPHERES				m_spheres;
	mutable BOXES				m_boxes;
	mutable Fsphere				m_selfbounds;
	mutable bool				m_actuality;

public:
			u8					m_space_restrictor_type;
private:
	IC		void				actual				(bool value) const;
			void				prepare				() const;
			bool				prepared_inside		(const Fsphere &sphere) const;

public:
	IC							CSpaceRestrictor	();
	~CSpaceRestrictor	() override;
	BOOL				net_Spawn			(CSE_Abstract* data) override;
	void				net_Destroy			() override;
			bool				inside				(const Fsphere &sphere) const;
	void				Center				(Fvector &C) const override;
	float				Radius				() const override;
	BOOL				UsedAI_Locations	() override;
	void				spatial_move		() override;
	IC		bool				actual				() const;
	CSpaceRestrictor	*cast_restrictor	() override {return this;}
	bool				register_schedule	() const override {return false;}

	IC RestrictionSpace::ERestrictorTypes restrictor_type() const; 

public:
#ifdef DEBUG
	void				OnRender			() override;
#endif
	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CSpaceRestrictor)
#undef script_type_list
#define script_type_list save_type_list(CSpaceRestrictor)

#include "space_restrictor_inline.h"