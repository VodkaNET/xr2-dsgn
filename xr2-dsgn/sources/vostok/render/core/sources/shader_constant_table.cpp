////////////////////////////////////////////////////////////////////////////
//	Created		: 07.02.2009
//	Author		: Mykhailo Parfeniuk
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <vostok/render/core/shader_constant_table.h>
#include <vostok/render/core/resource_manager.h>
#include <vostok/render/core/backend.h>

namespace vostok {
namespace render {

namespace res_const_table_predicates {

	inline bool	search	( shader_constant const& c, LPCSTR str)
	{
		return strcmp( c.host().name().c_str(), str) < 0;
	}

	inline bool sort( shader_constant const & c1, shader_constant const & c2)
	{
		return c1.host().name() < c2.host().name();
	}
}

void shader_constant_table::destroy_impl() const
{
	resource_manager::ref().release( this );
}

void shader_constant_table::fatal( LPCSTR msg)
{
	VOSTOK_UNREFERENCED_PARAMETER	( msg);
	FATAL( msg);
}

shader_constant const* shader_constant_table::get( LPCSTR name) const
{
	c_table::const_iterator it = std::lower_bound( m_table.begin(), m_table.end(), name, res_const_table_predicates::search);

	if ( it == m_table.end() || ( 0 != strcmp( it->host().name().c_str(), name)))
		return 0;
	else
		return &*it;
}

shader_constant* shader_constant_table::get( shared_string const& name)
{
	 //linear search, but only ptr-compare
	c_table::iterator it  = m_table.begin(),
						end = m_table.end();

	for ( ; it != end; ++it)
		if ( it->host().name() == name) 
			return &*it;

	return	0;
}

shader_constant* shader_constant_table::get( LPCSTR const name)
{
	c_table::iterator	it  = m_table.begin(),
						end = m_table.end();

	for ( ; it != end; ++it)
		if ( it->host().name() == name) 
			return &*it;


	return	0;
}

bool shader_constant_table::parse_constant_buffer( ID3DShaderReflectionConstantBuffer* src_table, u32 buffer_index)
{
	ASSERT( src_table);

	D3D_SHADER_BUFFER_DESC	shader_buffer_desc;
	HRESULT res = src_table->GetDesc( &shader_buffer_desc);
	CHECK_RESULT( res);

	for ( u32 i = 0; i < shader_buffer_desc.Variables; ++i)
	{
		ID3DShaderReflectionVariable*	variable;
		D3D_SHADER_VARIABLE_DESC		variable_desc;
		ID3DShaderReflectionType*		reflection_type;
		D3D_SHADER_TYPE_DESC			reflection_type_desc;

		variable = src_table->GetVariableByIndex( i);
		ASSERT( variable);

		variable->GetDesc( &variable_desc);
		reflection_type = variable->GetType();
		ASSERT( reflection_type);

		reflection_type->GetDesc( &reflection_type_desc);

		// Name
		LPCSTR	name		=	variable_desc.Name;

		// Type
		enum_constant_type	type = (enum_constant_type)u16( -1);
		switch( reflection_type_desc.Type)
		{
		case D3D10_SVT_FLOAT:
			type = rc_float;
			break;
		case D3D10_SVT_BOOL:
			type	= rc_bool;
			break;
		case D3D10_SVT_INT:
			type	= rc_int;
			break;
		default:
			fatal ( "R_constant_table::parse: unexpected shader variable type.");
		}

		//	Used as byte offset in shader constant buffer
		ASSERT( variable_desc.StartOffset<0x10000);
		u16		r_index			=	u16( variable_desc.StartOffset);
		u16		r_type			=	u16( -1);
		u16		r_array_size	=	u16( reflection_type_desc.Elements);

		// TypeInfo + class
		bool skip					= false;
		switch ( reflection_type_desc.Class)
		{
		case D3D10_SVC_SCALAR:
			r_type = rc_1x1;
			break;
		case D3D10_SVC_VECTOR:
			{
				switch( reflection_type_desc.Columns)
				{
				case 4:
					r_type = rc_1x4;
					break;
				case 3:
					r_type = rc_1x3;
					break;
				case 2:
					r_type = rc_1x2;
					break;
				default:
					fatal( "Vector: 1 components is scalar - there is special case for this!!!!!");
					break;
				}
			}
			break;
		case D3D10_SVC_MATRIX_ROWS:
			{
				switch ( reflection_type_desc.Columns)
				{
				case 4:
					switch ( reflection_type_desc.Rows)
					{
					case 2:
						r_type = rc_2x4;
						break;
					case 3:
						r_type = rc_3x4;
						break;
						/*
						switch ( it->RegisterCount)
						{
						case 2:	r_type	=	RC_2x4;	break;
						case 3: r_type	=	RC_3x4;	break;
						default:	
						fatal		( "MATRIX_ROWS: unsupported number of RegisterCount");
						break;
						}
						break;
						*/
					case 4: 
						r_type = rc_4x4;
						//ASSERT( 4 == it->RegisterCount); 
						break;
					default:
						fatal		( "MATRIX_ROWS: unsupported number of Rows");
						break;
					}
					break;
				default:
					fatal		( "MATRIX_ROWS: unsupported number of Columns");
					break;
				}
			}
			break;
		case D3D10_SVC_MATRIX_COLUMNS:
			fatal		( "Pclass MATRIX_COLUMNS unsupported");
			break;
		case D3D10_SVC_STRUCT:
			fatal		( "Pclass D3DXPC_STRUCT unsupported");
			break;
		case D3D10_SVC_OBJECT:
			{
				//	TODO: DX10: 
				ASSERT( !"Implement shader object parsing.");
			}
			skip		= TRUE;
			break;
		default:
			skip		= TRUE;
			break;
		}
		if ( skip)			continue;


		// We have determined all valuable info, search if shader constant already exists 
		shader_constant *	C		=	get( name);
		if ( !C)	
		{
			// Add shader constant to constants host registry.
			shader_constant_host * const_host = backend::ref().register_constant_host( name, type );
			ASSERT( const_host->type() == rc_INVALID || const_host->type() == type, "A shader constant with a specified name must have type same type in all shaders.");
			
			shader_constant	new_const( *const_host );
	
			new_const.m_slot.m_class_id			= r_type;
			new_const.m_slot.m_buffer_index		= (u16)buffer_index; 
			new_const.m_slot.m_slot_index		= r_index;
			new_const.m_slot.m_array_size		= (r_array_size == 0) ? 1 : r_array_size;

			m_table.push_back		( new_const);
		} 
		else 
		{
			NODEFAULT();
//			ASSERT	( C->type	==	type);
//// 			shader_constant_slot& L	=	C->m_shader_slots[destination];
//// 			L.cls				=	( u8)r_type;
//// 			L.buffer_index		=	( u8)buffer_index;
//// 			L.slot_index		=	r_index;
//
//			C->slot().class_id()				=	( u8)r_type;
//			C->slot.buffer_index		=	( u8)buffer_index;
//			C->slot.slot_index		=	r_index;

		}
	}
	return TRUE;
}


bool shader_constant_table::parse( ID3DShaderReflection* shader_reflection, enum_shader_type destination)
{
	clear();

	ASSERT( destination < enum_shader_types_count);

	D3D_SHADER_DESC	shader_desc;
	shader_reflection->GetDesc( &shader_desc);

	if ( shader_desc.ConstantBuffers)
	{
		m_table.reserve( shader_desc.ConstantBuffers);
		//	Parse single shader_constant table
		ID3DShaderReflectionConstantBuffer *const_buffer=0;

		for ( u16 buff_ind = 0; buff_ind<shader_desc.ConstantBuffers; ++buff_ind)
		{
			const_buffer = shader_reflection->GetConstantBufferByIndex( buff_ind);
			D3D_SHADER_BUFFER_DESC const_buffer_Desc;
			HRESULT res = const_buffer->GetDesc( &const_buffer_Desc);
			CHECK_RESULT( res);

			if ( const_buffer)
			{
				parse_constant_buffer( const_buffer, buff_ind);

				shader_constant_buffer_ptr	temp_buffer = resource_manager::ref().create_constant_buffer( const_buffer_Desc.Name, destination, const_buffer_Desc.Type, const_buffer_Desc.Size);
				m_const_buffers.push_back( temp_buffer);
			}
		}
	}

	std::sort	( m_table.begin(),m_table.end(), res_const_table_predicates::sort);
	return		TRUE;
}


// void shader_constant_table::merge( shader_constant_table* ctable)
// {
// 	if ( 0 == ctable) return;
// 
// 	// Real merge
// 	for ( u32 it = 0; it < ctable->m_table.size(); ++it)
// 	{
// 		shader_constant const & src	= ctable->m_table[it];
// 		shader_constant * c			= get( src.get_name());
// 		if ( !c)	
// 		{
// 			shader_constant c( src);
// 			m_table.push_back( c);
// 		} 
// 		else 
// 		{
// // 			ASSERT( c->m_type == src.m_type);
// // 			c->m_ps_slot	= src.m_ps_slot;
// // 			c->m_vs_slot	= src.m_vs_slot;
// 
// 
// // 			shader_constant_slot& sl	=	( src->m_destination&4)?src->m_samp:( ( src->m_destination&1)?src->m_ps:src->m_vs);
// // 			shader_constant_slot& dl	=	( src->m_destination&4)?c->m_samp:( ( src->m_destination&1)?c->m_ps:c->m_vs);
// // 			dl.m_index			=	sl.m_index;
// // 			dl.m_cls			=	sl.m_cls;
// 		}
// 	}
// 
// 	// Sort
// 	std::sort( m_table.begin(), m_table.end(), res_const_table_predicates::sort);
// 
// #ifdef	USE_DX10
// 	//	TODO:	DX10:	Implement merge with validity check
// 	m_table.reserve( m_table.size() + T->m_table.size());
// 	for ( u32 i = 0; i < T->m_table.size(); ++i)
// 		m_table.push_back( T->m_table[i]);
// #endif	//	USE_DX10
// }

void shader_constant_table::clear()                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
{
	m_table.clear();
	m_const_buffers.clear();
}

bool shader_constant_table::equal( shader_constant_table const & other) const
{
	if ( m_table.size() != other.m_table.size())	return false;
	
	u32 size = m_table.size();
	for ( u32 it=0; it<size; ++it)
	{
		if ( m_table[it] != other.m_table[it] )
			return false;
	}

	return true;
}

void shader_constant_table::apply_bindings( shader_constant_bindings const & bindings)
{
	vector<shader_constant_binding>::const_iterator	it  = bindings.bindings().begin(),
												end = bindings.bindings().end();

	for ( ; it!=end; ++it)
	{
		shader_constant * c = get( it->name() );

		if( c == NULL || c->source().pointer() != NULL ) // Do not overwrite source if it is set.
			continue;

		if( (constant_class_cast_mask & c->slot().class_id()) != (it->class_id() & constant_class_cast_mask))
		{
			ASSERT( (constant_class_cast_mask & c->slot().class_id()) == (it->class_id()&constant_class_cast_mask), 
					"The bound object cant be cast to the corresponding slot!");
			continue;
		}

		if( c->host().type() != it->type())
		{
			ASSERT( c->host().type() == it->type(), "The bound object dosen't have same type as the corresponding slot!");
			continue;
		}

		// Maybe we need ignore the binding in this case
		ASSERT( (c->slot().class_id()&constant_class_size_mask) <= it->source().size(), "The bound object has smaller dimension than the corresponding slot!");
		c->set_source (
			shader_constant_source(
				it->source().pointer(),
				math::min(
					it->source().size(),
					c->slot().class_id() & constant_class_size_mask
				)
			)
		);
		
// 		if ( c && c->m_loader.empty())
// 			c->m_loader = it->second;
	}
}

} // namespace render 
} // namespace vostok 
