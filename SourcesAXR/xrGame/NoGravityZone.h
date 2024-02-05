#pragma once
#include "CustomZone.h"

class CNoGravityZone :
	public CCustomZone
{
typedef CCustomZone inherited;
public:
protected:
void	enter_Zone						(SZoneObjectInfo& io) override;
void	exit_Zone						(SZoneObjectInfo& io) override;
private:
				void	switchGravity					(SZoneObjectInfo& io,bool val)		;
void	UpdateWorkload					(u32	dt	) override;
};