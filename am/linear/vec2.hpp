/**
@file linear/vec2.hpp
@brief 2-dimensional vector.

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tvec2.hpp"
#include "./vector_operations.hpp"

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

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_FLOAT
	/**
		2-dimensional floating-point vector.

		@sa AM_CONFIG_VECTOR_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using vec2 = detail::linear::tvec2<component_float>;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_INT
	/**
		2-dimensional signed integer vector.

		@sa AM_CONFIG_VECTOR_TYPES,
			AM_CONFIG_INT_PRECISION
	*/
	using ivec2 = detail::linear::tvec2<component_int>;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_UINT
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
