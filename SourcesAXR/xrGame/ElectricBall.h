///////////////////////////////////////////////////////////////
// ElectricBall.h
// ElectricBall - артефакт электрический шар
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CElectricBall :
	public CArtefact,
	public IMetaClass
{
	DECLARE_METACLASS1(CElectricBall, CArtefact)
private:
	typedef CArtefact inherited;
public:
	CElectricBall(void);
	~CElectricBall(void) override;

	void Load				(LPCSTR section) override;

protected:
	void	UpdateCLChild	() override;

};