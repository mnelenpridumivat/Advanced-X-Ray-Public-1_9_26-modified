#pragma once

#include "../../xrXMLParser/xrXMLParser.h"

class CUIXml :
	public CXml,
	public IMetaClass
{
	DECLARE_METACLASS1(CUIXml, CXml)
	int						m_dbg_id;
public:
			CUIXml			();
	~CUIXml			() override;

	shared_str correct_file_name	(LPCSTR path, LPCSTR fn) override;
};