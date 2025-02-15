////////////////////////////////////////////////////////////////////////////
//	Created		: 13.07.2011
//	Author		: Tetyana Meleshchenko
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_AI_SEARCH_OPERATOR_PAIR_H_INCLUDED
#define VOSTOK_AI_SEARCH_OPERATOR_PAIR_H_INCLUDED

#include <vostok/ai/search/base_types.h>

namespace vostok {
namespace ai {
namespace planning {

class operator_pair
{
public:
	typedef operator_id_type			operator_id_type;
	typedef operator_type				operator_type;
	typedef operator_ptr_type			operator_ptr_type;

public:
	inline								operator_pair	( operator_id_type const& operator_id, operator_ptr_type _operator );
	
	inline	bool						operator<		( operator_id_type const& operator_id ) const;
	
	inline	operator_ptr_type			get_operator	( ) const;
	inline	void						clear_operator	( );

	inline	operator_id_type const&		id				( ) const;

private:
	operator_id_type					m_id;
	operator_ptr_type					m_operator;
};

} // namespace planning
} // namespace ai
} // namespace vostok

#include <vostok/ai/search/operator_pair_inline.h>

#endif // #ifndef VOSTOK_AI_SEARCH_OPERATOR_PAIR_H_INCLUDED