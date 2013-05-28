/**
@file hash/murmur.hpp
@brief Murmur.

@author Tim Howard
@copyright 2012-2013 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_HASH_MURMUR_HPP_
#define AM_HASH_MURMUR_HPP_

#include "../config.hpp"
#include "./common.hpp"
#include "../detail/hash/murmur_impl.hpp"

namespace am {
namespace hash {

/**
	@addtogroup hash
	@{
*/
/**
	@defgroup murmur Murmur
	@details
	The Murmur hashes are general-purpose public domain algorithms
	created by Austin Appleby.

	AM implements <strong>MurmurHash2</strong> (32-bit and both 64-bit
	versions) and <strong>MurmurHash3</strong> (32-bit).

	There are a few quirks of the algorithms and of the AM
	implementations:

	- MurmurHash2 is not portable; it will give different output on
	  different system endians.
	- The two 64-bit MurmurHash2 versions do not produce the same
	  output.
	- The original MurmurHash2 will be used for @c murmur2<HL32>, and
	  MurmurHash64A will be used for @c murmur2<HL64>;
	  see @c murmur2_64b for MurmurHash64B (which only deals
	  in @c HL64).

	@remarks Only lengths @c HashLength::HL32 and @c HashLength::HL64
	are supplied for @c murmur2; only @c HashLength::HL32 is supplied
	for @c murmur3.

	@note Although the AM implementations are under the MIT license,
	the Murmur algorithms themselves are in the public domain and no
	copyright is claimed on them.
	@{
*/

/** @cond INTERNAL */
#define AM_HASH_MURMUR_V2_RESTRICT_LENGTH(hash_length)\
	AM_STATIC_ASSERT(\
		HashLength::HL32<=hash_length &&\
		HashLength::HL64>=hash_length,\
		"MurmurHash2 cannot produce hash lengths"\
		" less than 32 bits or greater than 64 bits"\
	);

#define AM_HASH_MURMUR_V3_RESTRICT_LENGTH(hash_length)\
	AM_STATIC_ASSERT(\
		HashLength::HL32==hash_length,\
		"Only the 32-bit MurmurHash3 is implemented"\
	);
/** @endcond */

/**
	Calculate the MurmurHash2 or MurmurHash64A (MurmurHash2 64-bit
	version for x64 processors) of a sequence of bytes.

	@returns The hash of the given data.
	@tparam L Hash length.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
	@param seed A seed.
*/
template<
	HashLength L,
	class Impl=detail::hash::murmur2_impl<L>
>
inline detail::hash::murmur_hash_type<L> murmur2(
	void const* const data,
	std::size_t const size,
	detail::hash::murmur_hash_type<L> const seed
) {
	AM_HASH_MURMUR_V2_RESTRICT_LENGTH(L);
	return Impl::calc(
		reinterpret_cast<uint8_t const*>(data),
		size,
		seed
	);
}

/**
	Calculate the MurmurHash2 or MurmurHash64A (MurmurHash2 64-bit
	version for x64 processors) of a standard string.

	@returns The hash of @a str.
	@tparam L Hash length.
	@tparam StringT A standard string type (e.g., @c std::string);
	inferred from @a str.
	@param str A string.
	@param seed A seed.
*/
template<HashLength L,
	class StringT,
	class Impl=detail::hash::murmur2_impl<L>
>
inline detail::hash::murmur_hash_type<L>
murmur2_str(
	StringT const& str,
	detail::hash::murmur_hash_type<L> const seed
) {
	AM_HASH_MURMUR_V2_RESTRICT_LENGTH(L);
	return Impl::calc(
		reinterpret_cast<uint8_t const*>(str.c_str()),
		str.size()<<(sizeof(typename StringT::value_type)>>1),
		seed
	);
}

/**
	Calculate the MurmurHash64B (alternate MurmurHash2 64-bit version
	for x86 processors) of a sequence of bytes.

	@returns The hash of the given data.
	@tparam L Hash length.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
	@param seed A seed.
*/
inline uint64_t
murmur2_64b(
	void const* const data,
	std::size_t const size,
	uint64_t const seed
) {
	return detail::hash::murmur2_64b_impl::calc(
		reinterpret_cast<uint8_t const*>(data),
		size,
		seed
	);
}

/**
	Calculate the MurmurHash64B (alternate MurmurHash2 64-bit version
	for x86 processors) of a standard string.

	@returns The hash of @a str.
	@tparam StringT A standard string type (e.g., @c std::string);
	inferred from @a str.
	@param str A string.
	@param seed A seed.
*/
template<class StringT>
inline uint64_t
murmur2_64b_str(
	StringT const& str,
	uint64_t const seed
) {
	return detail::hash::murmur2_64b_impl::calc(
		reinterpret_cast<uint8_t const*>(str.c_str()),
		str.size()<<(sizeof(typename StringT::value_type)>>1),
		seed
	);
}

/**
	Calculate the MurmurHash3 of a sequence of bytes.

	@returns The hash of the given data.
	@tparam L Hash length.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
	@param seed A seed.
*/
template<
	HashLength L,
	class Impl=detail::hash::murmur3_impl<L>
>
inline detail::hash::murmur_hash_type<L>
murmur3(
	void const* const data,
	std::size_t const size,
	detail::hash::murmur_hash_type<L> const seed
) {
	AM_HASH_MURMUR_V3_RESTRICT_LENGTH(L);
	return Impl::calc(
		reinterpret_cast<uint8_t const*>(data),
		size,
		seed
	);
}

/**
	Calculate the MurmurHash3 of a standard string.

	@returns The hash of @a str.
	@tparam L Hash length.
	@tparam StringT A standard string type (e.g., @c std::string);
	inferred from @a str.
	@param str A string.
	@param seed A seed.
*/
template<
	HashLength L,
	class StringT,
	class Impl=detail::hash::murmur3_impl<L>
>
inline detail::hash::murmur_hash_type<L>
murmur3_str(
	StringT const& str,
	detail::hash::murmur_hash_type<L> const seed
) {
	AM_HASH_MURMUR_V3_RESTRICT_LENGTH(L);
	return Impl::calc(
		reinterpret_cast<uint8_t const*>(str.c_str()),
		str.size()<<(sizeof(typename StringT::value_type)>>1),
		seed
	);
}

/**
	Calculate the MurmurHash3 of a C-string (constexpr).

	@returns The hash of the given string.
	@tparam L Hash length.
	@param data C-string.
	@param size Size in bytes of @a data.
	@param seed A seed.
*/
template<
	HashLength L,
	class Impl=detail::hash::murmur3_impl<L>
>
inline AM_CONSTEXPR detail::hash::murmur_hash_type<L>
murmur3_c(
	char const* const data,
	std::size_t const size,
	detail::hash::murmur_hash_type<L> const seed
) {
	AM_HASH_MURMUR_V3_RESTRICT_LENGTH(L);
	return Impl::calc_c_seq(
		data,
		static_cast<uint32_t>(size),
		seed
	);
}

/** @} */ // end of doc-group murmur
/** @} */ // end of doc-group hash

} // namespace hash
} // namespace am

#endif // AM_HASH_MURMUR_HPP_
