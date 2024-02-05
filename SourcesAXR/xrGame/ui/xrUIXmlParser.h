#pragma once

#include "../../xrXMLParser/xrXMLParser.h"

class CUIXml :public CXml
{
	int						m_dbg_id;
public:
			CUIXml			();
	~CUIXml			() override;

	shared_str correct_file_name	(LPCSTR path, LPCSTR fn) override;
};