#pragma once

#include "../control_path_builder.h"

class CPoltergeist;
class CCustomMonster;

class CPoltergeisMovementManager : public CControlPathBuilder {
	typedef CControlPathBuilder inherited;

	CPoltergeist	*m_monster;

public:
					CPoltergeisMovementManager	(CPoltergeist *monster) : inherited((CCustomMonster*)monster), m_monster(monster) {}
	~CPoltergeisMovementManager	() override {}

	void	move_along_path				(CPHMovementControl *movement_control, Fvector &dest_position, float time_delta) override;

			Fvector	CalculateRealPosition		();
};

