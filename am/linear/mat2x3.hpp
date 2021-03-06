/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief 2x3 matrix.
*/

#pragma once

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tmat2x3.hpp"
#include "./vec2.hpp"
#include "./vec3.hpp"

#ifdef AM_CONFIG_IMPLICIT_LINEAR_INTERFACE
	#include "../detail/linear/tmat2x3_interface.hpp"
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
	@defgroup mat2x3 2x3 matrix
	@{
*/

#if (AM_CONFIG_MATRIX_TYPES) & AM_FLAG_TYPE_FLOAT
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
