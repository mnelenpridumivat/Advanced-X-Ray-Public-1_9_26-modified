#pragma once
#include "CustomDetector.h"
class CUIArtefactDetectorAdv;

class CAdvancedDetector :
	public CCustomDetector,
	public IMetaClass
{
	DECLARE_METACLASS1(CAdvancedDetector, CCustomDetector)
	typedef CCustomDetector	inherited;
public:
					CAdvancedDetector			();
	~CAdvancedDetector			() override;
	void	on_a_hud_attach				() override;
	void	on_b_hud_detach				() override;
protected:
	void 	UpdateAf					() override;
	void 	CreateUI					() override;
	CUIArtefactDetectorAdv& ui					();

};

//	static void _BCL		BoneCallback					(CBoneInstance *B);
