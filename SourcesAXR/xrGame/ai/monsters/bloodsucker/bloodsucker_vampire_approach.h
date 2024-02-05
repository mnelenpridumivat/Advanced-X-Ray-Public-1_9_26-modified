#pragma once
#include "../state.h"

template<typename _Object>
class CStateBloodsuckerVampireApproach : public CState<_Object> {
	typedef CState<_Object> inherited;

public:
						CStateBloodsuckerVampireApproach	(_Object *obj);
	~CStateBloodsuckerVampireApproach	() override;

	void		initialize							() override;
	void		execute								() override;
	void		remove_links						(CObject* object) override { inherited::remove_links(object);}
};

#include "bloodsucker_vampire_approach_inline.h"
