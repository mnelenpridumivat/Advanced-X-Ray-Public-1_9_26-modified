#pragma once
#include "anomal_pseudo_gigant.h"

class CAnomalPseudoGigantWrapper : public CAnomalPseudoGigant, public luabind::wrap_base {

public:
	//CAnomalPseudoGigantWrapper(CScriptGameObject* object);
	//virtual				~CAnomalPseudoGigantWrapper();

public:

	virtual void on_shield_on();
	virtual void on_shield_on_static(CAnomalPseudoGigant* script_binder_object);
	virtual void on_shield_off();
	virtual void on_shield_off_static(CAnomalPseudoGigant* script_binder_object);
	virtual void on_hit();
	virtual void on_hit_static(CAnomalPseudoGigant* script_binder_object);
	virtual void on_jump();
	virtual void on_jump_static(CAnomalPseudoGigant* script_binder_object);

};