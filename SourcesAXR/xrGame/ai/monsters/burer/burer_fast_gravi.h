#pragma once
#include "../control_combase.h"

class CBurerFastGravi : public CControl_ComCustom<> {
	typedef CControl_ComCustom<> inherited;

public:
	bool	check_start_conditions	() override;
	void	activate				() override;
	void	deactivate				() override;
	void	on_event				(ControlCom::EEventType, ControlCom::IEventData*) override;
	
private:	
			void	process_hit				();

};

