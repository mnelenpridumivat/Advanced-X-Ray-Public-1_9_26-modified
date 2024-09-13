#include "stdafx.h"
#pragma hdrstop
#include "NET_utils.h"


// ---NET_Packet
// reading
void NET_Packet::read_start()	{	r_pos		= 0; INI_W(move_begin());}

u32 NET_Packet::r_begin			( u16& type	)	// returns time of receiving
{
	r_pos		= 0;
	if(!inistream)
		r_u16		(type);
	else
		inistream->r_u16(type);

	return		timeReceive;
}

void NET_Packet::w_seek	(u32 pos, const void* p, u32 count)	
{
	VERIFY(p && count && (pos+count<=B.count)); 
	CopyMemory(&B.data[pos],p,count);	
//.	INI_ASSERT		(w_seek)
}

void NET_Packet::r_seek	(u32 pos)
{
	INI_ASSERT		(r_seek)
	VERIFY			(pos < B.count);
	r_pos			= pos;
}

u32 NET_Packet::r_tell()	
{ 
	INI_ASSERT		(r_tell)
	return			r_pos; 
}

BOOL NET_Packet::r_eof()
{
	INI_ASSERT		(r_eof)
	return			(r_pos>=B.count);
}

u32 NET_Packet::r_elapsed()
{
	INI_ASSERT		(r_elapsed)
	return			(B.count-r_pos);
}

void NET_Packet::r_advance(u32 size)		
{
	INI_ASSERT		(r_advance)
	r_pos			+= size;	
	VERIFY			(r_pos<=B.count);
}

void NET_Packet::r_check_token(NET_Packet_token_type token)
{
	static xr_unordered_map<NET_Packet_token_type, xr_string> token_names = {
		{NET_Packet_token_type::token_double, "double"},
		{NET_Packet_token_type::token_float, "float"},
		{NET_Packet_token_type::token_vec3, "vec3"},
		{NET_Packet_token_type::token_vec4, "vec4"},
		{NET_Packet_token_type::token_u64, "u64"},
		{NET_Packet_token_type::token_s64, "s64"},
		{NET_Packet_token_type::token_u32, "u32"},
		{NET_Packet_token_type::token_s32, "s32"},
		{NET_Packet_token_type::token_u16, "u16"},
		{NET_Packet_token_type::token_s16, "s16"},
		{NET_Packet_token_type::token_u8, "u8"},
		{NET_Packet_token_type::token_s8, "s8"},
		{NET_Packet_token_type::token_float_q16, "float_q16"},
		{NET_Packet_token_type::token_float_q8, "float_q8"},
		{NET_Packet_token_type::token_angle16, "angle16"},
		{NET_Packet_token_type::token_angle8, "angle8"},
		{NET_Packet_token_type::token_dir, "dir"},
		{NET_Packet_token_type::token_sdir, "sdir"},
		{NET_Packet_token_type::token_stringZ, "string"},
		{NET_Packet_token_type::token_matrix, "matrix"},
		{NET_Packet_token_type::token_clientID, "clientID"},
		{NET_Packet_token_type::token_chunk8, "chunk8"},
		{NET_Packet_token_type::token_chunk16, "chunk16"}
	};
	NET_Packet_token_type value;
	r(&value, sizeof(NET_Packet_token_type));
	if (value != token) {
		VERIFY(token_names.find(value) != token_names.end());
		xr_string requested_token_name = "expect token: "+token_names[token];
		xr_string got_token_name = "got token: "+token_names[value];
		VERIFY4(value == token, "Error reading NET packet: token not matching", requested_token_name.c_str(), got_token_name.c_str());
	}
}

// reading - utilities
void NET_Packet::r_vec3(Fvector& A, bool read_token)
{ 
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_vec3);
	}
	if (!inistream) {
		r(&A, sizeof(Fvector));
	}
	else {
		inistream->r_vec3(A);
	}
} // vec3

void NET_Packet::r_vec4(Fvector4& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_vec4);
	}
	if (!inistream) {
		r(&A, sizeof(Fvector4));
	}
	else {
		inistream->r_vec4(A);
	}
} // vec4

void NET_Packet::r_double(double& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_double);
	}
	if (!inistream) {
		r(&A, sizeof(double));
	}
	else {
		inistream->r_double(A);
	}
} // double

void NET_Packet::r_float(float& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_float);
	}
	if (!inistream) {
		r(&A, sizeof(float));
	}
	else {
		inistream->r_float(A);
	}
} // float

void NET_Packet::r_u64(u64& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_u64);
	}
	if (!inistream) {
		r(&A, sizeof(u64));
	}
	else {
		inistream->r_u64(A);
	}
} // qword (8b)

void NET_Packet::r_s64(s64& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_s64);
	}
	if (!inistream) {
		r(&A, sizeof(s64));
	}
	else {
		inistream->r_s64(A);
	}
} // qword (8b)

void NET_Packet::r_u32(u32& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_u32);
	}
	if (!inistream) {
		r(&A, sizeof(u32));
	}
	else {
		inistream->r_u32(A);
	}
} // dword (4b)

void NET_Packet::r_s32(s32& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_s32);
	}
	if (!inistream) {
		r(&A, sizeof(s32));
	}
	else {
		inistream->r_s32(A);
	}
} // dword (4b)

void NET_Packet::r_u16(u16& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_u16);
	}
	if (!inistream) {
		r(&A, sizeof(u16));
	}
	else {
		inistream->r_u16(A);
	}
} // word (2b)

void NET_Packet::r_s16(s16& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_s16);
	}
	if (!inistream) {
		r(&A, sizeof(s16));
	}
	else {
		inistream->r_s16(A);
	}
} // word (2b)

void NET_Packet::r_u8(u8&  A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_u8);
	}
	if (!inistream) {
		r(&A, sizeof(u8));
	}
	else {
		inistream->r_u8(A);
	}
} // byte (1b)

void NET_Packet::r_s8(s8&  A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_s8);
	}
	if (!inistream) {
		r(&A, sizeof(s8));
	}
	else {
		inistream->r_s8(A);
	}
} // byte (1b)

// IReader compatibility
Fvector NET_Packet::r_vec3()		
{
	Fvector		A;
	r_vec3		(A);	
	return		(A);		
}

Fvector4 NET_Packet::r_vec4()
{
	Fvector4	A;
	r_vec4		(A);	
	return		(A);		
}

float NET_Packet::r_float_q8(float min,float max)
{
	float		A;
	r_float_q8	(A,min,max);
	return		A;
}

float NET_Packet::r_float_q16(float min, float max)
{
	float		A;
	r_float_q16	(A,min,max);
	return		A;
}

double NET_Packet::r_double()		
{ 
	double		A; 
	r_double	(A);					
	return		(A);		
} // float

float NET_Packet::r_float()
{
	float		A;
	r_float(A);
	return		(A);
} // float

u64 NET_Packet::r_u64()		
{ 
	u64 		A; 
	r_u64		(A);					
	return		(A);		
} // qword (8b)

s64 NET_Packet::r_s64()		
{ 
	s64 		A; 
	r_s64		(A);					
	return		(A);		
} // qword (8b)

u32 NET_Packet::r_u32()		
{ 
	u32 		A; 
	r_u32		(A);					
	return		(A);		
} // dword (4b)

s32 NET_Packet::r_s32()		
{ 
	s32			A; 
	r_s32		(A);					
	return		(A);		
} // dword (4b)

u16 NET_Packet::r_u16()		
{ 
	u16			A; 
	r_u16		(A);					
	return		(A);		
} // word (2b)

s16 NET_Packet::r_s16()		
{ 
	s16			A; 
	r_s16		(A);					
	return		(A);		
} // word (2b)

u8 NET_Packet::r_u8()		
{ 
	u8			A; 
	r_u8		(A);					
	return		(A);		
} // byte (1b)

s8 NET_Packet::r_s8()		
{ 
	s8			A; 
	r_s8		(A);					
	return		(A);		
}

void NET_Packet::r_float_q16(float& A, float min, float max, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_float_q16);
	}
	u16			val;
	r_u16		(val, false);
	A			= (float(val)*(max-min))/65535.f + min;		// floating-point-error possible
	VERIFY		((A >= min-EPS_S) && (A <= max+EPS_S));
}

void NET_Packet::r_float_q8(float& A, float min, float max, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_float_q8);
	}
	u8			val;
	r_u8		(val, false);
	A			= (float(val)/255.0001f) *(max-min) + min;	// floating-point-error possible
	VERIFY		((A >= min) && (A <= max));
}

void NET_Packet::r_angle16(float& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_angle16);
	}
	r_float_q16	(A,0,PI_MUL_2, false);	
}

void NET_Packet::r_angle8(float& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_angle8);
	}
	r_float_q8	(A,0,PI_MUL_2, false);	
}

void NET_Packet::r_dir(Fvector& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_dir);
	}
	u16			t; 
	r_u16		(t, false); 
	pvDecompress(A,t); 
}

void NET_Packet::r_sdir(Fvector& A, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_sdir);
	}
	u16				t;	
	float			s;
	r_u16			(t, false);
	r_float			(s, false);
	pvDecompress	(A,t);
	A.mul			(s);
}

void NET_Packet::r_stringZ( LPSTR S, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_stringZ);
	}
 	if(!inistream)
	{
		LPCSTR	data	= LPCSTR(&B.data[r_pos]);
		size_t	len		= xr_strlen(data);
		r				(S,(u32)len+1);
	}else{
		inistream->r_string(S, 4096);//???
	}
}

void NET_Packet::r_stringZ( xr_string& dest, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_stringZ);
	}
 	if(!inistream)
	{
		dest			= LPCSTR(&B.data[r_pos]);
		r_advance		(u32(dest.size()+1));
	}else{
		string4096		buff;
		inistream->r_string(buff, sizeof(buff));
		dest			= buff;
	}
}

void NET_Packet::r_stringZ(shared_str& dest, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_stringZ);
	}
 	if(!inistream)
	{
		dest			= LPCSTR(&B.data[r_pos]);
		r_advance		(dest.size()+1);
	}else{
		string4096		buff;
		inistream->r_string(buff, sizeof(buff));
		dest			= buff;
	}
}

void NET_Packet::skip_stringZ()
{
	r_check_token(NET_Packet_token_type::token_stringZ);
	if (!inistream)
	{
		LPCSTR	data	= LPCSTR(&B.data[r_pos]);
		u32	len		= xr_strlen(data);
		r_advance		(len + 1);
	} else {
		inistream->skip_stringZ	();
	}
}

void NET_Packet::r_matrix(Fmatrix& M, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_matrix);
	}
	r_vec3	(M.i, false);	M._14_	= 0;
	r_vec3	(M.j, false);	M._24_	= 0;
	r_vec3	(M.k, false);	M._34_	= 0;
	r_vec3	(M.c, false);	M._44_	= 1;
}

void NET_Packet::r_clientID(ClientID& C, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_clientID);
	}
	u32				tmp;
	r_u32			(tmp, false);
	C.set			(tmp);
}

void NET_Packet::r_stringZ_s	(LPSTR string, u32 const size, bool read_token)
{
	if (read_token) {
		r_check_token(NET_Packet_token_type::token_stringZ);
	}
	if ( inistream ) {
		inistream->r_string( string, size );
		return;
	}

	LPCSTR data		= LPCSTR( B.data + r_pos );
	u32 length		= xr_strlen( data );
	R_ASSERT2		( ( length+1 ) <= size, "buffer overrun" );
	r				( string, length+1 );
}