///////////////////////////////////////////////////////////////
// DummyArtifact.h
// DummyArtefact - артефакт пустышка
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CDummyArtefact :
	public CArtefact,
	public IMetaClass
{
	DECLARE_METACLASS1(CDummyArtefact, CArtefact)
private:
	typedef CArtefact inherited;
public:
	CDummyArtefact(void);
	~CDummyArtefact(void) override;

	void Load				(LPCSTR section) override;

protected:
};