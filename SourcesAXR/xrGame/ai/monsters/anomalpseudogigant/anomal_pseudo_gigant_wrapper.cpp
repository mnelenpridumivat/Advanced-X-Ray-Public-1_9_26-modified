#include "stdafx.h"
#include "pch_script.h"
#include "anomal_pseudo_gigant.h"
#include "../../../sound_player.h"
#include "../burer/burer.h"
#include "../../../GamePersistent.h"
#include "anomal_pseudo_gigant_state_manager.h"
#include "anomal_pseudo_gigant_wrapper.h"


void CAnomalPseudoGigantWrapper::on_shield_on()
{
	luabind::call_member<void>(this, "on_shield_on");
}

void CAnomalPseudoGigantWrapper::on_shield_on_static(CAnomalPseudoGigant* script_binder_object)
{
	script_binder_object->CAnomalPseudoGigant::on_shield_on();
}

void CAnomalPseudoGigantWrapper::on_shield_off()
{
	luabind::call_member<void>(this, "on_shield_off");
}

void CAnomalPseudoGigantWrapper::on_shield_off_static(CAnomalPseudoGigant* script_binder_object)
{
	script_binder_object->CAnomalPseudoGigant::on_shield_off();
}

void CAnomalPseudoGigantWrapper::on_hit()
{
	luabind::call_member<void>(this, "on_hit");
}

void CAnomalPseudoGigantWrapper::on_hit_static(CAnomalPseudoGigant* script_binder_object)
{
	script_binder_object->CAnomalPseudoGigant::on_hit();
}

void CAnomalPseudoGigantWrapper::on_jump()
{
	luabind::call_member<void>(this, "on_jump");
}

void CAnomalPseudoGigantWrapper::on_jump_static(CAnomalPseudoGigant* script_binder_object)
{
	script_binder_object->CAnomalPseudoGigant::on_jump();
}
