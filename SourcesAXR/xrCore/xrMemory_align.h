#pragma once

#pragma message("xrMemory_align.h moved to xrCommon/Memory/xrMemory_align.h")
#include "xrCommon/Memory/xrMemory_align.h"

#if 0
#ifndef xrMemory_alignH
#define xrMemory_alignH
#pragma once

u32		__stdcall xr_aligned_msize(void *);
void    __stdcall xr_aligned_free(void *);
void *  __stdcall xr_aligned_malloc(size_t, size_t);
void *  __stdcall xr_aligned_offset_malloc(size_t, size_t, size_t);
void *  __stdcall xr_aligned_realloc(void *, size_t, size_t);
void *  __stdcall xr_aligned_offset_realloc(void *, size_t, size_t, size_t);

#endif
#endif