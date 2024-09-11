#pragma once

#include "../xrCore/_types.h"
#include "../xrCore/_vector3d.h"
#include "script_export_space.h"

class IReader;
class IWriter;

class CReadWriteScriptWrapperBase {
protected:
	xr_vector<u8> data = {};
};

class CReaderScriptWrapper: public CReadWriteScriptWrapperBase {

	IReader* reader;

public:
	CReaderScriptWrapper(IReader* reader);


	Fvector		r_vec3();
	u64			r_u64();
	u32			r_u32();
	u16			r_u16();
	u8			r_u8();
	s64			r_s64();
	s32			r_s32();
	s16			r_s16();
	s8			r_s8();
	double		r_double();
	float		r_float();
	float		r_float_q16(float min, float max);
	float		r_float_q8(float min, float max);
	float		r_angle16();
	float		r_angle8();
	Fvector		r_dir();
	Fvector		r_sdir();
	LPCSTR		r_string();

	DECLARE_SCRIPT_REGISTER_FUNCTION;
};

add_to_type_list(CReaderScriptWrapper)
#undef script_type_list
#define script_type_list save_type_list(CReaderScriptWrapper)

class CWriterScriptWrapper : public CReadWriteScriptWrapperBase {

	IWriter* writer;

public:
	CWriterScriptWrapper(IWriter* writer);

	void		w_u64(u64 d);
	void		w_u32(u32 d);
	void		w_u16(u16 d);
	void		w_u8(u8 d);
	void		w_s64(s64 d);
	void		w_s32(s32 d);
	void		w_s16(s16 d);
	void		w_s8(s8 d);
	void		w_float(float d);
	void		w_double(double d);
	void		w_string(LPCSTR p);
	void		w_vec3(const Fvector3& v);
	void 		w_float_q16(float a, float min, float max);
	void 		w_float_q8(float a, float min, float max);
	void 		w_angle16(float a);
	void 		w_angle8(float a);
	void 		w_dir(const Fvector& D);
	void 		w_sdir(const Fvector& D);

	DECLARE_SCRIPT_REGISTER_FUNCTION;
};

add_to_type_list(CWriterScriptWrapper)
#undef script_type_list
#define script_type_list save_type_list(CWriterScriptWrapper)
