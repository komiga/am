/**
@file mat4x3.hpp
@brief 4x3 matrix.
@defgroup mat4x3 4x3 matrix

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_MAT4X3_HPP_
#define AM_MAT4X3_HPP_

#include "./config.hpp"
#include "./arithmetic_types.hpp"
#include "./detail/tvec3.hpp"
#include "./detail/tvec4.hpp"
#include "./detail/tmat4x3.hpp"
#include "./matrix_operations.hpp"

namespace am {

/**
	@addtogroup linear
	@{
*/
/**
	@addtogroup matrix
	@{
*/
/**
	@addtogroup mat4x3
	@{
*/

#if AM_CONFIG_MATRIX_TYPES & AM_FLAG_TYPE_FLOAT
	/**
		4x3 floating-point matrix.
		@sa AM_CONFIG_MATRIX_TYPES AM_CONFIG_FLOAT_PRECISION
	*/
	typedef detail::tmat4x3<component_float> mat4x3;
#endif

/** @} */ // end of doc-group mat4x3
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace am

#endif // AM_MAT4X3_HPP_
