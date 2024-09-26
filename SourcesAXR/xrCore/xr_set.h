#pragma once

#include <set>
#include "xalloc.h"
#include "xr_multiset.h"

template	<typename K, class P = std::less<K>, typename allocator = xalloc<K> >				
class	xr_set : public std::set<K, P, allocator> { 
public: 
	u32 size() const { 
		return (u32)__super::size(); 
	} 
};
