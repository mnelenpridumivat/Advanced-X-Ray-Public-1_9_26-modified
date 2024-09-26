#pragma once

#include "xalloc.h"

template	<typename T, typename allocator = xalloc<T> >									
class	xr_list : public std::list<T, allocator> { 
public: 
	u32 size() const { 
		return (u32)__super::size(); 
	} 
};
