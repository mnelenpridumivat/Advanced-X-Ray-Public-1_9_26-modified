#include "stdafx.h"
#include "anomal_pseudo_gigant.h"
#include "../../../sound_player.h"

void CAnomalPseudoGigant::jump(const Fvector& position, float factor)
{
	com_man().script_jump(position, factor);
	sound().play(MonsterSound::eMonsterSoundAggressive);
}
