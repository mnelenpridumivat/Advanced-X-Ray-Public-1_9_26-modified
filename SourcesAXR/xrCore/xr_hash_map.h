#pragma once

#include "xalloc.h"
#include <unordered_map>

template	<typename K, class V, class _Traits = std::equal_to<K>, typename allocator = xalloc<std::pair<const K, V> > >	
class	xr_hash_map : public std::unordered_map<K, V, std::hash<K>, _Traits, allocator> { 
public: 
	u32 size() const { 
		return (u32)__super::size(); 
	} 
};

template <typename K, class V, class Hasher = std::hash<K>, class Traits = std::equal_to<K>,
	typename allocator = xalloc<std::pair<const K, V>>>
using xr_unordered_map = std::unordered_map<K, V, Hasher, Traits, allocator>;
