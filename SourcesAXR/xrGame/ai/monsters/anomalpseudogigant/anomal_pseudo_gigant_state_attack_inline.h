#pragma once

//#include "burer_state_attack_tele.h"
//#include "burer_state_attack_gravi.h"
#include "anomal_pseudo_gigant_state_attack_shield.h"
//#include "burer_state_attack_melee.h"
#include "../states/state_look_point.h"
#include "../states/state_move_to_restrictor.h"
#include "../states/monster_state_attack_run.h"
#include "../states/monster_state_attack_run_attack.h"
#include "../states/monster_state_attack_melee.h"
#include "../states/monster_state_attack_on_run.h"
#include "../states/monster_state_find_enemy.h"
#include "../states/monster_state_steal.h"
#include "../states/monster_state_attack_camp.h"
//#include "burer_state_attack_run_around.h"
//#include "burer_state_attack_antiaim.h"

namespace anomal_pseudogigant
{
	float const health_delta				=	0.2f;

} // namespace detail

template <typename Object>
CStateAnomalPseudoGigantAttack<Object>::CStateAnomalPseudoGigantAttack(Object *obj) : inherited(obj)
{
	add_state(eStateAttack_Run, xr_new<CStateMonsterAttackRun<Object> >(obj));
	add_state(eStateAttack_Melee, xr_new<CStateMonsterAttackMelee<Object> >(obj));
	add_state(eStateAttack_RunAttack, xr_new<CStateMonsterAttackRunAttack<Object> >(obj));
	add_state(eStateAttack_Attack_On_Run, xr_new<CStateMonsterAttackOnRun<Object> >(obj));
	add_state(eStateAttack_RunAway, xr_new<CStateMonsterHideFromPoint<Object> >(obj));
	add_state(eStateAttack_FindEnemy, xr_new<CStateMonsterFindEnemy<Object> >(obj));
	add_state(eStateAttack_Steal, xr_new<CStateMonsterSteal<Object> >(obj));
	add_state(eStateAttackCamp, xr_new<CStateMonsterAttackCamp<Object> >(obj));
	add_state(eStateAttack_MoveToHomePoint, xr_new<CStateMonsterAttackMoveToHomePoint<Object> >(obj));

	add_state(eStateBurerAttack_Shield, xr_new<CStateAnomalPseudoGigantShield<Object> >(obj));
	//add_state(eStateAttack_AttackHidden, xr_new<CStateAnomalPseudoGigantAttackHidden<CAnomalPseudoGigant> >(obj));

	/*add_state(eStateBurerAttack_Tele, xr_new<CStateBurerAttackTele<Object> >(obj));
	add_state(eStateBurerAttack_Gravi,		xr_new<CStateBurerAttackGravi<Object> >		(obj));
	add_state(eStateBurerAttack_Melee,		xr_new<CStateBurerAttackMelee<Object> >		(obj));
	add_state(eStateBurerAttack_FaceEnemy,	xr_new<CStateMonsterLookToPoint<Object> >	(obj));
	add_state(eStateBurerAttack_RunAround,	xr_new<CStateBurerAttackRunAround<Object> >	(obj));
	add_state(eStateBurerAttack_Shield,		xr_new<CStateBurerShield<Object> >			(obj));
	add_state(eStateBurerAttack_AntiAim,	xr_new<CStateBurerAntiAim<Object> >			(obj));
	add_state(eStateAttack_Run,				xr_new<CStateMonsterAttackRun<Object> >		(obj));
	add_state(eStateCustomMoveToRestrictor,	xr_new<CStateMonsterMoveToRestrictor<Object> >(obj));

	m_allow_anti_aim						=	false;
	m_wait_state_end						=	false;
	m_lost_delta_health						=	false;*/
}

template <typename Object>
void CStateAnomalPseudoGigantAttack<Object>::initialize()
{
	inherited::initialize						();

	m_last_health							=	object->conditions().GetHealth();
	m_lost_delta_health						=	false;
	m_next_runaway_allowed_tick				=	0;
	m_allow_anti_aim						=	false;
	m_wait_state_end						=	false;

	
// 	CMonsterSquad *squad					=	monster_squad().get_squad(object);
// 	if ( squad )
// 	{
// 		squad->InformSquadAboutEnemy			(object->EnemyMan.get_enemy());
// 	}
}

template <typename Object>
void   CStateAnomalPseudoGigantAttack<Object>::execute ()
{
	CEntityAlive*		enemy				=	const_cast<CEntityAlive*>( object->EnemyMan.get_enemy() );

	// Notify squad	
	CMonsterSquad *squad					=	monster_squad().get_squad(object);
	if (squad) {
		SMemberGoal								goal;
		goal.type							=	MG_AttackEnemy;
		goal.entity							=	enemy;
		squad->UpdateGoal						(object, goal);
	}

	if ( object->anim().has_override_animation() )
	{
		object->anim().clear_override_animation();
	}

	if ( object->conditions().GetHealth() <= m_last_health - anomal_pseudogigant::health_delta )
	{
		m_last_health						=	object->conditions().GetHealth();
		m_lost_delta_health					=	true;
	}

	if ( m_wait_state_end )
	{
		if ( get_state_current()->check_completion() )
		{
			m_wait_state_end				=	false;
		}
		else
		{
			get_state_current()->execute		();
			prev_substate					=	current_substate;
			return;
		}
	}

	//m_allow_anti_aim						=	true;
	//bool const	anti_aim_ready				=	get_state(eStateBurerAttack_AntiAim)->check_start_conditions();
	//m_allow_anti_aim						=	false;

	//bool const	gravi_ready					=	get_state(eStateBurerAttack_Gravi)->check_start_conditions();
	bool const	shield_ready				=	get_state(eStateBurerAttack_Shield)->check_start_conditions();
	//bool const	tele_ready					=	get_state(eStateBurerAttack_Tele)->check_start_conditions();

	bool		selected_state				=	true;

	//if ( gravi_ready )
	//{
	//	select_state							(eStateBurerAttack_Gravi);
	//}
	/*else*/ 
	if (m_lost_delta_health && shield_ready)
	{
		m_lost_delta_health					=	false;
		select_state							(eStateBurerAttack_Shield);
	}
	//else if ( anti_aim_ready )
	//{
	//	select_state							(eStateBurerAttack_AntiAim);
	//}
	//else if ( tele_ready && current_substate != eStateBurerAttack_RunAround )
	//{
	//	select_state							(eStateBurerAttack_Tele);
	//}
	else
	{
		selected_state						=	false;
	}

	if ( selected_state )
	{
		get_state_current()->execute			();
		m_wait_state_end					=	true;
		prev_substate						=	current_substate;
		return;
	}

	Fvector	const		enemy_pos			=	enemy->Position();
	Fvector	const		self_pos			=	object->Position();
	Fvector	const		self2enemy			=	enemy_pos - self_pos;
	float	const		self2enemy_dist		=	magnitude(self2enemy);
	
	//bool	const		in_runaway_range	=	self2enemy_dist < object->m_runaway_distance;
	//bool	const		in_normal_range		=	self2enemy_dist < object->m_normal_distance;

	if ( current_substate == eStateCustomMoveToRestrictor )
	{
		if ( !get_state_current()->check_completion() )
		{
			get_state_current()->execute		();
			prev_substate					=	current_substate;
			return;
		}
	}

	if ( get_state(eStateCustomMoveToRestrictor)->check_start_conditions() ) 
	{
		select_state							(eStateCustomMoveToRestrictor);
		get_state_current()->execute			();
		prev_substate						=	current_substate;
		return;
	}

	/*if (current_substate == eStateBurerAttack_RunAround)
	{
		if ( get_state_current()->check_completion() )
		{
			if ( in_runaway_range )
			{
				m_next_runaway_allowed_tick	=	current_time() + 5000;
			}
		}
		else
		{
			get_state_current()->execute		();
			prev_substate					=	current_substate;
			return;
		}
	}*/

	/*if (m_lost_delta_health ||
		(in_runaway_range && current_time() > m_next_runaway_allowed_tick) )
	{
		m_lost_delta_health					=	false;
		select_state							(eStateBurerAttack_RunAround);		
	}
	else if ( !in_normal_range )
	{
		select_state							(eStateAttack_Run);
	}
	else */
	{
		Fvector	const	self2enemy			=	enemy_pos - self_pos;
		bool  	const 	good_aiming			=	angle_between_vectors(self2enemy, object->Direction()) 
												< deg2rad(20.f);

		select_state							(eStateBurerAttack_FaceEnemy);

		if ( !good_aiming )
		{
			bool const rotate_right			=	object->control().direction().is_from_right(enemy_pos);
			object->anim().set_override_animation
												(rotate_right ? eAnimStandTurnRight : eAnimStandTurnLeft, 0);
			object->dir().face_target			(enemy_pos);
		}

		object->set_action						(ACT_STAND_IDLE);
		return;
	}

	get_state_current()->execute				();
	prev_substate							=	current_substate;
}

template <typename Object>
void CStateAnomalPseudoGigantAttack<Object>::finalize()
{
	if ( object->anim().has_override_animation() )
	{
		object->anim().clear_override_animation	();
	}

	inherited::finalize							();
}

template <typename Object>
void CStateAnomalPseudoGigantAttack<Object>::critical_finalize()
{
	if ( object->anim().has_override_animation() )
	{
		object->anim().clear_override_animation	();
	}

	inherited::critical_finalize				();
}


template <typename Object>
bool   CStateAnomalPseudoGigantAttack<Object>::check_control_start_conditions (ControlCom::EControlType type)
{
	if ( type == ControlCom::eAntiAim )
	{
		return									m_allow_anti_aim;
	}

	return										true;
}