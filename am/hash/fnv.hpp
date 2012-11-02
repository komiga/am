/**
@file hash/fnv.hpp
@brief FNV.
@defgroup fnv FNV

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
Although the AM implementations are under the MIT license, the FNV algorithms themselves are in the public domain and no copyright is claimed on them.
*/

#ifndef AM_HASH_FNV_HPP_
#define AM_HASH_FNV_HPP_

#include "../config.hpp"
#include "./common.hpp"
#include "../detail/hash/fnv_impl.hpp"

namespace am {
namespace hash {

/**
	@addtogroup hash
	@{
*/
/**
	@addtogroup fnv
	@details
	The Fowler-Noll-Vo (FNV) hashing algorithm has three popular variations:

	- <strong>FNV-0</strong>: the first FNV (using an @c offset_basis of @c 0 -- given a 0-length input, it will return @c 0);
	- <strong>FNV-1</strong>: the same as FNV-0, but with an arbitrary non-zero @c offset_basis;
	- <strong>FNV-1a</strong>: an alternate version of FNV-1 with the multiplication and XOR operations swapped; this alternate version has much better avalanche characteristics.

	FNV-1a is the recommended variation.

	@remark Only sizes @c HashSize::HS32 and @c HashSize::HS64 are supplied.
	@{
*/

/** @cond INTERNAL */
#define AM_HASH_FNV_RESTRICT_SIZE(hash_size)\
		AM_STATIC_ASSERT(\
			HashSize::HS32<=hash_size &&\
			HashSize::HS64>=hash_size,\
			"FNV is not implemented for hash sizes less than 32 bits or greater than 64 bits");
/** @endcond */

/**
	Calculate the FNV-0 hash of a sequence of bytes.
	@returns The FNV-0 hash of the given data.
	@tparam S Hash size.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
*/
template<HashSize S, class impl_=detail::hash::fnv0_impl<S> >
inline typename impl_::value_type fnv0(void const* const data, std::size_t const size) {
	AM_HASH_FNV_RESTRICT_SIZE(S);
	return impl_::calc(static_cast<uint8_t const*>(data), size);
}
/**
	Calculate the FNV-0 hash of a standard string.
	@returns The FNV-0 hash of @a str.
	@tparam S Hash size.
	@tparam stringT A standard string type (e.g., @c std::string).
	@param str A string.
*/
template<HashSize S, class stringT, class impl_=detail::hash::fnv0_impl<S> >
inline typename impl_::value_type fnv0_str(stringT const& str) {
	AM_HASH_FNV_RESTRICT_SIZE(S);
	return impl_::calc(reinterpret_cast<uint8_t const*>(str.c_str()), str.size()<<(sizeof(typename stringT::value_type)>>1));
}

/**
	Calculate the FNV-1 hash of a sequence of bytes.
	@returns The FNV-1 hash of the given data.
	@tparam S Hash size.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
*/
template<HashSize S, class impl_=detail::hash::fnv1_impl<S> >
inline typename impl_::value_type fnv1(void const* const data, std::size_t const size) {
	AM_HASH_FNV_RESTRICT_SIZE(S);
	return impl_::calc(static_cast<uint8_t const*>(data), size);
}
/**
	Calculate the FNV-1 hash of a standard string.
	@returns The FNV-1 hash of @a str.
	@tparam S Hash size.
	@tparam stringT A standard string type (e.g., @c std::string).
	@param str A string.
*/
template<HashSize S, class stringT, class impl_=detail::hash::fnv1_impl<S> >
inline typename impl_::value_type fnv1_str(stringT const& str) {
	AM_HASH_FNV_RESTRICT_SIZE(S);
	return impl_::calc(reinterpret_cast<uint8_t const*>(str.c_str()), str.size()<<(sizeof(typename stringT::value_type)>>1));
}

/**
	Calculate the FNV-1a hash of a sequence of bytes.
	@returns The FNV-1a hash of the given data.
	@tparam S Hash size.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
*/
template<HashSize S, class impl_=detail::hash::fnv1a_impl<S> >
inline typename impl_::value_type fnv1a(void const* const data, std::size_t const size) {
	AM_HASH_FNV_RESTRICT_SIZE(S);
	return impl_::calc(static_cast<uint8_t const*>(data), size);
}
/**
	Calculate the FNV-1a hash of a standard string.
	@returns The FNV-1a hash of @a str.
	@tparam S Hash size.
	@tparam stringT A standard string type (e.g., @c std::string).
	@param str A string.
*/
template<HashSize S, class stringT, class impl_=detail::hash::fnv1a_impl<S> >
inline typename impl_::value_type fnv1a_str(stringT const& str) {
	AM_HASH_FNV_RESTRICT_SIZE(S);
	return impl_::calc(reinterpret_cast<uint8_t const*>(str.c_str()), str.size()<<(sizeof(typename stringT::value_type)>>1));
}

/** @} */ // end of doc-group fnv
/** @} */ // end of doc-group hash

} // namespace hash
} // namespace am

#endif // AM_HASH_FNV_HPP_
