/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief 4-dimensional vector.
*/

#pragma once

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tvec4.hpp"

#ifdef AM_CONFIG_IMPLICIT_LINEAR_INTERFACE
	#include "../detail/linear/tvec4_interface.hpp"
#endif

namespace am {
namespace linear {

/**
	@addtogroup linear
	@{
*/
/**
	@addtogroup vector
	@{
*/
/**
	@defgroup vec4 4-dimensional vector
	@{
*/

#if (AM_CONFIG_VECTOR_TYPES) & AM_FLAG_TYPE_FLOAT
	/**
		4-dimensional floating-point vector.

		@sa AM_CONFIG_VECTOR_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using vec4 = detail::linear::tvec4<component_float>;
#endif

#if (AM_CONFIG_VECTOR_TYPES) & AM_FLAG_TYPE_INT
	/**
		4-dimensional signed integer vector.

		@sa AM_CONFIG_VECTOR_TYPES,
			AM_CONFIG_INT_PRECISION
	*/
	using ivec4 = detail::linear::tvec4<component_int>;
#endif

#if (AM_CONFIG_VECTOR_TYPES) & AM_FLAG_TYPE_UINT
	/**
		4-dimensional unsigned integer vector.

		@sa AM_CONFIG_VECTOR_TYPES,
			AM_CONFIG_UINT_PRECISION
	*/
	using uvec4 = detail::linear::tvec4<component_uint>;
#endif

/** @} */ // end of doc-group vec4
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace am
} // namespace linear
