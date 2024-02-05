#pragma once
#include "customdetector.h"

class CUIArtefactDetectorSimple;

class CSimpleDetector :public CCustomDetector
{
	typedef CCustomDetector	inherited;
public:
					CSimpleDetector				();
	~CSimpleDetector			() override;
	
protected:
//.	virtual void 	UpdateZones					();
	void 	UpdateAf					() override;
	void 	CreateUI					() override;
	CUIArtefactDetectorSimple&	ui				();
};

