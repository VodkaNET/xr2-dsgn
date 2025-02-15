////////////////////////////////////////////////////////////////////////////
//	Created		: 20.04.2010
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_ANIMATION_MIXING_N_ARY_TREE_INTRUSIVE_BASE_INLINE_H_INCLUDED
#define VOSTOK_ANIMATION_MIXING_N_ARY_TREE_INTRUSIVE_BASE_INLINE_H_INCLUDED

namespace vostok {
namespace animation {
namespace mixing {

inline n_ary_tree_intrusive_base::n_ary_tree_intrusive_base	( ) :
	m_reference_count	( 0 )
{
}

template <typename T>
inline void n_ary_tree_intrusive_base::destroy				( T& )
{
}

inline u32 n_ary_tree_intrusive_base::reference_count		( ) const
{
	return				m_reference_count;
}

} // namespace mixing
} // namespace animation
} // namespace vostok

#endif // #ifndef VOSTOK_ANIMATION_MIXING_N_ARY_TREE_INTRUSIVE_BASE_INLINE_H_INCLUDED