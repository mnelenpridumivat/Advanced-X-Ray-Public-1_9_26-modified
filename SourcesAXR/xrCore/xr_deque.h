#pragma once

#include <deque>
#include "xalloc.h"

// deque
template <typename T, typename allocator = xalloc<T> >
class xr_deque : public std::deque<T, allocator> {
public:
	typedef typename allocator								allocator_type;
	typedef typename allocator_type::value_type				value_type;
	typedef typename allocator_type::size_type				size_type;
	u32		size() const { return (u32)__super::size(); }
};
