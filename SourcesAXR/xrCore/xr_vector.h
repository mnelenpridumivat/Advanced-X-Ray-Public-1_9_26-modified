#pragma once

#include <vector>
#include "_types.h"

// vector
template	<typename T, typename allocator = xalloc<T> >
class xr_vector : public std::vector<T, allocator> {
private:
	typedef std::vector<T, allocator>	inherited;

public:
	typedef allocator					allocator_type;

public:
	xr_vector() : inherited() {}
	xr_vector(size_t _count, const T& _value) : inherited(_count, _value) {}
	explicit xr_vector(size_t _count) : inherited(_count) {}
	u32		size() const { return (u32)inherited::size(); }

	void	clear_and_free() { inherited::clear(); }
	void	clear_not_free() { inherited::erase(inherited::begin(), inherited::end()); }
	void	clear_and_reserve() { if (inherited::capacity() <= (size() + size() / 4)) clear_not_free(); else { u32 old = size(); clear_and_free(); inherited::reserve(old); } }

#ifdef M_DONTDEFERCLEAR_EXT
	void	clear() { clear_and_free(); }
#else
	void	clear() { clear_not_free(); }
#endif

	inherited::const_reference operator[]	(inherited::size_type _Pos) const { { VERIFY2(_Pos < size(), make_string("index is out of range: index requested[%d], size of container[%d]", _Pos, size()).c_str()); } return (*(inherited::begin() + _Pos)); }
	inherited::reference operator[]		(inherited::size_type _Pos) { { VERIFY2(_Pos < size(), make_string("index is out of range: index requested[%d], size of container[%d]", _Pos, size()).c_str()); } return (*(inherited::begin() + _Pos)); }

	bool remove(T Item) {
		for (auto it = inherited::begin(); it != inherited::end(); ++it)
		{
			if (*it == Item)
			{
				inherited::erase(it);
				return true;
			}
		}
		return false;
	}
};

// vector<bool>
template <>
class xr_vector<bool, xalloc<bool> > : public std::vector<bool, xalloc<bool> > {
private:
	typedef std::vector<bool, xalloc<bool> > inherited;

public:
	u32		size() const { return (u32)inherited::size(); }
	void	clear() { erase(begin(), end()); }
};

template <typename allocator>
class xr_vector<bool, allocator> : public std::vector<bool, allocator> {
private:
	typedef std::vector<bool, allocator> inherited;

public:
	u32		size() const { return (u32)inherited::size(); }
	void	clear() { inherited::erase(inherited::begin(), inherited::end()); }
};
