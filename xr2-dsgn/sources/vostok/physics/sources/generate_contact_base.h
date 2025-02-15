////////////////////////////////////////////////////////////////////////////
//	Created 	: 03.02.2008
//	Author		: Konstantin Slipchenko
//	Description : gen_contact_base
////////////////////////////////////////////////////////////////////////////

#ifndef VOSTOK_PHYSICS_GENERATE_CONTACT_BASE_H_INCLUDED
#define VOSTOK_PHYSICS_GENERATE_CONTACT_BASE_H_INCLUDED

#include <vostok/collision/contact_info.h>

class island;

struct generate_contact_base:
	public vostok::collision::on_contact,
	private boost::noncopyable
{
	island	&isl;
	bool	reverted;
	u32		number;

	inline									generate_contact_base	( island	&i ): isl( i ), reverted( false ) ,number(0){} ;
	virtual	memory::base_allocator*			alocator				( )	{ return vostok::physics::g_ph_allocator; }
	virtual void							change_order			( );
//#ifdef DEBUG
//	virtual render::debug::renderer&	renderer				( )	;
//#endif // #ifdef DEBUG

}; // struct generate_contact_base

#endif // #ifndef VOSTOK_PHYSICS_GENERATE_CONTACT_BASE_H_INCLUDED