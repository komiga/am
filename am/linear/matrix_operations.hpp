/**
@file linear/matrix_operations.hpp
@brief Matrix operations.

@author Tim Howard
@copyright 2012-2013 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_LINEAR_MATRIX_OPERATIONS_HPP_
#define AM_LINEAR_MATRIX_OPERATIONS_HPP_

#include "../config.hpp"
#include "../detail/linear/type_traits.hpp"

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
	Get the transpose a matrix.

	@remarks Defined for all matrix types.
	@returns The transpose of @a m.
	@tparam conType A specialized matrix type.
	@param m Matrix.
*/
template<class conType>
inline typename conType::transpose_type transpose(conType const& m) {
	AM_STATIC_ASSERT(detail::linear::is_matrix<conType>::value,
		"conType must be a matrix");
	return conType::operations::transpose(m);
}

/**
	Calculate the determinant of a (square) matrix.

	@remarks Only defined for the following matrix types:
	- @c mat2x2
	- @c mat3x3
	- @c mat4x4
	@returns The determinant of @a m.
	@tparam conType A specialized square matrix type.
	@param m Matrix.
*/
template<class conType>
inline typename conType::value_type determinant(conType const& m) {
	AM_STATIC_ASSERT(detail::linear::is_square_matrix<conType>::value,
		"conType must be a square matrix");
	return conType::operations::determinant(m);
}

/**
	Calculate the inverse of a (square) matrix.

	@warning The values in the resultant matrix are undefined if @a m is
	singular.
	@remarks Only defined for the following matrix types:
	- @c mat2x2
	- @c mat3x3
	- @c mat4x4
	@returns The inverse of @a m.
	@tparam conType A specialized square matrix type.
	@param m Matrix.
*/
template<class conType>
inline conType inverse(conType const& m) {
	AM_STATIC_ASSERT(detail::linear::is_square_matrix<conType>::value,
		"conType must be a square matrix");
	return conType::operations::inverse(m);
}

/** @} */ // end of doc-group matrix_ops
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace am
} // namespace linear

#endif // AM_LINEAR_MATRIX_OPERATIONS_HPP_
