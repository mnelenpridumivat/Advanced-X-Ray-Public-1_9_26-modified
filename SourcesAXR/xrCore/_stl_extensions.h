#ifndef _STL_EXT_internal
#define _STL_EXT_internal

#include <functional>

#include "xalloc.h"

using std::swap;

#ifdef	__BORLANDC__
#define M_NOSTDCONTAINERS_EXT
#endif
#ifdef	_M_AMD64
#define M_DONTDEFERCLEAR_EXT
#endif

#define	M_DONTDEFERCLEAR_EXT		//. for mem-debug only

//--------	
#ifdef	M_NOSTDCONTAINERS_EXT

#define xr_list std::list
#define xr_deque std::deque
#define xr_stack std::stack
#define xr_set std::set
#define xr_multiset std::multiset
#define xr_map std::map
#define xr_hash_map std::hash_map
#define xr_multimap std::multimap
#define xr_string std::string

template <class T>
class xr_vector	: public std::vector<T> {
public: 
	typedef	size_t		size_type;
	typedef T&			reference;
	typedef const T&	const_reference;
public: 
			xr_vector			()								: std::vector<T>	()				{}
			xr_vector			(size_t _count, const T& _value): std::vector<T>	(_count,_value)	{}
	explicit xr_vector			(size_t _count)					: std::vector<T> 	(_count)		{}
	void	clear				()								{ erase(begin(),end());				} 
	void	clear_and_free		()								{ std::vector<T>::clear();			}
	void	clear_not_free		()								{ erase(begin(),end());	}
	ICF		const_reference	operator[]	(size_type _Pos) const	{ {VERIFY(_Pos<size());} return (*(begin() + _Pos)); }
	ICF		reference		operator[]	(size_type _Pos)		{ {VERIFY(_Pos<size());} return (*(begin() + _Pos)); }
};

template	<>												
class	xr_vector<bool>	: public std::vector<bool>{ 
	typedef	bool		T;
public: 
			xr_vector<T>		()								: std::vector<T>	()				{}
			xr_vector<T>		(size_t _count, const T& _value): std::vector<T>	(_count,_value)	{}
	explicit xr_vector<T>		(size_t _count)					: std::vector<T>	(_count)		{}
	u32		size() const										{ return (u32)std::vector<T>::size();	} 
	void	clear()												{ erase(begin(),end());				} 
};

#else

namespace std
{
	template<class _Tp1, class _Tp2>	inline	xalloc<_Tp2>&	__stl_alloc_rebind(xalloc<_Tp1>& __a, const _Tp2*)	{	return (xalloc<_Tp2>&)(__a);	}
	template<class _Tp1, class _Tp2>	inline	xalloc<_Tp2>	__stl_alloc_create(xalloc<_Tp1>&, const _Tp2*)		{	return xalloc<_Tp2>();			}

	//template<typename left, typename right, typename ret>
	//using binary_function = function<ret(left, right)>;
};

template	<typename T, typename allocator = xalloc<T> >									class	xr_list 		: public std::list<T,allocator>			{ public: u32 size() const {return (u32)__super::size(); } };
template	<typename K, class P=std::less<K>, typename allocator = xalloc<K> >				class	xr_set			: public std::set<K,P,allocator>		{ public: u32 size() const {return (u32)__super::size(); } };
template	<typename K, class P=std::less<K>, typename allocator = xalloc<K> >				class	xr_multiset		: public std::multiset<K,P,allocator>	{ public: u32 size() const {return (u32)__super::size(); } };
template	<typename K, class V, class P=std::less<K>, typename allocator = xalloc<std::pair<const K,V> > >	class	xr_map 			: public std::map<K,V,P,allocator>		{ public: u32 size() const {return (u32)__super::size(); } };
template	<typename K, class V, class P=std::less<K>, typename allocator = xalloc<std::pair<const K,V> > >	class	xr_multimap		: public std::multimap<K,V,P,allocator>	{ public: u32 size() const {return (u32)__super::size(); } };

template	<typename K, class V, class _Traits = std::equal_to<K>, typename allocator = xalloc<std::pair<const K,V> > >	class	xr_hash_map		: public std::unordered_map<K,V,std::hash<K>, _Traits,allocator>	{ public: u32 size() const {return (u32)__super::size(); } };
template	<typename K, class _Traits = std::equal_to<K>, typename allocator = xalloc<K> >	class	xr_hash_set : public std::unordered_set<K, std::hash<K>, _Traits, allocator> { public: u32 size() const { return (u32)__super::size(); } };


#endif

template	<class _Ty1, class _Ty2> inline	std::pair<_Ty1, _Ty2>		mk_pair(_Ty1 _Val1, _Ty2 _Val2)	{	return (std::pair<_Ty1, _Ty2>(_Val1, _Val2));	}

struct pred_str
{	
	IC bool operator()(const char* x, const char* y) const				{	return xr_strcmp(x,y)<0;	}
};
struct pred_stri
{	
	IC bool operator()(const char* x, const char* y) const				{	return stricmp(x,y)<0;	}
};

template <typename K, class V, class Hasher = std::hash<K>, class Traits = std::equal_to<K>,
	typename allocator = xalloc<std::pair<const K, V>>>
	using xr_unordered_map = std::unordered_map<K, V, Hasher, Traits, allocator>;

#include "FixedVector.h"
#include "buffer_vector.h"

#endif