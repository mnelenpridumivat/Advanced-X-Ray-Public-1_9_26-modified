#include "stdafx.h"
#include "script_read_write.h"
#include "../xrCore/FS.h"

LPCSTR CReaderScriptWrapper::r_string()
{
	shared_str			temp;
	reader->r_stringZ(temp);
	return			(*temp);
}

CReaderScriptWrapper::CReaderScriptWrapper(IReader* reader)
{
	this->reader = reader;
}

Fvector CReaderScriptWrapper::r_vec3()
{
	return reader->r_vec3();
}

u64 CReaderScriptWrapper::r_u64()
{
	return reader->r_u64();
}

u32 CReaderScriptWrapper::r_u32()
{
	return reader->r_u32();
}

u16 CReaderScriptWrapper::r_u16()
{
	return reader->r_u64();
}

u8 CReaderScriptWrapper::r_u8()
{
	return reader->r_u8();
}

s64 CReaderScriptWrapper::r_s64()
{
	return reader->r_s64();
}

s32 CReaderScriptWrapper::r_s32()
{
	return reader->r_s32();
}

s16 CReaderScriptWrapper::r_s16()
{
	return reader->r_s64();
}

s8 CReaderScriptWrapper::r_s8()
{
	return reader->r_s8();
}

double CReaderScriptWrapper::r_double()
{
	return reader->r_double();
}

float CReaderScriptWrapper::r_float()
{
	return reader->r_float();
}

float CReaderScriptWrapper::r_float_q16(float min, float max)
{
	return reader->r_float_q16(min, max);
}

float CReaderScriptWrapper::r_float_q8(float min, float max)
{
	return reader->r_float_q16(min, max);
}

float CReaderScriptWrapper::r_angle16()
{
	return reader->r_angle16();
}

float CReaderScriptWrapper::r_angle8()
{
	return reader->r_angle8();
}

Fvector CReaderScriptWrapper::r_dir()
{
	Fvector3 dir;
	reader->r_dir(dir);
	return dir;
}

Fvector CReaderScriptWrapper::r_sdir()
{
	Fvector3 dir;
	reader->r_sdir(dir);
	return dir;
}

void CWriterScriptWrapper::w_vec3(const Fvector3& v)
{
	writer->w_fvector3(v);
}

void CWriterScriptWrapper::w_float_q16(float a, float min, float max)
{
	writer->w_float_q16(a, min, max);
}

void CWriterScriptWrapper::w_float_q8(float a, float min, float max)
{
	writer->w_float_q8(a, min, max);
}

void CWriterScriptWrapper::w_angle16(float a)
{
	writer->w_angle16(a);
}

void CWriterScriptWrapper::w_angle8(float a)
{
	writer->w_angle8(a);
}

void CWriterScriptWrapper::w_dir(const Fvector& D)
{
	writer->w_dir(D);
}

void CWriterScriptWrapper::w_sdir(const Fvector& D)
{
	writer->w_sdir(D);
}

CWriterScriptWrapper::CWriterScriptWrapper(IWriter* writer)
{
	this->writer = writer;
}

void CWriterScriptWrapper::w_u64(u64 d)
{
	writer->w_u64(d);
}

void CWriterScriptWrapper::w_u32(u32 d)
{
	writer->w_u32(d);
}

void CWriterScriptWrapper::w_u16(u16 d)
{
	writer->w_u16(d);
}

void CWriterScriptWrapper::w_u8(u8 d)
{
	writer->w_u8(d);
}

void CWriterScriptWrapper::w_s64(s64 d)
{
	writer->w_s64(d);
}

void CWriterScriptWrapper::w_s32(s32 d)
{
	writer->w_s32(d);
}

void CWriterScriptWrapper::w_s16(s16 d)
{
	writer->w_s16(d);
}

void CWriterScriptWrapper::w_s8(s8 d)
{
	writer->w_s8(d);
}

void CWriterScriptWrapper::w_float(float d)
{
	writer->w_float(d);
}

void CWriterScriptWrapper::w_double(double d)
{
	writer->w_double(d);
}

void CWriterScriptWrapper::w_string(LPCSTR p)
{
	writer->w_string(p);
}
