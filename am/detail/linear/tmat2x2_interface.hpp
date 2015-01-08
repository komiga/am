/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief 2x2 matrix (interface).
*/

#pragma once

#include "../../config.hpp"
#include "./tmat2x2.hpp"

namespace am {
namespace detail {
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
	@addtogroup mat2x2
	@{
*/

/** @cond INTERNAL */
template<class T>
struct tmat2x2<T>::operations {
	using type = typename tmat2x2<T>::type;
	using type_cref = type const&;
	using value_type = typename type::value_type;
	using value_cref = typename type::value_type const&;
	using row_type = typename type::row_type;
	using col_type = typename type::col_type;
	using row_cref = row_type const&;
	using col_cref = col_type const&;
	using transpose_type = typename type::transpose_type;

	static transpose_type
	transpose(
		type_cref m
	) {
		return transpose_type{
			m.data[0].x, m.data[1].x,
			m.data[0].y, m.data[1].y};
	}
	static value_type
	determinant(
		type_cref m
	) {
		return
			m.data[0].x * m.data[1].y -
			m.data[1].x * m.data[0].y;
	}
	static type
	inverse(
		type_cref m
	) {
		value_type const det = operations::determinant(m);
		return type{
			 m.data[1].y / det, -m.data[0].y / det,
			-m.data[1].x / det,  m.data[0].x / det};
	}

	static type
	unary_negative(
		type_cref m
	) {
		return type{
			-m.data[0],
			-m.data[1]};
	}

	static type
	scalar_add(
		type_cref m,
		value_cref s
	) {
		return type{
			m.data[0] + s,
			m.data[1] + s};
	}

	static type
	add(
		type_cref m,
		type_cref n
	) {
		return type{
			m.data[0] + n.data[0],
			m.data[1] + n.data[1]};
	}

	static type
	scalar_subtract_rhs(
		type_cref m,
		value_cref s
	) {
		return type{
			m.data[0] - s,
			m.data[1] - s};
	}
	static type
	scalar_subtract_lhs(
		type_cref m,
		value_cref s
	) {
		return type{
			s - m.data[0],
			s - m.data[1]};
	}

	static type
	subtract(
		type_cref m,
		type_cref n
	) {
		return type{
			m.data[0] - n.data[0],
			m.data[1] - n.data[1]};
	}

	static type
	scalar_multiply(
		type_cref m,
		value_cref s
	) {
		return type{
			m.data[0] * s,
			m.data[1] * s};
	}

	static col_type
	row_multiply(
		type_cref m,
		row_cref v
	) {
		return col_type{
			m.data[0].x * v.x + m.data[1].x * v.y,
			m.data[0].y * v.x + m.data[1].y * v.y};
	}
	static row_type
	col_multiply(
		type_cref m,
		col_cref v
	) {
		return row_type{
			m.data[0].x * v.x + m.data[0].y * v.y,
			m.data[1].x * v.x + m.data[1].y * v.y};
	}

	static type
	multiply(
		type_cref m,
		type_cref n
	) {
		return type{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y};
	}
	static tmat3x2<T> multiply(
		type_cref m,
		tmat3x2<T> const& n
	) {
		return tmat3x2<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y,
			m.data[0].x * n.data[2].x + m.data[1].x * n.data[2].y,
			m.data[0].y * n.data[2].x + m.data[1].y * n.data[2].y};
	}
	static tmat4x2<T> multiply(
		type_cref m,
		tmat4x2<T> const& n
	) {
		return tmat4x2<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y,
			m.data[0].x * n.data[2].x + m.data[1].x * n.data[2].y,
			m.data[0].y * n.data[2].x + m.data[1].y * n.data[2].y,
			m.data[0].x * n.data[3].x + m.data[1].x * n.data[3].y,
			m.data[0].y * n.data[3].x + m.data[1].y * n.data[3].y};
	}

	static type
	scalar_divide_rhs(
		type_cref m,
		value_cref s
	) {
		return type{
			m.data[0] / s,
			m.data[1] / s};
	}
	static type
	scalar_divide_lhs(
		type_cref m,
		value_cref s
	) {
		return type{
			s / m.data[0],
			s / m.data[1]};
	}

	static col_type
	row_divide(
		type_cref m,
		row_cref v
	) {
		return row_multiply(operations::inverse(m), v);
	}
	static row_type
	col_divide(
		type_cref m,
		col_cref v
	) {
		return col_multiply(operations::inverse(m), v);
	}

	static type
	divide(
		type_cref m,
		type_cref n
	) {
		return multiply(m, operations::inverse(n));
	}
}; // struct tmat2x2<T>::operations
/** @endcond */ // INTERNAL

/** @name mat2x2 comparison operators */ /// @{
	/**
		Equivalence operator.

		@returns
		- @c true if the two matrices are equal,
		- @c false if they are not.
	*/
	template<class T>
	inline bool
	operator==(
		tmat2x2<T> const& m,
		tmat2x2<T> const& n
	) {
		return
			m.data[0] == n.data[0] &&
			m.data[1] == n.data[1];
	}

	/**
		Non-equivalence operator.

		@returns
		- @c false if the two matrices are equal,
		- @c true if they are not.
	*/
	template<class T>
	inline bool
	operator!=(
		tmat2x2<T> const& m,
		tmat2x2<T> const& n
	) {
		return
			m.data[0] != n.data[0] ||
			m.data[1] != n.data[1];
	}
/// @}

/** @name mat2x2 arithmetic assignment operators */ /// @{
	/**
		Add value to all components.

		@returns @a m after operation.
	*/
	template<class T, class U>
	inline tmat2x2<T>&
	operator+=(
		tmat2x2<T>& m,
		U const& s
	) {
		m.data[0] += T(s);
		m.data[1] += T(s);
		return m;
	}
	/**
		Add matrix.

		@returns @a m after operation.
	*/
	template<class T, class U>
	inline tmat2x2<T>&
	operator+=(
		tmat2x2<T>& m,
		tmat2x2<U> const& n
	) {
		m.data[0] += n.data[0];
		m.data[1] += n.data[1];
		return m;
	}

	/**
		Subtract value from all components.

		@returns @a m after operation.
	*/
	template<class T, class U>
	inline tmat2x2<T>&
	operator-=(
		tmat2x2<T>& m,
		U const& s
	) {
		m.data[0] -= T(s);
		m.data[1] -= T(s);
		return m;
	}
	/**
		Subtract matrix.

		@returns @a m after operation.
	*/
	template<class T, class U>
	inline tmat2x2<T>&
	operator-=(
		tmat2x2<T>& m,
		tmat2x2<U> const& n
	) {
		m.data[0] -= n.data[0];
		m.data[1] -= n.data[1];
		return m;
	}

	/**
		Multiply by scalar.

		@returns @a m after operation.
	*/
	template<class T, class U>
	inline tmat2x2<T>&
	operator*=(
		tmat2x2<T>& m,
		U const& s
	) {
		m.data[0] *= T(s);
		m.data[1] *= T(s);
		return m;
	}
	/**
		Multiply by matrix (proper product).

		@returns @a m after operation.
	*/
	template<class T, class U>
	inline tmat2x2<T>&
	operator*=(
		tmat2x2<T>& m,
		tmat2x2<U> const& n
	) {
		return (m = m * n);
	}

	/**
		Divide all components by value.

		@returns @a m after operation.
	*/
	template<class T, class U>
	inline tmat2x2<T>&
	operator/=(
		tmat2x2<T>& m,
		U const& s
	) {
		m.data[0] /= T(s);
		m.data[1] /= T(s);
		return m;
	}
	/**
		Divide by matrix (proper quotient).

		@returns @a m after operation.
	*/
	template<class T, class U>
	inline tmat2x2<T>&
	operator/=(
		tmat2x2<T>& m,
		tmat2x2<U> const& n
	) {
		return (m = m / n);
	}
/// @}

/** @name mat2x2 increment and decrement operators */ /// @{
	/**
		Prefix increment.

		@returns @a m after operation.
	*/
	template<class T>
	inline tmat2x2<T>&
	operator++(
		tmat2x2<T>& m
	) {
		++m.data[0];
		++m.data[1];
		return m;
	}

	/**
		Prefix decrement.

		@returns @a m after operation.
	*/
	template<class T>
	inline tmat2x2<T>&
	operator--(
		tmat2x2<T>& m
	) {
		--m.data[0];
		--m.data[1];
		return m;
	}

	/**
		Matrix postfix increment.

		@returns @a m before operation.
	*/
	template<class T>
	inline tmat2x2<T>
	operator++(
		tmat2x2<T>& m,
		signed
	) {
		tmat2x2<T> c{m};
		++m;
		return c;
	}

	/**
		Matrix postfix decrement.

		@returns @a m before operation.
	*/
	template<class T>
	inline tmat2x2<T>
	operator--(
		tmat2x2<T>& m,
		signed
	) {
		tmat2x2<T> c{m};
		--m;
		return c;
	}
/// @}

/** @name mat2x2 unary operators */ /// @{
	/**
		Matrix unary plus.

		@returns New matrix with exact value of @a m.
	*/
	template<class T>
	inline tmat2x2<T>
	operator+(
		tmat2x2<T> const& m
	) {
		return tmat2x2<T>{m};
	}

	/**
		Matrix unary minus.

		@returns New matrix with @c -m.
	*/
	template<class T>
	inline tmat2x2<T>
	operator-(
		tmat2x2<T> const& m
	) {
		return tmat2x2<T>::operations::unary_negative(m);
	}
/// @}

/** @name mat2x2 arithmetic operators */ /// @{
	/**
		Matrix right-hand value addition (component-wise).

		@returns New matrix with @a m plus @a s.
	*/
	template<class T>
	inline tmat2x2<T>
	operator+(
		tmat2x2<T> const& m,
		T const& s
	) {
		return tmat2x2<T>::operations::scalar_add(m, s);
	}
	/**
		Matrix left-hand value addition (component-wise).

		@returns New matrix with @a s plus @a m.
	*/
	template<class T>
	inline tmat2x2<T>
	operator+(
		T const& s,
		tmat2x2<T> const& m
	) {
		return tmat2x2<T>::operations::scalar_add(m, s);
	}
	/**
		Matrix addition.

		@returns New matrix with @a m plus @a n.
	*/
	template<class T>
	inline tmat2x2<T>
	operator+(
		tmat2x2<T> const& m,
		tmat2x2<T> const& n
	) {
		return tmat2x2<T>::operations::add(m, n);
	}

	/**
		Matrix right-hand value subtraction (component-wise).

		@returns New matrix with @a m minus @a s.
	*/
	template<class T>
	inline tmat2x2<T>
	operator-(
		tmat2x2<T> const& m,
		T const& s
	) {
		return tmat2x2<T>::operations::scalar_subtract_rhs(m, s);
	}
	/**
		Matrix left-hand value subtraction (component-wise).

		@returns New matrix with @a s minus @a m.
	*/
	template<class T>
	inline tmat2x2<T>
	operator-(
		T const& s,
		tmat2x2<T> const& m
	) {
		return tmat2x2<T>::operations::scalar_subtract_lhs(m, s);
	}
	/**
		Matrix subtraction.

		@returns New matrix with @a m minus @a n.
	*/
	template<class T>
	inline tmat2x2<T>
	operator-(
		tmat2x2<T> const& m,
		tmat2x2<T> const& n
	) {
		return tmat2x2<T>::operations::subtract(m, n);
	}

	/**
		Matrix right-hand scalar multiplication (component-wise).

		@returns New matrix with @a m times @a s.
	*/
	template<class T>
	inline tmat2x2<T>
	operator*(
		tmat2x2<T> const& m,
		T const& s
	) {
		return tmat2x2<T>::operations::scalar_multiply(m, s);
	}
	/**
		Matrix left-hand scalar multiplication (component-wise).

		@returns New matrix with @a s times @a m.
	*/
	template<class T>
	inline tmat2x2<T>
	operator*(
		T const& s,
		tmat2x2<T> const& m
	) {
		return tmat2x2<T>::operations::scalar_multiply(m, s);
	}
	/**
		Matrix right-hand (row) vector multiplication (proper product).

		@returns New column vector with @a m times @a v.
	*/
	template<class T>
	inline typename tmat2x2<T>::col_type
	operator*(
		tmat2x2<T> const& m,
		typename tmat2x2<T>::row_type const& v
	) {
		return tmat2x2<T>::operations::row_multiply(m, v);
	}
	/**
		Matrix left-hand (column) vector multiplication (proper product).

		@returns New row vector with @a v times @a m.
	*/
	template<class T>
	inline typename tmat2x2<T>::row_type
	operator*(
		typename tmat2x2<T>::col_type const& v,
		tmat2x2<T> const& m
	) {
		return tmat2x2<T>::operations::col_multiply(m, v);
	}
	/**
		Matrix multiplication (proper product).

		@returns New matrix with @a m times @a n.
	*/
	template<class T>
	inline tmat2x2<T>
	operator*(
		tmat2x2<T> const& m,
		tmat2x2<T> const& n
	) {
		return tmat2x2<T>::operations::multiply(m, n);
	}
	/**
		Matrix multiplication (proper product).

		@returns New matrix with @a m times @a n.
	*/
	template<class T>
	inline tmat3x2<T>
	operator*(
		tmat2x2<T> const& m,
		tmat3x2<T> const& n
	) {
		return tmat2x2<T>::operations::multiply(m, n);
	}
	/**
		Matrix multiplication (proper product).

		@returns New matrix with @a m times @a n.
	*/
	template<class T>
	inline tmat4x2<T>
	operator*(
		tmat2x2<T> const& m,
		tmat4x2<T> const& n
	) {
		return tmat2x2<T>::operations::multiply(m, n);
	}

	/**
		Matrix right-hand value division (component-wise).

		@returns New matrix with @a m divided by @a s.
	*/
	template<class T>
	inline tmat2x2<T>
	operator/(
		tmat2x2<T> const& m,
		T const& s
	) {
		return tmat2x2<T>::operations::scalar_divide_rhs(m, s);
	}
	/**
		Matrix left-hand value division (component-wise).

		@returns New matrix with @a s divided by @a m.
	*/
	template<class T>
	inline tmat2x2<T>
	operator/(
		T const& s,
		tmat2x2<T> const& m
	) {
		return tmat2x2<T>::operations::scalar_divide_lhs(m, s);
	}
	/**
		Matrix right-hand vector division (proper quotient).

		@returns New column vector with @a m divided by @a v.
	*/
	template<class T>
	inline typename tmat2x2<T>::col_type
	operator/(
		tmat2x2<T> const& m,
		typename tmat2x2<T>::row_type const& v
	) {
		return tmat2x2<T>::operations::row_divide(m, v);
	}
	/**
		Matrix left-hand vector division (proper quotient).

		@returns New row vector with @a v divided by @a m.
	*/
	template<class T>
	inline typename tmat2x2<T>::row_type
	operator/(
		typename tmat2x2<T>::col_type const& v,
		tmat2x2<T> const& m
	) {
		return tmat2x2<T>::operations::col_divide(m, v);
	}
	/**
		Matrix division (proper quotient).

		@returns New matrix with @a m divided by @a n.
	*/
	template<class T>
	inline tmat2x2<T>
	operator/(
		tmat2x2<T> const& m,
		tmat2x2<T> const& n
	) {
		return tmat2x2<T>::operations::divide(m, n);
	}
/// @}

/** @} */ // end of doc-group mat2x2
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am
