#pragma once
#include "MosquitoBald.h"

class CZoneCampfire :public CMosquitoBald
{
	typedef CMosquitoBald	inherited;
protected:
	CParticlesObject*		m_pEnablingParticles;
	CParticlesObject*		m_pDisabledParticles;
	ref_sound				m_sound;
	bool					m_turned_on;
	u32						m_turn_time;

	void		PlayIdleParticles			(bool bIdleLight=true) override;
	void		StopIdleParticles			(bool bIdleLight=true) override;
	BOOL		AlwaysTheCrow				() override;
	void		UpdateWorkload				(u32 dt) override;

public:
							CZoneCampfire				();
	~CZoneCampfire				() override;
	void		Load						(LPCSTR section) override;
	void		GoEnabledState				() override;
	void		GoDisabledState				() override;

				void		turn_on_script				();
				void		turn_off_script				();
				bool		is_on						();
	void		shedule_Update				(u32	dt	) override;
	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CZoneCampfire)
#undef script_type_list
#define script_type_list save_type_list(CZoneCampfire)