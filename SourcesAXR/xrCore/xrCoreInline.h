#pragma once


// inline control - redefine to use compiler's heuristics ONLY
// it seems "IC" is misused in many places which cause code-bloat
// ...and VC7.1 really don't miss opportunities for inline :)
#ifdef _EDITOR
#	define __forceinline	inline
#endif
#define _inline			inline
#define __inline		inline
#define IC				inline
#define ICF				__forceinline			// !!! this should be used only in critical places found by PROFILER
#ifdef _EDITOR
#	define ICN
#else
#	define ICN			__declspec (noinline)	
#endif