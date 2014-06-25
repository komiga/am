/**
@file linear/mat4x3.hpp
@brief 4x3 matrix.

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../config.hpp"
#include "../arithmetic_types.hpp"
#include "../detail/linear/tmat4x3.hpp"
#include "./vec3.hpp"
#include "./vec4.hpp"

#ifdef AM_CONFIG_LINEAR_IMPLICIT_INTERFACE
	#include "../detail/linear/tmat4x3_interface.hpp"
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
	@defgroup mat4x3 4x3 matrix
	@{
*/

#if AM_CONFIG_MATRIX_TYPES & AM_FLAG_TYPE_FLOAT
	/**
		4x3 floating-point matrix.

		@sa AM_CONFIG_MATRIX_TYPES,
			AM_CONFIG_FLOAT_PRECISION
	*/
	using mat4x3 = detail::linear::tmat4x3<component_float>;
#endif

/** @} */ // end of doc-group mat4x3
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace am
} // namespace linear
