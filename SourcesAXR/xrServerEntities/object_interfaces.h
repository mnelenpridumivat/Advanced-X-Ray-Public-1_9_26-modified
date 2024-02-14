////////////////////////////////////////////////////////////////////////////
//	Module 		: object_interfaces.h
//	Created 	: 05.01.2003
//  Modified 	: 12.05.2004
//	Author		: Dmitriy Iassenev
//	Description : ALife interfaces
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../xrGame/Metaclass.h"
//#include "../xrCore/FS.h"

class NET_Packet;

class IPureDestroyableObject:
	public IMetaClass
{
	DECLARE_METACLASS(IPureDestroyableObject)
public:
	virtual void					destroy()											= 0;
};

template <typename _storage_type>
class IPureLoadableObject :
	public IMetaClass
{
	DECLARE_METACLASS(IPureLoadableObject)
public:
	virtual void					load(_storage_type	&storage)						= 0;
};

template <typename _storage_type>
class IPureSavableObject :
	public IMetaClass
{
	DECLARE_METACLASS(IPureSavableObject)
public:
	virtual void					save(_storage_type	&storage)						= 0;
};

template <typename _storage_type_load, typename _storage_type_save>
class IPureSerializeObject :
	public IPureLoadableObject<_storage_type_load>,
	public IPureSavableObject<_storage_type_save>,
	public IMetaClass
{
	DECLARE_METACLASS2(IPureSerializeObject, IPureLoadableObject<_storage_type_load>, IPureSavableObject<_storage_type_save>)
public:
};

class IPureServerObject :
	public IPureSerializeObject<IReader,IWriter>,
	public IMetaClass
{
	using IPureSerializeObjectTempl = IPureSerializeObject<IReader, IWriter>;
	DECLARE_METACLASS1(IPureServerObject, IPureSerializeObjectTempl)
public:
	virtual void					STATE_Write	(NET_Packet &tNetPacket)				= 0;
	virtual void					STATE_Read	(NET_Packet &tNetPacket, u16 size)		= 0;
	virtual void					UPDATE_Write(NET_Packet &tNetPacket)				= 0;
	virtual void					UPDATE_Read	(NET_Packet &tNetPacket)				= 0;
};

class IPureSchedulableObject:
	public IMetaClass
{
	DECLARE_METACLASS(IPureSchedulableObject)
public:
	virtual void					update		()										= 0;
};
