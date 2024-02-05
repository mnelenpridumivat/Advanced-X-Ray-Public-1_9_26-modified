///////////////////////////////////////////////////////////////
// GalantineArtifact.h
// GalantineArtefact - �������� ������� �������
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CGalantineArtefact : public CArtefact 
{
private:
	typedef CArtefact inherited;
public:
	CGalantineArtefact(void);
	~CGalantineArtefact(void) override;

	void Load				(LPCSTR section) override;

protected:
};