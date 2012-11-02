/**
@file linear/vec1.hpp
@brief 1-dimensional vector.

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_LINEAR_VEC1_HPP_
#define AM_LINEAR_VEC1_HPP_

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tvec1.hpp"
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
	@defgroup vec1 1-dimensional vector
	@{
*/

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_FLOAT
	/**
		1-dimensional floating-point vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_FLOAT_PRECISION
	*/
	typedef detail::linear::tvec1<component_float> vec1;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_INT
	/**
		1-dimensional signed integer vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_INT_PRECISION
	*/
	typedef detail::linear::tvec1<component_int> ivec1;
#endif

#if AM_CONFIG_VECTOR_TYPES&AM_FLAG_TYPE_UINT
	/**
		1-dimensional unsigned integer vector.
		@sa AM_CONFIG_VECTOR_TYPES AM_CONFIG_UINT_PRECISION
	*/
	typedef detail::linear::tvec1<component_uint> uvec1;
#endif

/** @} */ // end of doc-group vec1
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace am

#endif // AM_LINEAR_VEC1_HPP_
