/**
@file mat4x4.hpp
@brief 4x4 matrix.
@defgroup mat4x4 4x4 matrix

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_MAT4X4_HPP_
#define AM_MAT4X4_HPP_

#include "./config.hpp"
#include "./arithmetic_types.hpp"
#include "./detail/tvec4.hpp"
#include "./detail/tmat4x4.hpp"
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
	@addtogroup mat4x4
	@{
*/

#if AM_CONFIG_MATRIX_TYPES & AM_FLAG_TYPE_FLOAT
	/**
		4x4 floating-point matrix.
		@sa AM_CONFIG_MATRIX_TYPES AM_CONFIG_FLOAT_PRECISION
	*/
	typedef detail::tmat4x4<component_float> mat4x4;
	/**
		4x4 floating-point matrix.
		@sa AM_CONFIG_MATRIX_TYPES AM_CONFIG_FLOAT_PRECISION
	*/
	typedef mat4x4 mat4;
#endif

/** @} */ // end of doc-group mat4x4
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace am

#endif // AM_MAT4X4_HPP_
