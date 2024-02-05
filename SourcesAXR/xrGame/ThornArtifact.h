///////////////////////////////////////////////////////////////
// ThornArtifact.h
// ThornArtefact - артефакт колючка
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CThornArtefact : public CArtefact 
{
private:
	typedef CArtefact inherited;
public:
	CThornArtefact(void);
	~CThornArtefact(void) override;

	void Load				(LPCSTR section) override;

protected:
};