#pragma once

#include "xalloc.h"
#include <unordered_set>

template	<typename K, class _Traits = std::equal_to<K>, typename allocator = xalloc<K> >	
class	xr_hash_set : public std::unordered_set<K, std::hash<K>, _Traits, allocator> { 
public: 
	u32 size() const { 
		return (u32)__super::size(); 
	} 
};
