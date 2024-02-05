///////////////////////////////////////////////////////////////
// DummyArtifact.h
// DummyArtefact - артефакт пустышка
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CDummyArtefact : public CArtefact 
{
private:
	typedef CArtefact inherited;
public:
	CDummyArtefact(void);
	~CDummyArtefact(void) override;

	void Load				(LPCSTR section) override;

protected:
};