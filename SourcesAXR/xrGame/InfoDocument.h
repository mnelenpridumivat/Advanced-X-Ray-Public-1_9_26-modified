///////////////////////////////////////////////////////////////
// InfoDocument.h
// InfoDocument - документ, содержащий сюжетную информацию
///////////////////////////////////////////////////////////////


#pragma once

#include "inventory_item_object.h"
#include "InfoPortionDefs.h"

class CInfoDocument:
	public CInventoryItemObject,
    public IMetaClass
{
    DECLARE_METACLASS1(CInfoDocument, CInventoryItemObject)
private:
    typedef	CInventoryItemObject inherited;
public:
	CInfoDocument(void);
    ~CInfoDocument(void) override;

    BOOL net_Spawn			(CSE_Abstract* DC) override;
    void Load				(LPCSTR section) override;
    void net_Destroy		() override;
    void shedule_Update		(u32 dt) override;
    void UpdateCL			() override;
    void renderable_Render	() override;

    void OnH_A_Chield		() override;
    void OnH_B_Independent	(bool just_before_destroy) override;

protected:
	//индекс информации, содержащейся в документе
	shared_str m_Info;
};
