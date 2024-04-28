////////////////////////////////////////////////////////////////////////////
//	Module 		: server_entity_wrapper.h
//	Created 	: 16.10.2004
//  Modified 	: 16.10.2004
//	Author		: Dmitriy Iassenev
//	Description : Server entity wrapper
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "object_interfaces.h"

class CSE_Abstract;

class CServerEntityWrapper : public IPureSerializeObject<IReader,IWriter> {
private:
	CSE_Abstract			*m_object;

public:
	IC						CServerEntityWrapper	(CSE_Abstract *object = nullptr);
	virtual					~CServerEntityWrapper	();
	void			save					(IWriter &stream) override;
	void			load					(IReader &stream) override;
			void			save_update				(IWriter &stream);
			void			load_update				(IReader &stream);
	IC		CSE_Abstract	&object					() const;
};

#include "server_entity_wrapper_inline.h"