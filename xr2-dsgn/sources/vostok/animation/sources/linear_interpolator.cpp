////////////////////////////////////////////////////////////////////////////
//	Created		: 02.04.2010
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <vostok/animation/linear_interpolator.h>
#include "interpolator_comparer.h"
#include <vostok/animation/interpolator_visitor.h>

using vostok::animation::linear_interpolator;
using vostok::animation::interpolator_comparer;
using vostok::animation::interpolator_visitor;
using vostok::animation::instant_interpolator;
using vostok::animation::fermi_interpolator;

float linear_interpolator::interpolated_value	( float current_transition_time ) const
{
	R_ASSERT			( current_transition_time < m_total_transition_time );
	return				current_transition_time/m_total_transition_time;
}

float linear_interpolator::transition_time		( ) const
{
	return				m_total_transition_time;
}

linear_interpolator* linear_interpolator::clone	( vostok::mutable_buffer& buffer ) const
{
	return				clone_impl< linear_interpolator >( buffer );
}

void linear_interpolator::accept				( interpolator_visitor& visitor ) const
{
	visitor.visit		( *this );
}

void linear_interpolator::accept				( interpolator_comparer& dispatcher, base_interpolator const& interpolator ) const
{
	interpolator.visit	( dispatcher, *this );
}

void linear_interpolator::visit					( interpolator_comparer& dispatcher, instant_interpolator const& interpolator ) const
{
	dispatcher.dispatch	( interpolator, *this );
}

void linear_interpolator::visit					( interpolator_comparer& dispatcher, linear_interpolator const& interpolator ) const
{
	dispatcher.dispatch	( interpolator, *this );
}

void linear_interpolator::visit					( interpolator_comparer& dispatcher, fermi_interpolator const& interpolator ) const
{
	dispatcher.dispatch	( interpolator, *this );
}