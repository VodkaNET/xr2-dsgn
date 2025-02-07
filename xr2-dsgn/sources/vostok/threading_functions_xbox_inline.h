////////////////////////////////////////////////////////////////////////////
//	Created		: 11.12.2009
//	Author		: Sergey Chechin
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef THREADING_FUNCTIONS_XBOX_INLINE_H_INCLUDED
#define THREADING_FUNCTIONS_XBOX_INLINE_H_INCLUDED

namespace vostok {
namespace threading {

VOSTOK_THREADING_INLINE atomic32_value_type interlocked_increment					( atomic32_type& value )
{
	return				InterlockedIncrement( &value );
}

VOSTOK_THREADING_INLINE atomic32_value_type interlocked_decrement					( atomic32_type& value )
{
	return				InterlockedDecrement( &value );
}

VOSTOK_THREADING_INLINE atomic32_value_type interlocked_exchange_add				( atomic32_type& value, atomic32_value_type increment )
{
	return				InterlockedExchangeAdd( &value, increment );
}

VOSTOK_THREADING_INLINE atomic32_value_type	interlocked_exchange_sub			( atomic32_type& value,  atomic32_value_type  subtract )
{
	return				InterlockedExchangeAdd( &value, -subtract );
}

VOSTOK_THREADING_INLINE atomic32_value_type interlocked_and						( atomic32_type& value, atomic32_value_type mask )
{
	return				InterlockedAnd( &value, mask );
}

VOSTOK_THREADING_INLINE atomic32_value_type interlocked_or						( atomic32_type& value, atomic32_value_type mask )
{
	return				InterlockedOr( &value, mask );
}

VOSTOK_THREADING_INLINE atomic32_value_type interlocked_exchange					( atomic32_type& target, atomic32_value_type value )
{
	return				InterlockedExchange( &target, value );
}

VOSTOK_THREADING_INLINE atomic_ptr_value_type interlocked_exchange_pointer		( atomic_ptr_type& target, atomic_ptr_value_type const value )
{
	return				InterlockedExchangePointer( &target, value );
}

VOSTOK_THREADING_INLINE atomic32_value_type interlocked_compare_exchange			( atomic32_type& target, atomic32_value_type exchange, atomic32_value_type comparand )
{
	return				InterlockedCompareExchange( &target, exchange, comparand);
}

VOSTOK_THREADING_INLINE atomic64_value_type interlocked_compare_exchange			( atomic64_type& target, atomic64_value_type exchange, atomic64_value_type comparand )
{
	return				InterlockedCompareExchange64((__int64*)&target, exchange, comparand);
}

VOSTOK_THREADING_INLINE atomic64_value_type interlocked_exchange					( atomic64_type& target, atomic64_value_type exchange )
{
	return				InterlockedExchange64(&target, exchange);
}

//VOSTOK_THREADING_INLINE atomic64_value_type interlocked_exchange_add				( atomic64_type& target, atomic64_value_type exchange )
//{
//	return				InterlockedExchangeAdd64(&target, exchange);
//}

VOSTOK_THREADING_INLINE atomic_ptr_value_type interlocked_compare_exchange_pointer( atomic_ptr_type& target, atomic_ptr_value_type const exchange, atomic_ptr_value_type const comparand )
{
	return				InterlockedCompareExchangePointer(& target, exchange, comparand);
}

} // namespace threading
} // namespace vostok

#endif // #ifndef THREADING_FUNCTIONS_XBOX_INLINE_H_INCLUDED