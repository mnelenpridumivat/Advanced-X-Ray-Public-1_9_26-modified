#pragma once
#include "../state.h"
#include "state_data.h"

template<typename _Object>
class CStateMonsterMoveToPoint : public CState<_Object> {
	typedef CState<_Object> inherited;
	
	SStateDataMoveToPoint data;

public:
						CStateMonsterMoveToPoint	(_Object *obj) : inherited(obj, &data) {}
	~CStateMonsterMoveToPoint	() override {}

	void		initialize					() override;
	void		execute						() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}

	bool		check_completion			() override;

};


template<typename _Object>
class CStateMonsterMoveToPointEx : public CState<_Object> {
	typedef CState<_Object> inherited;

protected:
	
	SStateDataMoveToPointEx data;

public:
						CStateMonsterMoveToPointEx	(_Object *obj) : inherited(obj, &data) {}
	~CStateMonsterMoveToPointEx	() override {}
	void		initialize					() override;
	void		execute						() override;
	bool		check_completion			() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "state_move_to_point_inline.h"
