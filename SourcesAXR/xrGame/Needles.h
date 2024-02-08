///////////////////////////////////////////////////////////////
// Needles.h
// Needles - артефакт иголки
///////////////////////////////////////////////////////////////

#pragma once
#include "artefact.h"

class CNeedles:
	public CArtefact,
	public IMetaClass
{
	DECLARE_METACLASS1(CNeedles, CArtefact)
private:
	typedef CArtefact inherited;
public:
	CNeedles(void);
	~CNeedles(void) override;
};