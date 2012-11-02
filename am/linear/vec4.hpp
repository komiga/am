/**
@file linear/vec4.hpp
@brief 4-dimensional vector specializations.
@defgroup vec4 4-dimensional vector

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_LINEAR_VEC4_HPP_
#define AM_LINEAR_VEC4_HPP_

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tvec4.hpp"
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
	@addtogroup vec4
	@{
*/

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_FLOAT
	/**
		4-dimensional floating-point vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_FLOAT_PRECISION
	*/
	typedef detail::linear::tvec4<component_float> vec4;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_INT
	/**
		4-dimensional signed integer vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_INT_PRECISION
	*/
	typedef detail::linear::tvec4<component_int> ivec4;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_UINT
	/**
		4-dimensional unsigned integer vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_UINT_PRECISION
	*/
	typedef detail::linear::tvec4<component_uint> uvec4;
#endif

/** @} */ // end of doc-group vec4
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace am
} // namespace linear

#endif // AM_LINEAR_VEC4_HPP_
