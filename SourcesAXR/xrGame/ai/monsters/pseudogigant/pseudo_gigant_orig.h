#pragma once
#include "pseudo_gigant.h"
#include "../controlled_entity.h"
#include "../../../../xrServerEntities/script_export_space.h"


class CPseudoGigant_orig : public CPseudoGigant {

	virtual	char*	get_monster_class_name () { return "pseudogigant"; }

	DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CPseudoGigant_orig)
#undef script_type_list
#define script_type_list save_type_list(CPseudoGigant_orig)
