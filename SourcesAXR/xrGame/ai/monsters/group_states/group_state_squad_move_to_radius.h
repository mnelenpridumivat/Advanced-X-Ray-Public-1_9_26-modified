#pragma once
#include "../state.h"
#include "../states/state_data.h"

template<typename _Object>
class CStateGroupSquadMoveToRadiusEx : public CState<_Object> {
	typedef CState<_Object> inherited;

protected:
	
	SStateDataMoveToPointEx data;

public:
						CStateGroupSquadMoveToRadiusEx	(_Object *obj) : inherited(obj, &data) {}
	~CStateGroupSquadMoveToRadiusEx	() override {}
	void		initialize					() override;
	void		execute						() override;
	bool		check_completion			() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

template<typename _Object>
class CStateGroupSquadMoveToRadius : public CState<_Object> {
	typedef CState<_Object> inherited;

protected:

	SStateDataMoveToPointEx data;

public:
	CStateGroupSquadMoveToRadius	(_Object *obj) : inherited(obj, &data) {}
	~CStateGroupSquadMoveToRadius	() override {}
	void		initialize					() override;
	void		execute						() override;
	bool		check_completion			() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};


#include "group_state_squad_move_to_radius_inline.h"
