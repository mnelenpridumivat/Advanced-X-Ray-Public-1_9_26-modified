#include "stdafx.h"
#include "pch_script.h"
#include "script_read_write.h"

using namespace luabind;

#pragma optimize("s",on)
void CReaderScriptWrapper::script_register(lua_State* L)
{
	module(L)
		[
			class_<CReaderScriptWrapper>("CReader")
				.def("r_bool", &CReaderScriptWrapper::r_bool)
				.def("r_vec3", &CReaderScriptWrapper::r_vec3)
				.def("r_u64", &CReaderScriptWrapper::r_u64)
				.def("r_u32", &CReaderScriptWrapper::r_u32)
				.def("r_u16", &CReaderScriptWrapper::r_u16)
				.def("r_u8", &CReaderScriptWrapper::r_u8)
				.def("r_s64", &CReaderScriptWrapper::r_s64)
				.def("r_s32", &CReaderScriptWrapper::r_s32)
				.def("r_s16", &CReaderScriptWrapper::r_s16)
				.def("r_s8", &CReaderScriptWrapper::r_s8)
				.def("r_double", &CReaderScriptWrapper::r_double)
				.def("r_float", &CReaderScriptWrapper::r_float)
				.def("r_float_q16", &CReaderScriptWrapper::r_float_q16)
				.def("r_float_q8", &CReaderScriptWrapper::r_float_q8)
				.def("r_angle16", &CReaderScriptWrapper::r_angle16)
				.def("r_angle8", &CReaderScriptWrapper::r_angle8)
				.def("r_dir", &CReaderScriptWrapper::r_dir)
				.def("r_sdir", &CReaderScriptWrapper::r_sdir)
				.def("r_stringZ", &CReaderScriptWrapper::r_stringZ)
				.def("r_seek", &CReaderScriptWrapper::r_seek)
				.def("r_tell", &CReaderScriptWrapper::r_tell)
				.def("r_matrix", &CReaderScriptWrapper::r_matrix)
				.def("r_clientID", &CReaderScriptWrapper::r_clientID)
				.def("r_elapsed", &CReaderScriptWrapper::r_elapsed)
				.def("r_advance", &CReaderScriptWrapper::r_advance)
				.def("r_eof", &CReaderScriptWrapper::r_eof)

		];
}

SCRIPT_EXPORT(CReaderScriptWrapper);

#pragma optimize("s",on)
void CWriterScriptWrapper::script_register(lua_State* L)
{
	module(L)
		[
			class_<CWriterScriptWrapper>("CWriter")
				.def("w_bool", &CWriterScriptWrapper::w_bool)
				.def("w_vec3", &CWriterScriptWrapper::w_vec3)
				.def("w_u64", &CWriterScriptWrapper::w_u64)
				.def("w_u32", &CWriterScriptWrapper::w_u32)
				.def("w_u16", &CWriterScriptWrapper::w_u16)
				.def("w_u8", &CWriterScriptWrapper::w_u8)
				.def("w_s64", &CWriterScriptWrapper::w_s64)
				.def("w_s32", &CWriterScriptWrapper::w_s32)
				.def("w_s16", &CWriterScriptWrapper::w_s16)
				.def("w_s8", &CWriterScriptWrapper::w_s8)
				.def("w_double", &CWriterScriptWrapper::w_double)
				.def("w_float", &CWriterScriptWrapper::w_float)
				.def("w_float_q16", &CWriterScriptWrapper::w_float_q16)
				.def("w_float_q8", &CWriterScriptWrapper::w_float_q8)
				.def("w_angle16", &CWriterScriptWrapper::w_angle16)
				.def("w_angle8", &CWriterScriptWrapper::w_angle8)
				.def("w_dir", &CWriterScriptWrapper::w_dir)
				.def("w_sdir", &CWriterScriptWrapper::w_sdir)
				.def("w_stringZ", &CWriterScriptWrapper::w_stringZ)
				.def("w_begin", &CWriterScriptWrapper::w_begin)
				.def("w_tell", &CWriterScriptWrapper::w_tell)
				.def("w_matrix", &CWriterScriptWrapper::w_matrix)
				.def("w_clientID", &CWriterScriptWrapper::w_clientID)
				.def("w_chunk_open8", &CWriterScriptWrapper::w_chunk_open8)
				.def("w_chunk_close8", &CWriterScriptWrapper::w_chunk_close8)
				.def("w_chunk_open16", &CWriterScriptWrapper::w_chunk_open16)
				.def("w_chunk_close16", &CWriterScriptWrapper::w_chunk_close16)

		];
}

SCRIPT_EXPORT(CWriterScriptWrapper);
