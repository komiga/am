/**
@file linear/vec3.hpp
@brief 3-dimensional vector.

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tvec3.hpp"
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
	@defgroup vec3 3-dimensional vector
	@{
*/

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_FLOAT
	/**
		3-dimensional floating-point vector.

		@sa AM_CONFIG_VECTOR_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using vec3 = detail::linear::tvec3<component_float>;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_INT
	/**
		3-dimensional signed integer vector.

		@sa AM_CONFIG_VECTOR_TYPES,
			AM_CONFIG_INT_PRECISION
	*/
	using ivec3 = detail::linear::tvec3<component_int>;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_UINT
	/**
		3-dimensional unsigned integer vector.

		@sa AM_CONFIG_VECTOR_TYPES,
			AM_CONFIG_UINT_PRECISION
	*/
	using uvec3 = detail::linear::tvec3<component_uint>;
#endif

/** @} */ // end of doc-group vec3
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace am
