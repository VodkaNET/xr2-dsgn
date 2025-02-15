////////////////////////////////////////////////////////////////////////////
//	Created		: 25.02.2010
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef SUBTRACTION_LEXEME_H_INCLUDED
#define SUBTRACTION_LEXEME_H_INCLUDED

#include <vostok/animation/mixing_binary_tree_subtraction_node.h>
#include <vostok/animation/mixing_binary_operation_lexeme.h>
#include <vostok/animation/mixing_expression.h>

namespace vostok {
namespace animation {
namespace mixing {

class VOSTOK_ANIMATION_API subtraction_lexeme :
	public binary_tree_subtraction_node,
	public binary_operation_lexeme
{
public:
	template < typename T1, typename T2 >
	inline							subtraction_lexeme	( T1& left, T2& right );
	inline							subtraction_lexeme	( subtraction_lexeme const& other, bool );
	inline subtraction_lexeme* cloned_in_buffer			( );

protected:
	using binary_operation_lexeme::cloned_in_buffer;
}; // class subtraction_lexeme

	template < typename T1, typename T2 >
	inline subtraction_lexeme& operator -				( T1& left, T2& right );

} // namespace mixing
} // namespace animation
} // namespace vostok

#include <vostok/animation/mixing_subtraction_lexeme_inline.h>

#endif // #ifndef SUBTRACTION_LEXEME_H_INCLUDED