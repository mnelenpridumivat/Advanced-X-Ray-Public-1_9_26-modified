///////////////////////////////////////////////////////////////
// BlackDrops.h
// BlackDrops - черные капли
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CBlackDrops :
	public CArtefact,
	public IMetaClass
{
	DECLARE_METACLASS1(CBlackDrops, CArtefact)
private:
	typedef CArtefact inherited;
public:
	CBlackDrops(void);
	~CBlackDrops(void) override;

	void Load				(LPCSTR section) override;

protected:
};