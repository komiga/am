/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief 2-dimensional vector.
*/

#pragma once

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tvec2.hpp"

#ifdef AM_CONFIG_IMPLICIT_LINEAR_INTERFACE
	#include "../detail/linear/tvec2_interface.hpp"
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
	@defgroup vec2 2-dimensional vector
	@{
*/

#if (AM_CONFIG_VECTOR_TYPES) & AM_FLAG_TYPE_FLOAT
	/**
		2-dimensional floating-point vector.

		@sa AM_CONFIG_VECTOR_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using vec2 = detail::linear::tvec2<component_float>;
#endif

#if (AM_CONFIG_VECTOR_TYPES) & AM_FLAG_TYPE_INT
	/**
		2-dimensional signed integer vector.

		@sa AM_CONFIG_VECTOR_TYPES,
			AM_CONFIG_INT_PRECISION
	*/
	using ivec2 = detail::linear::tvec2<component_int>;
#endif

#if (AM_CONFIG_VECTOR_TYPES) & AM_FLAG_TYPE_UINT
	/**
		2-dimensional unsigned integer vector.

		@sa AM_CONFIG_VECTOR_TYPES,
			AM_CONFIG_UINT_PRECISION
	*/
	using uvec2 = detail::linear::tvec2<component_uint>;
#endif

/** @} */ // end of doc-group vec2
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace am
} // namespace linear
