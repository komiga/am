/**
@file vec3.hpp
@brief 3-dimensional vector specializations.
@defgroup vector Vector types
@defgroup vec3 3-dimensional vector

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_VEC3_HPP_
#define AM_VEC3_HPP_

#include "./config.hpp"
#include "./arithmetic_types.hpp"
#include "./detail/tvec3.hpp"

namespace am {

/**
	@addtogroup vector
	@{
*/
/**
	@addtogroup vec3
	@{
*/

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_FLOAT
	/**
		3-dimensional floating-point vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_FLOAT_PRECISION
	*/
	typedef detail::tvec3<component_float> vec3;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_INT
	/**
		3-dimensional signed integer vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_INT_PRECISION
	*/
	typedef detail::tvec3<component_int> ivec3;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_UINT
	/**
		3-dimensional unsigned integer vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_UINT_PRECISION
	*/
	typedef detail::tvec3<component_uint> uvec3;
#endif

/** @} */ // end of doc-group vec3
/** @} */ // end of doc-group vector

} // namespace am

#endif // AM_VEC3_HPP_
