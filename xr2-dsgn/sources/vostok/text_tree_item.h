////////////////////////////////////////////////////////////////////////////
//	Created		: 16.08.2011
//	Author		: Sergey Prishchepa
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////
#ifndef TEXT_TREE_ITEM_H_INCLUDED
#define TEXT_TREE_ITEM_H_INCLUDED

#include <vostok/memory_stack_allocator.h>
#include <vostok/intrusive_list.h>

namespace vostok {
namespace strings {

	inline pcstr make_str(pcstr format, ...)
	{
		va_list args;
		va_start(args, format);
		vostok::debug::detail::string_helper h;
		h.appendf_va_list(format, args);
		return h.c_str();
	}
	inline pcstr make_str(bool b) {return b ? "+" : "-";}
	inline pcstr make_str(float f) {return make_str("%f", f);}
	inline pcstr make_str(s32 d) {return make_str("%i", d);}
	inline pcstr make_str(u32 d) {return make_str("%u", d);}
	inline pcstr make_str(vostok::math::float3 v) {return make_str("[%f][%f][%f]", v.x, v.y, v.z);}

	class text_tree_item;

	struct VOSTOK_CORE_API text_tree_item_base
	{
		text_tree_item*		m_next_brother;
	};

	template class VOSTOK_CORE_API intrusive_list<
		text_tree_item_base,
		text_tree_item*,
		&text_tree_item_base::m_next_brother
	>;

	struct text_tree_column_item
	{
		text_tree_column_item	()
			:next(NULL),
			value(NULL)
		{};

		text_tree_column_item*	next;
		pstr					value;
	}; // class text_tree_column_item

	template class VOSTOK_CORE_API intrusive_list<
		text_tree_column_item,
		text_tree_column_item*,
		&text_tree_column_item::next
	>;

	typedef memory::stack_allocator allocator_type;
	typedef intrusive_list<text_tree_column_item, text_tree_column_item*, &text_tree_column_item::next>	column_items_type;
	typedef intrusive_list<text_tree_item_base, text_tree_item*, &text_tree_item_base::m_next_brother>	sub_items_type;

	class VOSTOK_CORE_API text_tree_item: public text_tree_item_base//, private boost::noncopyable 
	{
		struct text_tree_item_deleter: private boost::noncopyable
		{
			text_tree_item_deleter(allocator_type& allocator)
				:m_allocator(allocator)
			{};

			allocator_type& m_allocator;
			void operator ()(text_tree_item* itm)
			{
				itm->clear();
				VOSTOK_DELETE_IMPL(m_allocator, itm);
			}
			void operator ()(text_tree_column_item* itm)
			{
				VOSTOK_FREE_IMPL(m_allocator, itm->value);
				VOSTOK_DELETE_IMPL(m_allocator, itm);
			}
		};
		typedef boost::function<void (text_tree_item*, u32, char)>	functor_type;

	public:
									text_tree_item	(allocator_type& allocator, pcstr value, bool is_page_breaker=false);
									~text_tree_item	();
		void						clear			();
		bool						is_page_breaker	() const {return m_is_page_breaker;};
		bool						get_visibility	() const {return m_is_visible;};
		void						set_visibility	(bool is_visible) {m_is_visible=is_visible;};
		text_tree_item*				find			(pcstr s);
		text_tree_item*				new_child		(pcstr s, bool is_page_breaker=false);
		template <class Type1>
		void						add_column		(Type1 s) {add_column_impl(make_str(s));};
		void						set_name		(pcstr s);
		pcstr						get_name		() {return m_column_value;};
		column_items_type const&	get_columns		() {return m_column_items;};
		sub_items_type const&		get_sub_items	() {return m_sub_items;};
		void						break_page		();

	private:
									text_tree_item	(const text_tree_item&);
		const text_tree_item&		operator=		(const text_tree_item&);
		void						add_column_impl	(pcstr s);

	private:
		sub_items_type		m_sub_items;
		column_items_type	m_column_items;
		pstr				m_column_value;
		allocator_type&		m_allocator;
		bool				m_is_visible;
		const bool			m_is_page_breaker;
	}; // struct text_tree_node
} // namespace strings
} // namespace vostok
#endif // #ifndef TEXT_TREE_ITEM_H_INCLUDED