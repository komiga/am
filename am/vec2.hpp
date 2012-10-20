/**
@file vec2.hpp
@brief 2-dimensional vector specializations.
@defgroup vector Vector types
@defgroup vec2 2-dimensional vector

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_VEC2_HPP_
#define AM_VEC2_HPP_

#include "./config.hpp"
#include "./arithmetic_types.hpp"
#include "./detail/tvec2.hpp"

namespace am {

/**
	@addtogroup vector
	@{
*/
/**
	@addtogroup vec2
	@{
*/

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_FLOAT
	/**
		2-dimensional floating-point vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_FLOAT_PRECISION
	*/
	typedef detail::tvec2<component_float> vec2;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_INT
	/**
		2-dimensional signed integer vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_INT_PRECISION
	*/
	typedef detail::tvec2<component_int> ivec2;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_UINT
	/**
		2-dimensional unsigned integer vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_UINT_PRECISION
	*/
	typedef detail::tvec2<component_uint> uvec2;
#endif

/** @} */ // end of doc-group vec2
/** @} */ // end of doc-group vector

} // namespace am

#endif // AM_VEC2_HPP_
