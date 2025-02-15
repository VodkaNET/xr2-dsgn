////////////////////////////////////////////////////////////////////////////
//	Created		: 04.03.2010
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#ifndef N_ARY_TREE_ADDITION_NODE_H_INCLUDED
#define N_ARY_TREE_ADDITION_NODE_H_INCLUDED

#include "mixing_n_ary_tree_n_ary_operation_node.h"

namespace vostok {
namespace animation {
namespace mixing {

class n_ary_tree_addition_node : public n_ary_tree_n_ary_operation_node {
public:
	inline	n_ary_tree_addition_node	( u32 const operands_count ) : n_ary_tree_n_ary_operation_node ( operands_count ) { }
	inline	n_ary_tree_addition_node	( n_ary_tree_addition_node const& other ) : n_ary_tree_n_ary_operation_node ( other ) { }

private:
	virtual	void	accept				( n_ary_tree_visitor& visitor );
	virtual void	accept				( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_base_node& node );
	virtual void	visit				( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_animation_node& node );
	virtual void	visit				( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_weight_node& node );
	virtual void	visit				( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_time_scale_node& node );
	virtual void	visit				( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_addition_node& node );
	virtual void	visit				( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_subtraction_node& node );
	virtual void	visit				( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_multiplication_node& node );
	virtual void	visit				( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_weight_transition_node& node );
	virtual void	visit				( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_time_scale_transition_node& node );
}; // class n_ary_tree_addition_node

} // namespace mixing
} // namespace animation
} // namespace vostok

#endif // #ifndef N_ARY_TREE_ADDITION_NODE_H_INCLUDED