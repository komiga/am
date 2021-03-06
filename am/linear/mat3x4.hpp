/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief 3x4 matrix.
*/

#pragma once

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tmat3x4.hpp"
#include "./vec3.hpp"
#include "./vec4.hpp"

#ifdef AM_CONFIG_IMPLICIT_LINEAR_INTERFACE
	#include "../detail/linear/tmat3x4_interface.hpp"
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
	@defgroup mat3x4 3x4 matrix
	@{
*/

#if (AM_CONFIG_MATRIX_TYPES) & AM_FLAG_TYPE_FLOAT
	/**
		3x4 floating-point matrix.

		@sa AM_CONFIG_MATRIX_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using mat3x4 = detail::linear::tmat3x4<component_float>;
#endif

/** @} */ // end of doc-group mat3x4
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace am
} // namespace linear
