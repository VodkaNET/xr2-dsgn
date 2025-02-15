////////////////////////////////////////////////////////////////////////////
//	Created		: 27.10.2010
//	Author		: Konstantin Slipchenko
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "mixing_binary_tree_null_weight_searcher.h"
#include <vostok/animation/mixing_binary_tree_animation_node.h>
#include <vostok/animation/mixing_binary_tree_weight_node.h>
#include <vostok/animation/mixing_binary_tree_addition_node.h>
#include <vostok/animation/mixing_binary_tree_subtraction_node.h>
#include <vostok/animation/mixing_binary_tree_multiplication_node.h>

using vostok::animation::mixing::binary_tree_null_weight_searcher;
using vostok::animation::mixing::binary_tree_animation_node;
using vostok::animation::mixing::binary_tree_weight_node;
using vostok::animation::mixing::binary_tree_addition_node;
using vostok::animation::mixing::binary_tree_multiplication_node;
using vostok::animation::mixing::binary_tree_subtraction_node;
using vostok::animation::mixing::binary_tree_binary_operation_node;
using vostok::animation::base_interpolator;

binary_tree_null_weight_searcher::binary_tree_null_weight_searcher	( ) :
	m_result					( false )
{
}

void binary_tree_null_weight_searcher::visit	( binary_tree_animation_node& node )
{
	VOSTOK_UNREFERENCED_PARAMETER	( node );
	UNREACHABLE_CODE			( );
}

void binary_tree_null_weight_searcher::visit	( binary_tree_weight_node& node )
{
	m_result					= m_result || (node.weight() == 0.f);
}

void binary_tree_null_weight_searcher::visit	( binary_tree_addition_node& node )
{
	VOSTOK_UNREFERENCED_PARAMETER	( node );
}

void binary_tree_null_weight_searcher::visit	( binary_tree_subtraction_node& node )
{
	VOSTOK_UNREFERENCED_PARAMETER	( node );
}

void binary_tree_null_weight_searcher::visit	( binary_tree_multiplication_node& node )
{
	node.left().accept			( *this );
	node.right().accept			( *this );
}