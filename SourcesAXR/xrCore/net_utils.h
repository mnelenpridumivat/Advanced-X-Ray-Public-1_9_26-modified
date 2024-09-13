#ifndef _INCDEF_NETUTILS_H_
#define _INCDEF_NETUTILS_H_
#pragma once

#include "client_id.h"

#pragma pack(push,1)

const	u32			NET_PacketSizeLimit = 16 * 1024;

enum class NET_Packet_token_type : u8 {
	token_double = 0,
	token_float,
	token_vec3,
	token_vec4,
	token_u64,
	token_s64,
	token_u32,
	token_s32,
	token_u16,
	token_s16,
	token_u8,
	token_s8,
	token_float_q16,
	token_float_q8,
	token_angle16,
	token_angle8,
	token_dir,
	token_sdir,
	token_stringZ,
	token_matrix,
	token_clientID,
	token_chunk8,
	token_chunk16,
};

struct XRCORE_API IIniFileStream
{
	virtual void	 __stdcall 	move_begin() = 0;

	virtual void	 __stdcall  w_token(NET_Packet_token_type token) = 0;

	virtual void	 __stdcall 	w_double(double a) = 0;
	virtual void	 __stdcall 	w_float(float a) = 0;
	virtual void 	 __stdcall 	w_vec3(const Fvector& a) = 0;
	virtual void 	 __stdcall 	w_vec4(const Fvector4& a) = 0;
	virtual void 	 __stdcall 	w_u64(u64 a) = 0;
	virtual void 	 __stdcall 	w_s64(s64 a) = 0;
	virtual void 	 __stdcall 	w_u32(u32 a) = 0;
	virtual void 	 __stdcall 	w_s32(s32 a) = 0;
	virtual void 	 __stdcall 	w_u16(u16 a) = 0;
	virtual void 	__stdcall	w_s16(s16 a) = 0;
	virtual void	__stdcall	w_u8(u8 a) = 0;
	virtual void	__stdcall	w_s8(s8 a) = 0;
	virtual void	__stdcall	w_stringZ(LPCSTR S) = 0;

	virtual void	__stdcall	r_vec3(Fvector&) = 0;
	virtual void	__stdcall	r_vec4(Fvector4&) = 0;
	virtual void	__stdcall	r_double(double&) = 0;
	virtual void	__stdcall	r_float(float&) = 0;
	virtual void	__stdcall	r_u8(u8&) = 0;
	virtual void	__stdcall	r_u16(u16&) = 0;
	virtual void	__stdcall	r_u32(u32&) = 0;
	virtual void	__stdcall	r_u64(u64&) = 0;
	virtual void	__stdcall	r_s8(s8&) = 0;
	virtual void	__stdcall	r_s16(s16&) = 0;
	virtual void	__stdcall	r_s32(s32&) = 0;
	virtual void	__stdcall	r_s64(s64&) = 0;

	virtual void	__stdcall	r_string(LPSTR dest, u32 dest_size) = 0;
	//	virtual void	__stdcall	r_tell			()							= 0;
	//	virtual void	__stdcall	r_seek			(u32 pos)					= 0;
	virtual void	__stdcall	skip_stringZ() = 0;
};


#define INI_W(what_to_do)\
if(inistream)\
{\
	inistream->what_to_do;\
}

#define INI_ASSERT(what_to_do)\
{\
if(inistream)\
	R_ASSERT3(0,#what_to_do,"not implemented");\
}

struct	NET_Buffer
{
	BYTE	data[NET_PacketSizeLimit];
	u32		count;
};

class XRCORE_API NET_Packet
{
public:
	IIniFileStream* inistream;

	void            construct(const void* data, unsigned size)
	{
		memcpy(B.data, data, size);
		B.count = size;
	}

	NET_Buffer		B;
	u32				r_pos;
	u32				timeReceive;
	bool			w_allow;
public:
	NET_Packet() :inistream(NULL), w_allow(true) {}

	// writing - main
	IC void write_start() { 
		B.count = 0;				
		INI_W(move_begin()); 
	}

	IC void	w_begin(u16 type) { 
		B.count = 0;	
		w_u16(type, false); 
	}

	struct W_guard {
		bool* guarded;
		W_guard(bool* b) :guarded(b) { *b = true; }
		~W_guard() { *guarded = false; }
	};

	IC void	w(const void* p, u32 count)
	{
		R_ASSERT(inistream == NULL || w_allow);
		VERIFY(p && count);
		VERIFY(B.count + count < NET_PacketSizeLimit);
		CopyMemory(&B.data[B.count], p, count);
		B.count += count;
		VERIFY(B.count < NET_PacketSizeLimit);
	}

	IC void w_seek(u32 pos, const void* p, u32 count);

	IC u32	w_tell() { return B.count; }

	IC void w_token(NET_Packet_token_type token) { 
		W_guard g(&w_allow);  
		w(&token, sizeof(NET_Packet_token_type)); 
		INI_W(w_token(token)); 
	}

	// writing - utilities
	IC void	w_double(double a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_double);
		}
		w(&a, sizeof(double));
		INI_W(w_double(a));
	}			// float

	IC void	w_float(float a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_float);
		}
		w(&a, sizeof(float));
		INI_W(w_float(a));
	}			// float

	IC void w_vec3(const Fvector& a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_vec3);
		}
		w(&a, 3 * sizeof(float));
		INI_W(w_vec3(a));
	}			// vec3

	IC void w_vec4(const Fvector4& a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_vec4);
		}
		w(&a, 4 * sizeof(float));
		INI_W(w_vec4(a));
	}			// vec4

	IC void w_u64(u64 a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_u64);
		}
		w(&a, sizeof(u64));
		INI_W(w_u64(a));
	}			// qword (8b)

	IC void w_s64(s64 a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_s64);
		}
		w(&a, sizeof(s64));
		INI_W(w_s64(a));
	}			// qword (8b)

	IC void w_u32(u32 a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_u32);
		}
		w(&a, sizeof(u32));
		INI_W(w_u32(a));
	}			// dword (4b)

	IC void w_s32(s32 a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_s32);
		}
		w(&a, sizeof(s32));
		INI_W(w_s32(a));
	}			// dword (4b)

	IC void w_u16(u16 a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_u16);
		}
		w(&a, sizeof(u16));
		INI_W(w_u16(a));
	}			// word (2b)

	IC void w_s16(s16 a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_s16);
		}
		w(&a, sizeof(s16));
		INI_W(w_s16(a));
	}			// word (2b)

	IC void	w_u8(u8 a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_u8);
		}
		w(&a, sizeof(u8));
		INI_W(w_u8(a));
	}			// byte (1b)

	IC void	w_s8(s8 a, bool write_token = true) {
		W_guard g(&w_allow);
		if (write_token) {
			w_token(NET_Packet_token_type::token_s8);
		}
		w(&a, sizeof(s8));
		INI_W(w_s8(a));
	}			// byte (1b)

	IC void w_float_q16(float a, float min, float max, bool write_token = true)
	{
		if (write_token) {
			w_token(NET_Packet_token_type::token_float_q16);
		}
		VERIFY(a >= min && a <= max);
		float q = (a - min) / (max - min);
		w_u16(u16(iFloor(q * 65535.f + 0.5f)));
	}
	IC void w_float_q8(float a, float min, float max, bool write_token = true)
	{
		if (write_token) {
			w_token(NET_Packet_token_type::token_float_q8);
		}
		VERIFY(a >= min && a <= max);
		float q = (a - min) / (max - min);
		w_u8(u8(iFloor(q * 255.f + 0.5f)));
	}

	IC void w_angle16(float a, bool write_token = true) {
		if (write_token) {
			w_token(NET_Packet_token_type::token_angle16);
		}
		w_float_q16(angle_normalize(a), 0, PI_MUL_2, false); 
	}

	IC void w_angle8(float a, bool write_token = true) {
		if (write_token) {
			w_token(NET_Packet_token_type::token_angle8);
		}
		w_float_q8(angle_normalize(a), 0, PI_MUL_2, false); 
	}

	IC void w_dir(const Fvector& D, bool write_token = true) {
		if (write_token) {
			w_token(NET_Packet_token_type::token_dir);
		}
		w_u16(pvCompress(D), false); 
	}

	IC void w_sdir(const Fvector& D, bool write_token = true) {
		if (write_token) {
			w_token(NET_Packet_token_type::token_sdir);
		}
		Fvector C;
		float mag = D.magnitude();
		if (mag > EPS_S) {
			C.div(D, mag);
		}
		else {
			C.set(0, 0, 1);
			mag = 0;
		}
		w_dir(C, false);
		w_float(mag, false);
	}

	IC void w_stringZ(LPCSTR S, bool write_token = true) {
		if (write_token) {
			w_token(NET_Packet_token_type::token_stringZ);
		}
		W_guard g(&w_allow); 
		w(S, (u32)xr_strlen(S) + 1);	
		INI_W(w_stringZ(S)); 
	}

	IC void w_stringZ(const shared_str& p, bool write_token = true)
	{
		if (write_token) {
			w_token(NET_Packet_token_type::token_stringZ);
		}
		W_guard g(&w_allow);
		if (*p)
			w(*p, p.size() + 1);
		else {
			IIniFileStream* tmp = inistream;
			inistream = NULL;
			w_u8(0, false);
			inistream = tmp; //hack -(
		}

		INI_W(w_stringZ(p.c_str()));
	}
	IC void w_matrix(Fmatrix& M, bool write_token = true)
	{
		if (write_token) {
			w_token(NET_Packet_token_type::token_matrix);
		}
		w_vec3(M.i, false);
		w_vec3(M.j, false);
		w_vec3(M.k, false);
		w_vec3(M.c, false);
	}

	IC void w_clientID(ClientID& C, bool write_token = true) {
		if (write_token) {
			w_token(NET_Packet_token_type::token_clientID);
		}
		w_u32(C.value(), false); 
	}

	IC void	w_chunk_open8(u32& position, bool write_token = true)
	{
		if (write_token) {
			w_token(NET_Packet_token_type::token_chunk8);
		}
		position = w_tell();
		w_u8(0);
		INI_ASSERT(w_chunk_open8)
	}

	IC void w_chunk_close8(u32 position)
	{
		u32 size = u32(w_tell() - position) - sizeof(u8);
		VERIFY(size < 256);
		u8			_size = (u8)size;
		w_seek(position, &_size, sizeof(_size));
		INI_ASSERT(w_chunk_close8)
	}

	IC void	w_chunk_open16(u32& position, bool write_token = true)
	{
		if (write_token) {
			w_token(NET_Packet_token_type::token_chunk16);
		}
		position = w_tell();
		w_u16(0);
		INI_ASSERT(w_chunk_open16)
	}

	IC void w_chunk_close16(u32 position)
	{
		u32 size = u32(w_tell() - position) - sizeof(u16);
		VERIFY(size < 65536);
		u16			_size = (u16)size;
		w_seek(position, &_size, sizeof(_size));
		INI_ASSERT(w_chunk_close16)
	}

	// reading
	void		read_start();
	u32			r_begin(u16& type);
	void		r_seek(u32 pos);
	u32			r_tell();

	IC void		r(void* p, u32 count)
	{
		R_ASSERT(inistream == NULL);
		VERIFY(p && count);
		CopyMemory(p, &B.data[r_pos], count);
		r_pos += count;
#ifdef FS_DEBUG
		VERIFY(r_pos <= B.count);
#endif
	}
	BOOL		r_eof();
	u32			r_elapsed();
	void		r_advance(u32 size);

	void r_check_token(NET_Packet_token_type token);

	// reading - utilities
	void		r_vec3(Fvector& A, bool read_token = true);
	void		r_vec4(Fvector4& A, bool read_token = true);
	void		r_double(double& A, bool read_token = true);
	void		r_float(float& A, bool read_token = true);
	void 		r_u64(u64& A, bool read_token = true);
	void 		r_s64(s64& A, bool read_token = true);
	void 		r_u32(u32& A, bool read_token = true);
	void		r_s32(s32& A, bool read_token = true);
	void		r_u16(u16& A, bool read_token = true);
	void		r_s16(s16& A, bool read_token = true);
	void		r_u8(u8& A, bool read_token = true);
	void		r_s8(s8& A, bool read_token = true);

	// IReader compatibility
	Fvector		r_vec3();
	Fvector4	r_vec4();
	float		r_float_q8(float min, float max);
	float		r_float_q16(float min, float max);
	double		r_double();
	float		r_float();
	u64 		r_u64();
	s64 		r_s64();
	u32 		r_u32();
	s32			r_s32();
	u16			r_u16();
	s16			r_s16();
	u8			r_u8();
	s8			r_s8();

	void		r_float_q16(float& A, float min, float max, bool read_token = true);
	void		r_float_q8(float& A, float min, float max, bool read_token = true);
	void		r_angle16(float& A, bool read_token = true);
	void		r_angle8(float& A, bool read_token = true);
	void		r_dir(Fvector& A, bool read_token = true);

	void		r_sdir(Fvector& A, bool read_token = true);
	void		r_stringZ(LPSTR S, bool read_token = true);
	void		r_stringZ(xr_string& dest, bool read_token = true);
	void 		r_stringZ(shared_str& dest, bool read_token = true);

	void		skip_stringZ();

	void		r_stringZ_s(LPSTR string, u32 size, bool read_token = true);

	template <u32 size>
	inline void	r_stringZ_s(char(&string)[size], bool read_token = true)
	{
		r_stringZ_s(string, size, read_token);
	}

	void		r_matrix(Fmatrix& M, bool read_token = true);
	void		r_clientID(ClientID& C, bool read_token = true);
	};

#pragma pack(pop)

#endif /*_INCDEF_NETUTILS_H_*/