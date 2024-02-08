///////////////////////////////////////////////////////////////
// GalantineArtifact.h
// GalantineArtefact - артефакт ведбмин студень
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CGalantineArtefact :
	public CArtefact,
	public IMetaClass
{
	DECLARE_METACLASS1(CGalantineArtefact, CArtefact)
private:
	typedef CArtefact inherited;
public:
	CGalantineArtefact(void);
	~CGalantineArtefact(void) override;

	void Load				(LPCSTR section) override;

protected:
};