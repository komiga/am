/**
@file linear/mat3x2.hpp
@brief 3x2 matrix.

@author Tim Howard
@copyright 2012-2014 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_LINEAR_MAT3X2_HPP_
#define AM_LINEAR_MAT3X2_HPP_

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tvec2.hpp"
#include "../detail/linear/tvec3.hpp"
#include "../detail/linear/tmat3x2.hpp"
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
	@defgroup mat3x2 3x2 matrix
	@{
*/

#if AM_CONFIG_MATRIX_TYPES & AM_FLAG_TYPE_FLOAT
	/**
		3x2 floating-point matrix.

		@sa AM_CONFIG_MATRIX_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using mat3x2 = detail::linear::tmat3x2<component_float>;
#endif

/** @} */ // end of doc-group mat3x2
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace am

#endif // AM_LINEAR_MAT3X2_HPP_
