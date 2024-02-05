#pragma once
#include "pp_effector_custom.h"

//////////////////////////////////////////////////////////////////////////
// CPPEffectorDistance
//////////////////////////////////////////////////////////////////////////
class CPPEffectorDistance : public CPPEffectorController {
	typedef CPPEffectorController inherited;

	float			m_r_min_perc;		// min_radius (percents [0..1])
	float			m_r_max_perc;		// max_radius (percents [0..1])
	float			m_radius;
	float			m_dist;
public:
	void	load					(LPCSTR section) override;
	IC		void	set_radius				(float r) {m_radius = r;}
	IC		void	set_current_dist		(float dist) {m_dist = dist;}

	bool	check_completion		() override;
	bool	check_start_conditions	() override;
	void	update_factor			() override;

	CPPEffectorControlled *create_effector	() override;
};
