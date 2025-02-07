////////////////////////////////////////////////////////////////////////////
//	Created 	: 02.02.2008
//	Author		: Konstantin Slipchenko
//	Description : collision element 
////////////////////////////////////////////////////////////////////////////
#ifndef VOSTOK_PHYSICS_COLLIDE_ELEMENT_H_INCLUDED
#define VOSTOK_PHYSICS_COLLIDE_ELEMENT_H_INCLUDED

#include "shell_element.h"

namespace vostok {
namespace collision {
	struct on_contact;
	class geometry_instance;
} // namespace collision
} // namespace vostok

class island;
class collide_element;
class collide_element_iterface;
class body;

class collide_element:
	public shell_element
{
protected:
	collision::geometry_instance	&m_geometry_instance;

protected:
	virtual	void	generate_contacts	( vostok::collision::on_contact& c, const vostok::collision::geometry_instance& og  )const	;

protected:
					~collide_element	();
					collide_element		( vostok::collision::geometry_instance	&cf ):	m_geometry_instance( cf )			{ }
private:
	collide_element& operator =			( collide_element const& )		{ UNREACHABLE_CODE(return *this); }

protected:
	virtual	void								render					( render::scene_ptr const& scene, render::debug::renderer& renderer ) const;

private:
	virtual	vostok::collision::geometry_instance	&get_geometry			( )													{ return m_geometry_instance; }
	virtual void								check_collision_validity( )const;
	virtual	math::aabb							&aabb					( math::aabb &box ) const;
	virtual	bool								aabb_test				( math::aabb const& aabb )const;
};


#endif
