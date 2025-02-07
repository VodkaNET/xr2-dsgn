////////////////////////////////////////////////////////////////////////////
//	Created		: 20.04.2010
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef BASE_INTERPOLATOR_INLINE_H_INCLUDED
#define BASE_INTERPOLATOR_INLINE_H_INCLUDED

namespace vostok {
namespace animation {

template < typename T>
inline T* base_interpolator::clone_impl					( vostok::mutable_buffer& buffer ) const
{
	T* const result			= new (buffer.c_ptr()) T( static_cast<T const&>(*this) );
	buffer					+= sizeof(T);
	return					result;
}

inline bool base_interpolator::operator ==				( base_interpolator const& other ) const
{
	return					compare(*this, other) == equal;
}

inline bool	base_interpolator::operator !=				( base_interpolator const& other ) const
{
	return					!(*this == other);
}

inline bool operator <									(
		base_interpolator const& left,
		base_interpolator const& right
	)
{
	return					compare(left,right)	== less;
}

inline bool merge_interpolators_predicate::operator ( )	(
		base_interpolator const* const left,
		base_interpolator const* const right
	) const
{
	return					*left < *right;
}

inline bool unique_interpolators_predicate::operator ( )(
		base_interpolator const* const left,
		base_interpolator const* const right
	) const
{
	return					*left == *right;
}

} // namespace animation
} // namespace vostok

#endif // #ifndef BASE_INTERPOLATOR_INLINE_H_INCLUDED