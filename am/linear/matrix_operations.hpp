/**
@file linear/matrix_operations.hpp
@brief Matrix operations.

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../config.hpp"
#include "../detail/linear/type_traits.hpp"
#include "./matrix_interface.hpp"

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
	@defgroup matrix_ops Matrix operations
	@{
*/

/**
	Transpose a matrix.

	@remarks Defined for all matrix types.

	@tparam Cons A specialized matrix type.
	@returns The transpose of @a m.
	@param m Matrix.
*/
template<
	class Cons
>
inline typename Cons::transpose_type
transpose(
	Cons const& m
) {
	AM_STATIC_ASSERT(
		detail::linear::is_matrix<Cons>::value,
		"Cons must be a matrix"
	);
	return Cons::operations::transpose(m);
}

/**
	Calculate the determinant of a (square) matrix.

	@remarks Only defined for the following matrix types:
	- @c mat2x2
	- @c mat3x3
	- @c mat4x4

	@tparam Cons A specialized square matrix type.
	@returns The determinant of @a m.
	@param m Matrix.
*/
template<
	class Cons
>
inline detail::linear::value_type<Cons>
determinant(
	Cons const& m
) {
	AM_STATIC_ASSERT(
		detail::linear::is_square_matrix<Cons>::value,
		"Cons must be a square matrix"
	);
	return Cons::operations::determinant(m);
}

/**
	Calculate the inverse of a (square) matrix.

	@warning The values in the resultant matrix are undefined if @a m is
	singular.

	@remarks Only defined for the following matrix types:
	- @c mat2x2
	- @c mat3x3
	- @c mat4x4

	@tparam Cons A specialized square matrix type.
	@returns The inverse of @a m.
	@param m Matrix.
*/
template<
	class Cons
>
inline Cons
inverse(
	Cons const& m
) {
	AM_STATIC_ASSERT(
		detail::linear::is_square_matrix<Cons>::value,
		"Cons must be a square matrix"
	);
	return Cons::operations::inverse(m);
}

/** @} */ // end of doc-group matrix_ops
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace am
} // namespace linear
