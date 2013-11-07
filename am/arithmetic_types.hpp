/**
@file arithmetic_types.hpp
@brief Arithmetic types.

@author Tim Howard
@copyright 2012-2013 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_ARITHMETIC_TYPES_HPP_
#define AM_ARITHMETIC_TYPES_HPP_

#include "./config.hpp"

namespace am {

/**
	@defgroup arithmetic_types Arithmetic types
	@details

	Integer types are defined to strictly-sized 16-, 32-,
	and 64-bit arithmetic types (respective to: low, medium, high).
	Medium- and high-precision floating-point types are defined to
	system single- and double-precision types, respectively (which
	usually correspond to IEEE-754 32- and 64-bit floating-point
	types, respectively).

	Note that no low-precision floating-point type is provided.
	@{
*/

/** Medium-precision floating-point. */
using mediump_float = float;
/** High-precision floating-point. */
using highp_float = double;

/** Low-precision signed integer. */
using lowp_int = int16_t;
/** Medium-precision signed integer. */
using mediump_int = int32_t;
/** High-precision signed integer. */
using highp_int = int64_t;

/** Low-precision unsigned integer. */
using lowp_uint = uint16_t;
/** Medium-precision unsigned integer. */
using mediump_uint = uint32_t;
/** High-precision unsigned integer. */
using highp_uint = uint64_t;

#ifdef DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

/**
	Component floating-point type specified by @c AM_CONFIG_FLOAT_PRECISION.

	@sa AM_CONFIG_FLOAT_PRECISION
*/
using component_float = configuration_dependent;
/**
	Component signed integer type specified by @c AM_CONFIG_INT_PRECISION.

	@sa AM_CONFIG_INT_PRECISION
*/
using component_int = configuration_dependent;
/**
	Component unsigned integer type specified by @c AM_CONFIG_UINT_PRECISION.

	@sa AM_CONFIG_UINT_PRECISION
*/
using component_uint = configuration_dependent;

#else // -

// NOTE: Config validation guaranteed via config.hpp

#if		AM_CONFIG_FLOAT_PRECISION==AM_PRECISION_MEDIUM
	using component_float = mediump_float;
#elif	AM_CONFIG_FLOAT_PRECISION==AM_PRECISION_HIGH
	using component_float = highp_float;
#endif

#if		AM_CONFIG_INT_PRECISION==AM_PRECISION_LOW
	using component_int = lowp_int;
#elif	AM_CONFIG_INT_PRECISION==AM_PRECISION_MEDIUM
	using component_int = mediump_int;
#elif	AM_CONFIG_INT_PRECISION==AM_PRECISION_HIGH
	using component_int = highp_int;
#endif

#if		AM_CONFIG_UINT_PRECISION==AM_PRECISION_LOW
	using component_uint = lowp_uint;
#elif	AM_CONFIG_UINT_PRECISION==AM_PRECISION_MEDIUM
	using component_uint = mediump_uint;
#elif	AM_CONFIG_UINT_PRECISION==AM_PRECISION_HIGH
	using component_uint = highp_uint;
#endif

#endif // DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

/** @} */ // end of doc-group arithmetic_types

} // namespace am

#endif // AM_ARITHMETIC_TYPES_HPP_
