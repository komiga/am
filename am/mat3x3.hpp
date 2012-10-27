/**
@file mat3x3.hpp
@brief 3x3 matrix.
@defgroup mat3x3 3x3 matrix

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_MAT3X3_HPP_
#define AM_MAT3X3_HPP_

#include "./config.hpp"
#include "./arithmetic_types.hpp"
#include "./detail/tvec3.hpp"
#include "./detail/tmat3x3.hpp"
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
	@addtogroup mat3x3
	@{
*/

#if AM_CONFIG_MATRIX_TYPES & AM_FLAG_TYPE_FLOAT
	/**
		3x3 floating-point matrix.
		@sa AM_CONFIG_MATRIX_TYPES AM_CONFIG_FLOAT_PRECISION
	*/
	typedef detail::tmat3x3<component_float> mat3x3;
	/**
		3x3 floating-point matrix.
		@sa AM_CONFIG_MATRIX_TYPES AM_CONFIG_FLOAT_PRECISION
	*/
	typedef mat3x3 mat3;
#endif

/** @} */ // end of doc-group mat3x3
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace am

#endif // AM_MAT3X3_HPP_
