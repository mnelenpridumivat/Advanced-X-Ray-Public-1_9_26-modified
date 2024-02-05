#pragma once
#include "../monster_state_manager.h"

class CPoltergeist;

class CStateManagerPoltergeist : public CMonsterStateManager<CPoltergeist> {
	typedef CMonsterStateManager<CPoltergeist> inherited;


public:
						CStateManagerPoltergeist		(CPoltergeist *obj);
	~CStateManagerPoltergeist	() override;

	void		reinit						() override;
	void		execute						() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}

private:

			u32			time_next_flame_attack;
			u32			time_next_tele_attack;
			u32			time_next_scare_attack;

			void		polter_attack				();
			


};
