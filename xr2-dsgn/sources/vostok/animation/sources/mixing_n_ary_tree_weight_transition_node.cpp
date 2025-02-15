////////////////////////////////////////////////////////////////////////////
//	Created		: 04.03.2010
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "mixing_n_ary_tree_animation_node.h"
#include "mixing_n_ary_tree_weight_node.h"
#include "mixing_n_ary_tree_time_scale_node.h"
#include "mixing_n_ary_tree_addition_node.h"
#include "mixing_n_ary_tree_subtraction_node.h"
#include "mixing_n_ary_tree_multiplication_node.h"
#include "mixing_n_ary_tree_weight_transition_node.h"
#include "mixing_n_ary_tree_time_scale_transition_node.h"
#include "mixing_n_ary_tree_visitor.h"
#include "mixing_n_ary_tree_double_dispatcher.h"

using vostok::animation::mixing::n_ary_tree_visitor;
using vostok::animation::mixing::n_ary_tree_double_dispatcher;
using vostok::animation::mixing::n_ary_tree_animation_node;
using vostok::animation::mixing::n_ary_tree_weight_node;
using vostok::animation::mixing::n_ary_tree_time_scale_node;
using vostok::animation::mixing::n_ary_tree_addition_node;
using vostok::animation::mixing::n_ary_tree_subtraction_node;
using vostok::animation::mixing::n_ary_tree_multiplication_node;
using vostok::animation::mixing::n_ary_tree_weight_transition_node;
using vostok::animation::mixing::n_ary_tree_time_scale_transition_node;

void n_ary_tree_weight_transition_node::accept	( n_ary_tree_visitor& visitor )
{
	visitor.visit		( *this );
}

void n_ary_tree_weight_transition_node::accept	( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_base_node& node )
{
	node.visit			( dispatcher, *this );
}

void n_ary_tree_weight_transition_node::visit	( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_animation_node& node )
{
	dispatcher.dispatch	( node, *this );
}

void n_ary_tree_weight_transition_node::visit	( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_weight_node& node )
{
	dispatcher.dispatch	( node, *this );
}

void n_ary_tree_weight_transition_node::visit	( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_time_scale_node& node )
{
	dispatcher.dispatch	( node, *this );
}

void n_ary_tree_weight_transition_node::visit	( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_addition_node& node )
{
	dispatcher.dispatch	( node, *this );
}

void n_ary_tree_weight_transition_node::visit	( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_subtraction_node& node )
{
	dispatcher.dispatch	( node, *this );
}

void n_ary_tree_weight_transition_node::visit	( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_multiplication_node& node )
{
	dispatcher.dispatch	( node, *this );
}

void n_ary_tree_weight_transition_node::visit	( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_weight_transition_node& node )
{
	dispatcher.dispatch	( node, *this );
}

void n_ary_tree_weight_transition_node::visit	( n_ary_tree_double_dispatcher& dispatcher, n_ary_tree_time_scale_transition_node& node )
{
	dispatcher.dispatch	( node, *this );
}