/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief 3x3 matrix.
*/

#pragma once

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tmat3x3.hpp"
#include "./vec3.hpp"

#ifdef AM_CONFIG_IMPLICIT_LINEAR_INTERFACE
	#include "../detail/linear/tmat3x3_interface.hpp"
#endif

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
	@defgroup mat3x3 3x3 matrix
	@{
*/

#if (AM_CONFIG_MATRIX_TYPES) & AM_FLAG_TYPE_FLOAT
	/**
		3x3 floating-point matrix.

		@sa AM_CONFIG_MATRIX_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using mat3x3 = detail::linear::tmat3x3<component_float>;
	/**
		3x3 floating-point matrix.

		@sa AM_CONFIG_MATRIX_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using mat3 = mat3x3;
#endif

/** @} */ // end of doc-group mat3x3
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace am
} // namespace linear
