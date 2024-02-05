#pragma once
#include "../state.h"
#include "../../../grenade.h"


template<typename Object>
class CStateBurerAttackTele : public CState<Object> {
	typedef CState<Object> inherited;	

	xr_vector<CPhysicsShellHolder *>	tele_objects;
	CPhysicsShellHolder					*selected_object;
	xr_vector<CObject*>					m_nearest;
	
	u32									time_started;

	enum {
		ACTION_TELE_STARTED,
		ACTION_TELE_CONTINUE,
		ACTION_TELE_FIRE,
		ACTION_WAIT_FIRE_END,
		ACTION_COMPLETED,
	} m_action;

public:
						CStateBurerAttackTele	(Object *obj);

	void		initialize				() override;
	void		execute					() override;
	void		finalize				() override;
	void		critical_finalize		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	bool		check_start_conditions	() override;
	bool		check_completion		() override;


private:
			// Поиск объектов для телекинеза	
			void		FindObjects				();

			void		HandleGrenades			();

			// выполнять состояние
			void		ExecuteTeleContinue		();
			void		ExecuteTeleFire			();

			// Проверка, есть ли хоть один объект под контролем
			bool		IsActiveObjects			();

			// Проверить, может ли стартовать телекинез
			bool		CheckTeleStart			();
			// Выбор подходящих объектов для телекинеза
			void		SelectObjects			();

			// internal for FindObjects
			void		FindFreeObjects			(xr_vector<CObject*> &tpObjects, const Fvector &pos);
			void xr_stdcall OnGrenadeDestroyed	(CGrenade* const grenade);

			void		FireAllToEnemy			();
			void		deactivate				();

private:
	TTime				m_last_grenade_scan;
	TTime				m_anim_end_tick;
	TTime				m_end_tick;
	float				m_initial_health;
};

#include "burer_state_attack_tele_inline.h"
