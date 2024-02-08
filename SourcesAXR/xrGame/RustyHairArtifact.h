///////////////////////////////////////////////////////////////
// RustyHairArtifact.h
// RustyHairArtefact - артефакт ржавые волосы
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CRustyHairArtefact :
	public CArtefact,
	public IMetaClass
{
	DECLARE_METACLASS1(CRustyHairArtefact, CArtefact)
private:
	typedef CArtefact inherited;
public:
	CRustyHairArtefact(void);
	~CRustyHairArtefact(void) override;

	void Load				(LPCSTR section) override;

protected:
};