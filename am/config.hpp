/**
@file config.hpp
@brief Configuration.
@defgroup config Configuration

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_CONFIG_HPP_
#define AM_CONFIG_HPP_

#include <cstdint>

namespace am {

/**
	@addtogroup config
	@details
	Configuration defines:
	
	- %AM_CONFIG_FLOAT_PRECISION
	- %AM_CONFIG_INT_PRECISION
	- %AM_CONFIG_UINT_PRECISION
	- %AM_CONFIG_VECTOR_TYPES
	@{
*/

/** @cond INTERNAL */
#define AM_CFG_MSG(msg_) "AM config: " msg_
#define AM_STATIC_ASSERT(expr_, msg_) static_assert((expr_), AM_CFG_MSG(msg_))
#define AM_CONSTEXPR constexpr
/** @endcond */

/**
	@name Arithmetic type precision
	@{
*/

/** Low arithmetic type precision. */
#define AM_PRECISION_LOW	1
/** Medium arithmetic type precision. */
#define AM_PRECISION_MEDIUM	2
/** High arithmetic type precision. */
#define AM_PRECISION_HIGH	3

#ifdef DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

/**
	Precision for AM-supplied floating-point type specializations.
	@remark Defaults to @c AM_PRECISION_MEDIUM.
	@sa AM_CONFIG_VECTOR_TYPES
*/
#define AM_CONFIG_FLOAT_PRECISION AM_PRECISION_MEDIUM
/**
	Precision for AM-supplied signed integer type specializations.
	@remark Defaults to @c AM_PRECISION_MEDIUM.
	@sa AM_CONFIG_VECTOR_TYPES
*/
#define AM_CONFIG_INT_PRECISION AM_PRECISION_MEDIUM
/**
	Precision for AM-supplied unsigned integer type specializations.
	@remark Defaults to @c AM_PRECISION_MEDIUM.
	@sa AM_CONFIG_VECTOR_TYPES
*/
#define AM_CONFIG_UINT_PRECISION AM_PRECISION_MEDIUM

#else // -

#ifndef AM_CONFIG_FLOAT_PRECISION
	#define AM_CONFIG_FLOAT_PRECISION AM_PRECISION_MEDIUM
#else
	AM_STATIC_ASSERT(
		AM_PRECISION_LOW < AM_CONFIG_FLOAT_PRECISION && // half-floats not supported
		AM_PRECISION_HIGH>=AM_CONFIG_FLOAT_PRECISION,
		"AM_CONFIG_FLOAT_PRECISION invalid or not supported (only medium- and high-precision floats are available)"
	);
#endif

#ifndef AM_CONFIG_INT_PRECISION
	#define AM_CONFIG_INT_PRECISION AM_PRECISION_MEDIUM
#else
	AM_STATIC_ASSERT(
		AM_PRECISION_LOW <=AM_CONFIG_INT_PRECISION &&
		AM_PRECISION_HIGH>=AM_CONFIG_INT_PRECISION,
		"AM_CONFIG_INT_PRECISION invalid"
	);
#endif

#ifndef AM_CONFIG_UINT_PRECISION
	#define AM_CONFIG_UINT_PRECISION AM_PRECISION_MEDIUM
#else
	AM_STATIC_ASSERT(
		AM_PRECISION_LOW <=AM_CONFIG_UINT_PRECISION &&
		AM_PRECISION_HIGH>=AM_CONFIG_UINT_PRECISION,
		"AM_CONFIG_UINT_PRECISION invalid"
	);
#endif

#endif // DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

/** @} */ // end of name-group Arithmetic type precision

/**
	@name Type declarations
	@{
*/

/** No types. */
#define AM_FLAG_TYPE_NONE	0
/** Floating-point type. */
#define AM_FLAG_TYPE_FLOAT	1<<0
/** Signed integer type. */
#define AM_FLAG_TYPE_INT	1<<1
/** Unsigned integer type. */
#define AM_FLAG_TYPE_UINT	1<<2
/** All types. */
#define AM_FLAG_TYPE_ALL	(AM_FLAG_TYPE_FLOAT|AM_FLAG_TYPE_INT|AM_FLAG_TYPE_UINT)

#ifdef DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

/**
	Vector types to declare.
	When including vector headers (e.g., <vec1.hpp>), the typedefs declared depend on the set flags.
	For example: with @c AM_FLAG_TYPE_FLOAT only @c vec1, @a vec2, etc., will be defined; if @c AM_FLAG_TYPE_INT were included, @c ivec1, @c ivec2, etc., would also be defined.
	@remark Defaults to @c AM_FLAG_TYPE_ALL.
	@sa AM_FLAG_TYPE_NONE, AM_FLAG_TYPE_FLOAT, AM_FLAG_TYPE_INT, AM_FLAG_TYPE_UINT, AM_FLAG_TYPE_ALL
*/
#define AM_CONFIG_VECTOR_TYPES AM_FLAG_TYPE_ALL

#else // -

#ifndef AM_CONFIG_VECTOR_TYPES
	#define AM_CONFIG_VECTOR_TYPES AM_FLAG_TYPE_ALL
#else
	AM_STATIC_ASSERT(
		0==(AM_CONFIG_VECTOR_TYPES&~(AM_FLAG_TYPE_ALL)),
		"AM_CONFIG_VECTOR_TYPES has invalid bits"
	);
#endif

#endif // DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

/** @} */ // end of name-group Type declarations
/** @} */ // end of doc-group config

} // namespace am

#endif // AM_CONFIG_HPP_
