/**
@file linear/mat2x2.hpp
@brief 2x2 matrix.

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_LINEAR_MAT2X2_HPP_
#define AM_LINEAR_MAT2X2_HPP_

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tvec2.hpp"
#include "../detail/linear/tmat2x2.hpp"
#include "./matrix_operations.hpp"

namespace am {
namespace linear {

/**
	@addtogroup linear
	@{
*/
/**
	@addtogroup matrix
	@{
*/
/**
	@defgroup mat2x2 2x2 matrix
	@{
*/

#if AM_CONFIG_MATRIX_TYPES & AM_FLAG_TYPE_FLOAT
	/**
		2x2 floating-point matrix.
		@sa AM_CONFIG_MATRIX_TYPES AM_CONFIG_FLOAT_PRECISION
	*/
	typedef detail::linear::tmat2x2<component_float> mat2x2;
	/**
		2x2 floating-point matrix.
		@sa AM_CONFIG_MATRIX_TYPES AM_CONFIG_FLOAT_PRECISION
	*/
	typedef mat2x2 mat2;
#endif

/** @} */ // end of doc-group mat2x2
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace am

#endif // AM_LINEAR_MAT2X2_HPP_
