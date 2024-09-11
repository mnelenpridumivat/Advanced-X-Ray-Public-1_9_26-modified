////////////////////////////////////////////////////////////////////////////
//	Module 		: script_export_space.h
//	Created 	: 22.09.2003
//  Modified 	: 01.04.2004
//	Author		: Dmitriy Iassenev
//	Description : XRay Script export space 
////////////////////////////////////////////////////////////////////////////

#ifndef script_export_spaceH
#define script_export_spaceH

#pragma once
#include "../xrCore/vector.h"

struct lua_State;

//#define SCRIPT_REGISTRATOR

#ifdef SCRIPT_REGISTRATOR
#	define	script_type_list		Loki::NullType
#	define	add_to_type_list(type)	typedef Loki::Typelist<type,script_type_list> TypeList_##type;
#	define	save_type_list(type)	TypeList_##type
#else
#	define	script_type_list		
#	define	add_to_type_list(type)	;
#	define	save_type_list(type)		
#endif

#define DECLARE_SCRIPT_REGISTER_FUNCTION public: static void script_register(lua_State *);
#define DECLARE_SCRIPT_REGISTER_FUNCTION_STRUCT static void script_register(lua_State *);

template <typename T> struct enum_exporter{DECLARE_SCRIPT_REGISTER_FUNCTION};
template <typename T> struct class_exporter{DECLARE_SCRIPT_REGISTER_FUNCTION};

struct script_exporter_base {
	virtual void script_register(lua_State* L) = 0;
};

extern xr_vector<script_exporter_base*> script_exporter_container;

#define SCRIPT_EXPORT(x) script_exporter<x> x##_exporter;
#define SCRIPT_EXPORT_NAME(x, name) script_exporter<x> name##_exporter;

//xr_vector<script_exporter_base*> script_exporter_container::container = {};

template<typename T>
struct script_exporter: public script_exporter_base {
	script_exporter() {
		script_exporter_container.push_back(this);
	}

	virtual void script_register(lua_State* L) override {
		T::script_register(L);
	}
};

#endif
