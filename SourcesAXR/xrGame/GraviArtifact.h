///////////////////////////////////////////////////////////////
// GraviArtifact.h
// GraviArtefact - гравитационный артефакт, прыгает на месте
// и парит над землей
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CGraviArtefact :
	public CArtefact,
	public IMetaClass
{
	DECLARE_METACLASS1(CGraviArtefact, CArtefact)
private:
	typedef CArtefact inherited;
public:
	CGraviArtefact(void);
	~CGraviArtefact(void) override;

	void Load				(LPCSTR section) override;

protected:
	void	UpdateCLChild	() override;
	//параметры артефакта
	float m_fJumpHeight;
	float m_fEnergy;
};
