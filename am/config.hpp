/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief Configuration.
*/

#pragma once

#include <cstdint>

#include "./config_values.hpp"

namespace am {

/**
	@defgroup config Configuration
	@details
	Configuration defines:

	- %AM_CONFIG_IMPLICIT_LINEAR_INTERFACE
	- %AM_CONFIG_FLOAT_PRECISION
	- %AM_CONFIG_INT_PRECISION
	- %AM_CONFIG_UINT_PRECISION
	- %AM_CONFIG_VECTOR_TYPES
	- %AM_CONFIG_MATRIX_TYPES
	@{
*/

/** @cond INTERNAL */
#define AM_CFG_MSG(msg_) "AM config: " msg_
#define AM_ERR_MSG(msg_) "AM error: " msg_
#define AM_CONFIG_ASSERT(expr_, msg_) \
	static_assert((expr_), AM_CFG_MSG(msg_))
#define AM_STATIC_ASSERT(expr_, msg_) \
	static_assert((expr_), AM_ERR_MSG(msg_))
//#define AM_STATIC_ERROR(msg_) static_assert(false, AM_ERR_MSG(msg_))
/** @endcond */

/**
	@name Linear configuration
	@{
*/

#ifdef DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI
	/**
		Whether linear type headers should implicitly include
		their corresponding interface headers when they are not
		needed by the header.

		This is not defined by default.
	*/
	#define AM_CONFIG_IMPLICIT_LINEAR_INTERFACE
#endif

#ifdef DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

/**
	Precision for AM-supplied floating-point type specializations.

	@remarks Defaults to @c AM_PRECISION_MEDIUM.

	@sa AM_CONFIG_VECTOR_TYPES,
		AM_CONFIG_MATRIX_TYPES
*/
#define AM_CONFIG_FLOAT_PRECISION AM_PRECISION_MEDIUM
/**
	Precision for AM-supplied signed integer type specializations.

	@remarks Defaults to @c AM_PRECISION_MEDIUM.

	@sa AM_CONFIG_VECTOR_TYPES,
		AM_CONFIG_MATRIX_TYPES
*/
#define AM_CONFIG_INT_PRECISION AM_PRECISION_MEDIUM
/**
	Precision for AM-supplied unsigned integer type specializations.

	@remarks Defaults to @c AM_PRECISION_MEDIUM.

	@sa AM_CONFIG_VECTOR_TYPES,
		AM_CONFIG_MATRIX_TYPES
*/
#define AM_CONFIG_UINT_PRECISION AM_PRECISION_MEDIUM

#else // -

#ifndef AM_CONFIG_FLOAT_PRECISION
	#define AM_CONFIG_FLOAT_PRECISION AM_PRECISION_MEDIUM
#else
	AM_CONFIG_ASSERT(
		// half-floats not supported
		AM_PRECISION_LOW  <  AM_CONFIG_FLOAT_PRECISION &&
		AM_PRECISION_HIGH >= AM_CONFIG_FLOAT_PRECISION,
		"AM_CONFIG_FLOAT_PRECISION invalid or not supported (only"
		" medium- and high-precision floats are available)"
	);
#endif

#ifndef AM_CONFIG_INT_PRECISION
	#define AM_CONFIG_INT_PRECISION AM_PRECISION_MEDIUM
#else
	AM_CONFIG_ASSERT(
		AM_PRECISION_LOW  <= AM_CONFIG_INT_PRECISION &&
		AM_PRECISION_HIGH >= AM_CONFIG_INT_PRECISION,
		"AM_CONFIG_INT_PRECISION invalid"
	);
#endif

#ifndef AM_CONFIG_UINT_PRECISION
	#define AM_CONFIG_UINT_PRECISION AM_PRECISION_MEDIUM
#else
	AM_CONFIG_ASSERT(
		AM_PRECISION_LOW  <= AM_CONFIG_UINT_PRECISION &&
		AM_PRECISION_HIGH >= AM_CONFIG_UINT_PRECISION,
		"AM_CONFIG_UINT_PRECISION invalid"
	);
#endif

#endif // DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

#ifdef DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

/**
	Vector types to declare.

	When including vector headers (e.g., <linear/vec2.hpp>),
	the specializations declared depend on the set flags.

	For example: with only @c AM_FLAG_TYPE_FLOAT set, @c vec1,
	@c vec2, etc., will be defined; if @c AM_FLAG_TYPE_INT were
	included, @c ivec1, @c ivec2, etc., would also be defined.

	@remarks Defaults to @c AM_FLAG_TYPE_would also be defined.

	@par
	@remarks Defaults to @c AM_FLAG_TYPE_ALL.

	@sa AM_CONFIG_MATRIX_TYPES,
		AM_FLAG_TYPE_NONE,
		AM_FLAG_TYPE_FLOAT,
		AM_FLAG_TYPE_INT,
		AM_FLAG_TYPE_UINT,
		AM_FLAG_TYPE_ALL
*/
#define AM_CONFIG_VECTOR_TYPES AM_FLAG_TYPE_ALL

/**
	Matrix types to declare.

	When including matrix headers (e.g., <linear/mat2x2.hpp>),
	the specializations declared depend on the set flags.

	With @c AM_FLAG_TYPE_FLOAT set, @c mat2x2, @c mat3x3, etc.,
	will be defined; no other flags, apart from @c AM_FLAG_TYPE_NONE,
	are valid.

	@remarks Defaults to @c AM_FLAG_TYPE_FLOAT.

	@sa AM_CONFIG_VECTOR_TYPES,
		AM_FLAG_TYPE_NONE,
		AM_FLAG_TYPE_FLOAT
*/
#define AM_CONFIG_MATRIX_TYPES AM_FLAG_TYPE_FLOAT

#else // -

#ifndef AM_CONFIG_VECTOR_TYPES
	#define AM_CONFIG_VECTOR_TYPES AM_FLAG_TYPE_ALL
#else
	AM_CONFIG_ASSERT(
		0 == ((AM_CONFIG_VECTOR_TYPES) & ~(AM_FLAG_TYPE_ALL)),
		"AM_CONFIG_VECTOR_TYPES has invalid flags set"
	);
#endif

#ifndef AM_CONFIG_MATRIX_TYPES
	#define AM_CONFIG_MATRIX_TYPES AM_FLAG_TYPE_FLOAT
#else
	AM_CONFIG_ASSERT(
		0 == ((AM_CONFIG_MATRIX_TYPES) & ~(AM_FLAG_TYPE_FLOAT)),
		"AM_CONFIG_MATRIX_TYPES has invalid flags set"
	);
#endif

#endif // DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI

/** @} */ // end of name-group Linear configuration
/** @} */ // end of doc-group config

} // namespace am
