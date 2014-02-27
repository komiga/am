/**
@file linear/mat4x4.hpp
@brief 4x4 matrix.

@author Tim Howard
@copyright 2012-2014 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_LINEAR_MAT4X4_HPP_
#define AM_LINEAR_MAT4X4_HPP_

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tvec4.hpp"
#include "../detail/linear/tmat4x4.hpp"
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
	@defgroup mat4x4 4x4 matrix
	@{
*/

#if AM_CONFIG_MATRIX_TYPES & AM_FLAG_TYPE_FLOAT
	/**
		4x4 floating-point matrix.

		@sa AM_CONFIG_MATRIX_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using mat4x4 = detail::linear::tmat4x4<component_float>;
	/**
		4x4 floating-point matrix.

		@sa AM_CONFIG_MATRIX_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using mat4 = mat4x4;
#endif

/** @} */ // end of doc-group mat4x4
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace am
} // namespace linear

#endif // AM_LINEAR_MAT4X4_HPP_
