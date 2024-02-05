///////////////////////////////////////////////////////////////
// BlackDrops.h
// BlackDrops - черные капли
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CBlackDrops : public CArtefact 
{
private:
	typedef CArtefact inherited;
public:
	CBlackDrops(void);
	~CBlackDrops(void) override;

	void Load				(LPCSTR section) override;

protected:
};