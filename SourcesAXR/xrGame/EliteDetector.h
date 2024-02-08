#pragma once
#include "CustomDetector.h"
#include "level.h"

class CUIArtefactDetectorElite;

class CEliteDetector :
	public CCustomDetector,
	public IMetaClass
{
	DECLARE_METACLASS1(CEliteDetector, CCustomDetector)
	typedef CCustomDetector	inherited;
public:
					CEliteDetector				();
	~CEliteDetector				() override;
	void	render_item_3d_ui			() override;
	bool	render_item_3d_ui_query		() override;
	virtual LPCSTR	ui_xml_tag					() const {return "elite";}
protected:
	void 	UpdateAf					() override;
	void 	CreateUI					() override;
	CUIArtefactDetectorElite& ui				();
};



class CScientificDetector :
	public CEliteDetector,
	public IMetaClass
{
	DECLARE_METACLASS1(CScientificDetector, CEliteDetector)
	typedef CEliteDetector	inherited;
public:
					CScientificDetector			();
	~CScientificDetector		() override;
	void 	Load						(LPCSTR section) override;
	void 	OnH_B_Independent			(bool just_before_destroy) override;
	void 	shedule_Update				(u32 dt) override;
	LPCSTR	ui_xml_tag					() const override {return "scientific";}
protected:
	void	UpfateWork					() override;
	CZoneList		m_zones;
};

