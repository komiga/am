/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief 2x4 matrix.
*/

#pragma once

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tmat2x4.hpp"
#include "./vec2.hpp"
#include "./vec4.hpp"

#ifdef AM_CONFIG_IMPLICIT_LINEAR_INTERFACE
	#include "../detail/linear/tmat2x4_interface.hpp"
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
	@defgroup mat2x4 2x4 matrix
	@{
*/

#if (AM_CONFIG_MATRIX_TYPES) & AM_FLAG_TYPE_FLOAT
	/**
		2x4 floating-point matrix.

		@sa AM_CONFIG_MATRIX_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using mat2x4 = detail::linear::tmat2x4<component_float>;
#endif

/** @} */ // end of doc-group mat2x4
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace am
