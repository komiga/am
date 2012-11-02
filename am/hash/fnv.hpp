/**
@file hash/fnv.hpp
@brief FNV.

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
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
	@defgroup fnv FNV
	@details
	The <strong>Fowler-Noll-Vo</strong> (<strong>FNV</strong>) hashing algorithm has three popular versions:

	- <strong>FNV-0</strong>: the first FNV (using an @c offset_basis of @c 0 -- given a 0-length input, it will return @c 0).
	- <strong>FNV-1</strong>: the same as FNV-0, but with an arbitrary non-zero @c offset_basis.
	- <strong>FNV-1a</strong>: an alternate version of FNV-1 with the multiplication and XOR operations swapped; this alternate version has much better avalanche characteristics.

	FNV-1a is the recommended version.

	@remark Only lengths @c HashLength::HL32 and @c HL64 are supplied.
	@note Although the AM implementations are under the MIT license, the FNV algorithms themselves are in the public domain and no copyright is claimed on them.
	@{
*/

/** @cond INTERNAL */
#define AM_HASH_FNV_RESTRICT_LENGTH(hash_length)\
		AM_STATIC_ASSERT(\
			HashLength::HL32<=hash_length &&\
			HashLength::HL64>=hash_length,\
			"FNV is not implemented for hash lengths less than 32 bits or greater than 64 bits");
/** @endcond */

/**
	Calculate the FNV-0 hash of a sequence of bytes.
	@returns The FNV-0 hash of the given data.
	@tparam L Hash length.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
*/
template<HashLength L, class impl_=detail::hash::fnv0_impl<L> >
inline detail::hash::fnv_hash_type<L> fnv0(void const* const data, std::size_t const size) {
	AM_HASH_FNV_RESTRICT_LENGTH(L);
	return impl_::calc(static_cast<uint8_t const*>(data), size);
}
/**
	Calculate the FNV-0 hash of a standard string.
	@returns The FNV-0 hash of @a str.
	@tparam L Hash length.
	@tparam stringT A standard string type (e.g., @c std::string); inferred from @a str.
	@param str A string.
*/
template<HashLength L, class stringT, class impl_=detail::hash::fnv0_impl<L> >
inline detail::hash::fnv_hash_type<L> fnv0_str(stringT const& str) {
	AM_HASH_FNV_RESTRICT_LENGTH(L);
	return impl_::calc(reinterpret_cast<uint8_t const*>(str.c_str()), str.size()<<(sizeof(typename stringT::value_type)>>1));
}

/**
	Calculate the FNV-1 hash of a sequence of bytes.
	@returns The FNV-1 hash of the given data.
	@tparam L Hash length.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
*/
template<HashLength L, class impl_=detail::hash::fnv1_impl<L> >
inline detail::hash::fnv_hash_type<L> fnv1(void const* const data, std::size_t const size) {
	AM_HASH_FNV_RESTRICT_LENGTH(L);
	return impl_::calc(static_cast<uint8_t const*>(data), size);
}
/**
	Calculate the FNV-1 hash of a standard string.
	@returns The FNV-1 hash of @a str.
	@tparam L Hash length.
	@tparam stringT A standard string type (e.g., @c std::string); inferred from @a str.
	@param str A string.
*/
template<HashLength L, class stringT, class impl_=detail::hash::fnv1_impl<L> >
inline detail::hash::fnv_hash_type<L> fnv1_str(stringT const& str) {
	AM_HASH_FNV_RESTRICT_LENGTH(L);
	return impl_::calc(reinterpret_cast<uint8_t const*>(str.c_str()), str.size()<<(sizeof(typename stringT::value_type)>>1));
}

/**
	Calculate the FNV-1a hash of a sequence of bytes.
	@returns The FNV-1a hash of the given data.
	@tparam L Hash length.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
*/
template<HashLength L, class impl_=detail::hash::fnv1a_impl<L> >
inline detail::hash::fnv_hash_type<L> fnv1a(void const* const data, std::size_t const size) {
	AM_HASH_FNV_RESTRICT_LENGTH(L);
	return impl_::calc(static_cast<uint8_t const*>(data), size);
}
/**
	Calculate the FNV-1a hash of a standard string.
	@returns The FNV-1a hash of @a str.
	@tparam L Hash length.
	@tparam stringT A standard string type (e.g., @c std::string); inferred from @a str.
	@param str A string.
*/
template<HashLength L, class stringT, class impl_=detail::hash::fnv1a_impl<L> >
inline detail::hash::fnv_hash_type<L> fnv1a_str(stringT const& str) {
	AM_HASH_FNV_RESTRICT_LENGTH(L);
	return impl_::calc(reinterpret_cast<uint8_t const*>(str.c_str()), str.size()<<(sizeof(typename stringT::value_type)>>1));
}

/** @} */ // end of doc-group fnv
/** @} */ // end of doc-group hash

} // namespace hash
} // namespace am

#endif // AM_HASH_FNV_HPP_
