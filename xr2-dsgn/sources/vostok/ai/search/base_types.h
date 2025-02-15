////////////////////////////////////////////////////////////////////////////
//	Created		: 12.07.2011
//	Author		: Tetyana Meleshchenko
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_AI_SEARCH_BASE_TYPES_H_INCLUDED
#define VOSTOK_AI_SEARCH_BASE_TYPES_H_INCLUDED

namespace vostok {
namespace ai {
namespace planning {

class operator_impl;

typedef u32				property_id_type;
typedef bool			property_value_type;
typedef u32				operator_id_type;
typedef u32				operator_weight_type;
typedef operator_impl	operator_type;
typedef operator_type*	operator_ptr_type;

} // namespace planning
} // namespace ai
} // namespace vostok

#endif // #ifndef VOSTOK_AI_SEARCH_BASE_TYPES_H_INCLUDED