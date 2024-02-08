///////////////////////////////////////////////////////////////
// ThornArtifact.h
// ThornArtefact - артефакт колючка
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CThornArtefact :
	public CArtefact,
	public IMetaClass
{
	DECLARE_METACLASS1(CThornArtefact, CArtefact)
private:
	typedef CArtefact inherited;
public:
	CThornArtefact(void);
	~CThornArtefact(void) override;

	void Load				(LPCSTR section) override;

protected:
};