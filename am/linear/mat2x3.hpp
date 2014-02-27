/**
@file linear/mat2x3.hpp
@brief 2x3 matrix.

@author Tim Howard
@copyright 2012-2014 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_LINEAR_MAT2X3_HPP_
#define AM_LINEAR_MAT2X3_HPP_

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tvec2.hpp"
#include "../detail/linear/tvec3.hpp"
#include "../detail/linear/tmat2x3.hpp"
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
	@defgroup mat2x3 2x3 matrix
	@{
*/

#if AM_CONFIG_MATRIX_TYPES & AM_FLAG_TYPE_FLOAT
	/**
		2x3 floating-point matrix.

		@sa AM_CONFIG_MATRIX_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using mat2x3 = detail::linear::tmat2x3<component_float>;
#endif

/** @} */ // end of doc-group mat2x3
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace am

#endif // AM_LINEAR_MAT2X3_HPP_
