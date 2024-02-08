///////////////////////////////////////////////////////////////
// FadedBall.h
// FadedBall - артефакт блеклый шар
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CFadedBall :
	public CArtefact,
	public IMetaClass
{
	DECLARE_METACLASS1(CFadedBall, CArtefact)
private:
	typedef CArtefact inherited;
public:
	CFadedBall(void);
	~CFadedBall(void) override;

	void Load				(LPCSTR section) override;

protected:
};