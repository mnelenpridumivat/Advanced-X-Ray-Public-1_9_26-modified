///////////////////////////////////////////////////////////////
// ZudaArtifact.h
// ZudaArtefact - артефакт зуда
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CZudaArtefact : public CArtefact 
{
private:
	typedef CArtefact inherited;
public:
	CZudaArtefact(void);
	~CZudaArtefact(void) override;

	void Load				(LPCSTR section) override;

protected:
};