/**
@file arithmetic_types.hpp
@brief Arithmetic types.

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_ARITHMETIC_TYPES_HPP_
#define AM_ARITHMETIC_TYPES_HPP_

#include "./config.hpp"

namespace am {

/**
	@defgroup arithmetic_types Arithmetic types
	@details
	Integer types are defined to strictly-sized 16-, 32-, and 64-bit arithmetic types (respective to: low, medium, high).
	Medium- and high-precision floating-point types are defined to system single- and double-precision types, respectively (which usually correspond to IEEE-754 32- and 64-bit floating-point types, respectively).
	
	Note that no low-precision floating-point type is provided.
	@{
*/

/** Medium-precision floating-point. */
typedef float mediump_float;
/** High-precision floating-point. */
typedef double highp_float;

/** Low-precision signed integer. */
typedef int16_t lowp_int;
/** Medium-precision signed integer. */
typedef int32_t mediump_int;
/** High-precision signed integer. */
typedef int64_t highp_int;

/** Low-precision unsigned integer. */
typedef uint16_t lowp_uint;
/** Medium-precision unsigned integer. */
typedef uint32_t mediump_uint;
/** High-precision unsigned integer. */
typedef uint64_t highp_uint;

#ifdef DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

/**
	Component floating-point type specified by @c AM_CONFIG_FLOAT_PRECISION.
	@sa AM_CONFIG_FLOAT_PRECISION
*/
typedef configuration_dependent component_float;
/**
	Component signed integer type specified by @c AM_CONFIG_INT_PRECISION.
	@sa AM_CONFIG_INT_PRECISION
*/
typedef configuration_dependent component_int;
/**
	Component unsigned integer type specified by @c AM_CONFIG_UINT_PRECISION.
	@sa AM_CONFIG_UINT_PRECISION
*/
typedef configuration_dependent component_uint;

#else // -

// NOTE: Config validation guaranteed via config.hpp

#if		AM_CONFIG_FLOAT_PRECISION==AM_PRECISION_MEDIUM
	typedef mediump_float	component_float;
#elif	AM_CONFIG_FLOAT_PRECISION==AM_PRECISION_HIGH
	typedef highp_float		component_float;
#endif

#if		AM_CONFIG_INT_PRECISION==AM_PRECISION_LOW
	typedef lowp_int		component_int;
#elif	AM_CONFIG_INT_PRECISION==AM_PRECISION_MEDIUM
	typedef mediump_int		component_int;
#elif	AM_CONFIG_INT_PRECISION==AM_PRECISION_HIGH
	typedef highp_int		component_int;
#endif

#if		AM_CONFIG_UINT_PRECISION==AM_PRECISION_LOW
	typedef lowp_uint		component_uint;
#elif	AM_CONFIG_UINT_PRECISION==AM_PRECISION_MEDIUM
	typedef mediump_uint	component_uint;
#elif	AM_CONFIG_UINT_PRECISION==AM_PRECISION_HIGH
	typedef highp_uint		component_uint;
#endif

#endif // DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

/** @} */ // end of doc-group arithmetic_types

} // namespace am

#endif // AM_ARITHMETIC_TYPES_HPP_
