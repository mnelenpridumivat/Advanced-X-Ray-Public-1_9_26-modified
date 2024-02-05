///////////////////////////////////////////////////////////////
// ElectricBall.h
// ElectricBall - �������� ������������� ���
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CElectricBall : public CArtefact 
{
private:
	typedef CArtefact inherited;
public:
	CElectricBall(void);
	~CElectricBall(void) override;

	void Load				(LPCSTR section) override;

protected:
	void	UpdateCLChild	() override;

};