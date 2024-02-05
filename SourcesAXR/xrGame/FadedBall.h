///////////////////////////////////////////////////////////////
// FadedBall.h
// FadedBall - �������� ������� ���
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CFadedBall : public CArtefact 
{
private:
	typedef CArtefact inherited;
public:
	CFadedBall(void);
	~CFadedBall(void) override;

	void Load				(LPCSTR section) override;

protected:
};