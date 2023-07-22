#pragma once
#include "../pseudogigant/pseudo_gigant.h"

class CAnomalPseudoGigant : public CPseudoGigant {

	typedef		CPseudoGigant						inherited;

public:

	virtual	char* get_monster_class_name() { return "anomalpseudogigant"; }

	// snork jump

	virtual void	jump(const Fvector& position, float factor);
	virtual bool	ability_jump_over_physics() { return true; }


	// poltergeist telekinesis



};

add_to_type_list(CAnomalPseudoGigant)
#undef script_type_list
#define script_type_list save_type_list(CAnomalPseudoGigant)

