#pragma once
#include "../../../xrEngine/feel_touch.h"
#include "energy_holder.h"

class CBaseMonster;

class CPsyAura : public Feel::Touch, public CEnergyHolder {
	
	typedef CEnergyHolder inherited;

	// �������� ����
	CBaseMonster	*m_object;

	// ������ ����
	float			m_radius;

public:
					CPsyAura				();
	~CPsyAura				() override;
	
			void	init_external			(CBaseMonster *obj) {m_object = obj;}
	BOOL	feel_touch_contact		(CObject* O) override {return FALSE;}
	void	schedule_update			() override;
	virtual void	process_objects_in_aura	() {}

	// �������� ����
			void	set_radius				(float R) {m_radius = R;}
			float	get_radius				(){return m_radius;}

	CBaseMonster	*get_object				(){return m_object;}
};



