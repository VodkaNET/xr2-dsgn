////////////////////////////////////////////////////////////////////////////
//	Created		: 12.08.2011
//	Author		: Tetyana Meleshchenko
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef OR_LEXEME_H_INCLUDED
#define OR_LEXEME_H_INCLUDED

#include "binary_operation_lexeme.h"

namespace vostok {
namespace ai {
namespace planning {

class or_lexeme : public binary_operation_lexeme
{
public:
								or_lexeme		( base_lexeme const& left, base_lexeme const& right, bool const destroy_manually );

	virtual	base_lexeme const&	expand_brackets	( memory::stack_allocator& allocator ) const;
	virtual	base_lexeme const&	expand_brackets	( memory::stack_allocator& allocator, base_lexeme const& right ) const;
	virtual	base_lexeme const&	generate_permutations	( memory::stack_allocator& allocator, base_lexeme const& left ) const;

	virtual	u32	memory_size_for_brackets_expansion		( ) const;
	virtual	u32 memory_size_for_brackets_expansion		( base_lexeme const& right ) const;
	virtual	u32	memory_size_for_permutations_generation	( base_lexeme const& left ) const;

	virtual	void		add_to_preconditions	( generalized_action& action ) const;
	virtual	void		add_to_effects			( generalized_action& action ) const;

	virtual	void		destroy					( ) const;


}; // class or_lexeme

} // namespace planning
} // namespace ai
} // namespace vostok

#endif // #ifndef OR_LEXEME_H_INCLUDED