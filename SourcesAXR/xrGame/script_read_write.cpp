#include "stdafx.h"
#include "script_read_write.h"
#include "../xrCore/FS.h"

LPCSTR CReaderScriptWrapper::r_stringZ()
{
	shared_str			temp;
	reader->r_stringZ(temp);
	return			(*temp);
}

void CReaderScriptWrapper::r_seek(u32 pos)
{
	reader->seek(pos);
}

u32 CReaderScriptWrapper::r_tell()
{
	return reader->tell();
}

void CReaderScriptWrapper::r_matrix(Fmatrix& M)
{
	M.i = r_vec3();
	M.j = r_vec3();
	M.k = r_vec3();
	M.c = r_vec3();
}

void CReaderScriptWrapper::r_clientID(ClientID& C)
{
	C.set(r_u32());
}

BOOL CReaderScriptWrapper::r_eof()
{
	return reader->eof();
}

u32 CReaderScriptWrapper::r_elapsed()
{
	return reader->elapsed();
}

void CReaderScriptWrapper::r_advance(u32 size)
{
	reader->advance(size);
}

CReaderScriptWrapper::CReaderScriptWrapper(IReader* reader)
{
	this->reader = reader;
}

bool CReaderScriptWrapper::r_bool()
{
	bool value;
	reader->r(&value, sizeof(bool));
	return value;
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
	return reader->r_u16();
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
	return reader->r_s16();
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

void CWriterScriptWrapper::w_begin(u16 type)
{
	writer->seek(0);
	writer->w_u16(type);
}

u32 CWriterScriptWrapper::w_tell()
{
	return writer->tell();
}

void CWriterScriptWrapper::w_seek(u32 pos, const void* p, u32 count)
{
	auto cur_pos = writer->tell();
	writer->seek(pos);
	writer->w(p, count);
	writer->seek(cur_pos);
}

void CWriterScriptWrapper::w_matrix(Fmatrix& M)
{
	w_vec3(M.i);
	w_vec3(M.j);
	w_vec3(M.k);
	w_vec3(M.c);
}

void CWriterScriptWrapper::w_clientID(ClientID& C)
{
	w_u32(C.value());
}

void CWriterScriptWrapper::w_chunk_open8(u32& position)
{
	position = w_tell();
	w_u8(0);
}

void CWriterScriptWrapper::w_chunk_close8(u32 position)
{
	u32 size = u32(w_tell() - position) - sizeof(u8);
	VERIFY(size < 256);
	u8			_size = (u8)size;
	w_seek(position, &_size, sizeof(_size));
}

void CWriterScriptWrapper::w_chunk_open16(u32& position)
{
	position = w_tell();
	w_u16(0);
}

void CWriterScriptWrapper::w_chunk_close16(u32 position)
{
	u32 size = u32(w_tell() - position) - sizeof(u16);
	VERIFY(size < 65536);
	u16			_size = (u16)size;
	w_seek(position, &_size, sizeof(_size));
}

CWriterScriptWrapper::CWriterScriptWrapper(IWriter* writer)
{
	this->writer = writer;
}

void CWriterScriptWrapper::w_bool(bool d)
{
	writer->w(&d, sizeof(bool));
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

void CWriterScriptWrapper::w_stringZ(LPCSTR p)
{
	writer->w_stringZ(p);
}
