#pragma once
#include <map>
#include "xalloc.h"

template <typename K, class V, class P = std::less<K>, typename allocator = xalloc<std::pair<const K, V>>>
using xr_map = std::map<K, V, P, allocator>;

template <typename K, class V, class P = std::less<K>, typename allocator = xalloc<std::pair<const K, V>>>
using xr_multimap = std::multimap<K, V, P, allocator>;
    