////////////////////////////////////////////////////////////////////////////
//	Created		: 12.02.2009
//	Author		: Mykhailo Parfeniuk
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef MANAGER_COMMON_INLINE_H_INCLUDED
#define MANAGER_COMMON_INLINE_H_INCLUDED

namespace vostok {
namespace render {

template < typename T >
inline bool reclaim(vector<T*>& vec, const T* ptr)
{
	vector<T*>::iterator	it	= vec.begin(),
		end	= vec.end();

	for (; it!=end; ++it)
	{
		if (*it == ptr)
		{
			vec.erase(it);
			return true;
		}
	}

	return false;
}

template<typename T>
bool reclaim_with_id(vector<T*>& vec, const T* ptr)
{
	bool	found = false;
	vector<T*>::iterator it   = vec.begin(),
		end  = vec.end(),
		last = vec.end() - 1;

	for(; it!=end; it++)
	{
		if (*it==ptr)
		{
			found = true;

			if (it+1 != vec.end())
			{
				//set new id
				(*last)->set_id((*it)->id());
				std::swap(*it, *last);
			}

			vec.pop_back();

			break;
		}
	}

	return found;
}

template <class T>
u32 gen_id(const T& res_map, vector<u32>& free_id)
{
	if (free_id.empty())
	{
		return static_cast<u32>(res_map.size());
	}

	u32 id = free_id.back();
	free_id.pop_back();

	return id;
}

template<typename T1, typename T2>
std::pair<T1, T2> mk_pair(const T1& p1, const T2& p2)
{
	return std::pair<T1, T2>(p1, p2);
}

template<typename fw_iterator, typename predicate>
u32 remove_if( fw_iterator begin, fw_iterator end, predicate pred)
{
	fw_iterator  pref_it	= begin;
	fw_iterator  it			= begin;
	for( ; it != end; ++it )
	{
		if( pred(it))

	}
}

} // namespace render 
} // namespace vostok 


#endif // #ifndef MANAGER_COMMON_INLINE_H_INCLUDED