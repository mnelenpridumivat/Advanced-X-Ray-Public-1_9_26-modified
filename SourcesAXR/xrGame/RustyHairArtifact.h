///////////////////////////////////////////////////////////////
// RustyHairArtifact.h
// RustyHairArtefact - �������� ������ ������
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CRustyHairArtefact : public CArtefact 
{
private:
	typedef CArtefact inherited;
public:
	CRustyHairArtefact(void);
	~CRustyHairArtefact(void) override;

	void Load				(LPCSTR section) override;

protected:
};