/**
@file detail/linear/tmat3x3_interface.hpp
@brief 3x3 matrix (interface).

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../../config.hpp"
#include "./tmat3x3.hpp"

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
	@addtogroup mat3x3
	@{
*/

/** @cond INTERNAL */
template<class T>
struct tmat3x3<T>::operations {
	using type = typename tmat3x3<T>::type;
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
			m.data[0].x, m.data[1].x, m.data[2].x,
			m.data[0].y, m.data[1].y, m.data[2].y,
			m.data[0].z, m.data[1].z, m.data[2].z};
	}
	static value_type
	determinant(
		type_cref m
	) {
		return
			m.data[0].x * (m.data[1].y * m.data[2].z - m.data[2].y * m.data[1].z) - // a(ei - fh) -
			m.data[1].x * (m.data[0].y * m.data[2].z - m.data[2].y * m.data[0].z) + // b(di - fg) +
			m.data[2].x * (m.data[0].y * m.data[1].z - m.data[1].y * m.data[0].z) ; // c(dh - eg)
	}
	static type
	inverse(
		type_cref m
	) {
		/*
			a b c
			d e f
			g h i
		*/
		value_type const
		c01{m.data[1].y * m.data[2].z - m.data[2].y * m.data[1].z}, // (ei - fh)
		c02{m.data[0].y * m.data[2].z - m.data[2].y * m.data[0].z}, // (fg - di)
		c03{m.data[0].y * m.data[1].z - m.data[1].y * m.data[0].z}, // (dh - eg)
		c11{m.data[1].x * m.data[2].z - m.data[2].x * m.data[1].z}, // (ch - bi)
		c12{m.data[0].x * m.data[2].z - m.data[2].x * m.data[0].z}, // (ai - cg)
		c13{m.data[0].x * m.data[1].z - m.data[1].x * m.data[0].z}, // (bg - ah)
		c21{m.data[1].x * m.data[2].y - m.data[2].x * m.data[1].y}, // (bf - ce)
		c22{m.data[0].x * m.data[2].y - m.data[2].x * m.data[0].y}, // (cd - af)
		c23{m.data[0].x * m.data[1].y - m.data[1].x * m.data[0].y}; // (ae - bd)

		value_type const det=
			m.data[0].x * c01 - // a(ei - fh) -
			m.data[1].x * c02 + // b(di - fg) +
			m.data[2].x * c03 ; // c(dh - eg)
		return type{
			 c01 / det, // (ei - fh)
			-c02 / det, //-(di - fg)
			 c03 / det, // (dh - eg)
			-c11 / det, //-(bi - ch)
			 c12 / det, // (ai - cg)
			-c13 / det, //-(ah - bg)
			 c21 / det, // (bf - ce)
			-c22 / det, //-(af - cd)
			 c23 / det};// (ae - bd)
	}

	static type
	postfix_increment(
		type_cref m
	) {
		return type{
			m.data[0]++,
			m.data[1]++,
			m.data[2]++};
	}
	static type
	postfix_decrement(
		type_cref m
	) {
		return type{
			m.data[0]--,
			m.data[1]--,
			m.data[2]--};
	}

	static type
	unary_negative(
		type_cref m
	) {
		return type{
			-m.data[0],
			-m.data[1],
			-m.data[2]};
	}

	static type
	scalar_add(
		type_cref m,
		value_cref s
	) {
		return type{
			m.data[0] + s,
			m.data[1] + s,
			m.data[2] + s};
	}

	static type
	add(
		type_cref m,
		type_cref n
	) {
		return type{
			m.data[0] + n.data[0],
			m.data[1] + n.data[1],
			m.data[2] + n.data[2]};
	}

	static type
	scalar_subtract_rhs(
		type_cref m,
		value_cref s
	) {
		return type{
			m.data[0] - s,
			m.data[1] - s,
			m.data[2] - s};
	}
	static type
	scalar_subtract_lhs(
		type_cref m,
		value_cref s
	) {
		return type{
			s - m.data[0],
			s - m.data[1],
			s - m.data[2]};
	}

	static type
	subtract(
		type_cref m,
		type_cref n
	) {
		return type{
			m.data[0] - n.data[0],
			m.data[1] - n.data[1],
			m.data[2] - n.data[2]};
	}

	static type
	scalar_multiply(
		type_cref m,
		value_cref s
	) {
		return type{
			m.data[0] * s,
			m.data[1] * s,
			m.data[2] * s};
	}

	static col_type
	row_multiply(
		type_cref m,
		row_cref v
	) {
		return col_type{
			m.data[0].x * v.x + m.data[1].x * v.y + m.data[2].x * v.z,
			m.data[0].y * v.x + m.data[1].y * v.y + m.data[2].y * v.z,
			m.data[0].z * v.x + m.data[1].z * v.y + m.data[2].z * v.z};
	}
	static row_type
	col_multiply(
		type_cref m,
		col_cref v
	) {
		return row_type{
			m.data[0].x * v.x + m.data[0].y * v.y + m.data[0].z * v.z,
			m.data[1].x * v.x + m.data[1].y * v.y + m.data[1].z * v.z,
			m.data[2].x * v.x + m.data[2].y * v.y + m.data[2].z * v.z};
	}

	static tmat2x3<T>
	multiply(
		type_cref m,
		tmat2x3<T> const& n
	) {
		return tmat2x3<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y + m.data[2].x * n.data[0].z,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y + m.data[2].y * n.data[0].z,
			m.data[0].z * n.data[0].x + m.data[1].z * n.data[0].y + m.data[2].z * n.data[0].z,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y + m.data[2].x * n.data[1].z,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y + m.data[2].y * n.data[1].z,
			m.data[0].z * n.data[1].x + m.data[1].z * n.data[1].y + m.data[2].z * n.data[1].z};
	}
	static type
	multiply(
		type_cref m,
		type_cref n
	) {
		return type{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y + m.data[2].x * n.data[0].z,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y + m.data[2].y * n.data[0].z,
			m.data[0].z * n.data[0].x + m.data[1].z * n.data[0].y + m.data[2].z * n.data[0].z,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y + m.data[2].x * n.data[1].z,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y + m.data[2].y * n.data[1].z,
			m.data[0].z * n.data[1].x + m.data[1].z * n.data[1].y + m.data[2].z * n.data[1].z,
			m.data[0].x * n.data[2].x + m.data[1].x * n.data[2].y + m.data[2].x * n.data[2].z,
			m.data[0].y * n.data[2].x + m.data[1].y * n.data[2].y + m.data[2].y * n.data[2].z,
			m.data[0].z * n.data[2].x + m.data[1].z * n.data[2].y + m.data[2].z * n.data[2].z};
	}
	static tmat4x3<T>
	multiply(
		type_cref m,
		tmat4x3<T> const& n
	) {
		return tmat4x3<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y + m.data[2].x * n.data[0].z,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y + m.data[2].y * n.data[0].z,
			m.data[0].z * n.data[0].x + m.data[1].z * n.data[0].y + m.data[2].z * n.data[0].z,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y + m.data[2].x * n.data[1].z,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y + m.data[2].y * n.data[1].z,
			m.data[0].z * n.data[1].x + m.data[1].z * n.data[1].y + m.data[2].z * n.data[1].z,
			m.data[0].x * n.data[2].x + m.data[1].x * n.data[2].y + m.data[2].x * n.data[2].z,
			m.data[0].y * n.data[2].x + m.data[1].y * n.data[2].y + m.data[2].y * n.data[2].z,
			m.data[0].z * n.data[2].x + m.data[1].z * n.data[2].y + m.data[2].z * n.data[2].z,
			m.data[0].x * n.data[3].x + m.data[1].x * n.data[3].y + m.data[2].x * n.data[3].z,
			m.data[0].y * n.data[3].x + m.data[1].y * n.data[3].y + m.data[2].y * n.data[3].z,
			m.data[0].z * n.data[3].x + m.data[1].z * n.data[3].y + m.data[2].z * n.data[3].z};
	}

	static type scalar_divide_rhs(
		type_cref m,
		value_cref s
	) {
		return type{
			m.data[0] / s,
			m.data[1] / s,
			m.data[2] / s};
	}
	static type scalar_divide_lhs(
		type_cref m,
		value_cref s
	) {
		return type{
			s / m.data[0],
			s / m.data[1],
			s / m.data[2]};
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
};
/** @endcond */ // INTERNAL

/** @name mat3x3 comparison operators */ /// @{
	/**
		Equivalence operator.

		@returns
		- @c true if the two matrices are equal,
		- @c false if they are not.
	*/
	template<class T>
	inline bool
	operator==(
		tmat3x3<T> const& m,
		tmat3x3<T> const& n
	) {
		return
			m.data[0] == n.data[0] &&
			m.data[1] == n.data[1] &&
			m.data[2] == n.data[2];
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
		tmat3x3<T> const& m,
		tmat3x3<T> const& n
	) {
		return
			m.data[0] != n.data[0] ||
			m.data[1] != n.data[1] ||
			m.data[2] != n.data[2];
	}
/// @}

/** @name mat3x3 arithmetic assignment operators */ /// @{
	/**
		Add value to all components.

		@returns @a m after operation.
	*/
	template<class T, class U>
	tmat3x3<T>&
	operator+=(
		tmat3x3<T>& m,
		U const& s
	) {
		m.data[0] += T(s);
		m.data[1] += T(s);
		m.data[2] += T(s);
		return m;
	}
	/**
		Add matrix.

		@returns @a m after operation.
	*/
	template<class T, class U>
	tmat3x3<T>&
	operator+=(
		tmat3x3<T>& m,
		tmat3x3<U> const& n
	) {
		m.data[0] += n.data[0];
		m.data[1] += n.data[1];
		m.data[2] += n.data[2];
		return m;
	}

	/**
		Subtract value from all components.

		@returns @a m after operation.
	*/
	template<class T, class U>
	tmat3x3<T>&
	operator-=(
		tmat3x3<T>& m,
		U const& s
	) {
		m.data[0] -= T(s);
		m.data[1] -= T(s);
		m.data[2] -= T(s);
		return m;
	}
	/**
		Subtract matrix.

		@returns @a m after operation.
	*/
	template<class T, class U>
	tmat3x3<T>&
	operator-=(
		tmat3x3<T>& m,
		tmat3x3<U> const& n
	) {
		m.data[0] -= n.data[0];
		m.data[1] -= n.data[1];
		m.data[2] -= n.data[2];
		return m;
	}

	/**
		Multiply by scalar.

		@returns @a m after operation.
	*/
	template<class T, class U>
	tmat3x3<T>&
	operator*=(
		tmat3x3<T>& m,
		U const& s
	) {
		m.data[0] *= T(s);
		m.data[1] *= T(s);
		m.data[2] *= T(s);
		return m;
	}
	/**
		Multiply by matrix (proper product).

		@returns @a m after operation.
	*/
	template<class T, class U>
	tmat3x3<T>&
	operator*=(
		tmat3x3<T>& m,
		tmat3x3<U> const& n
	) {
		return (m = m * n);
	}

	/**
		Divide all components by value.

		@returns @a m after operation.
	*/
	template<class T, class U>
	tmat3x3<T>&
	operator/=(
		tmat3x3<T>& m,
		U const& s
	) {
		m.data[0] /= T(s);
		m.data[1] /= T(s);
		m.data[2] /= T(s);
		return m;
	}
	/**
		Divide by matrix (proper quotient).

		@returns @a m after operation.
	*/
	template<class T, class U>
	tmat3x3<T>&
	operator/=(
		tmat3x3<T>& m,
		tmat3x3<U> const& n
	) {
		return (m = m / n);
	}
/// @}

/** @name mat3x3 increment and decrement operators */ /// @{
	/**
		Prefix increment.

		@returns @a m after operation.
	*/
	template<class T>
	tmat3x3<T>&
	operator++(
		tmat3x3<T>& m
	) {
		++m.data[0];
		++m.data[1];
		++m.data[2];
		return m;
	}

	/**
		Prefix decrement.

		@returns @a m after operation.
	*/
	template<class T>
	tmat3x3<T>&
	operator--(
		tmat3x3<T>& m
	) {
		--m.data[0];
		--m.data[1];
		--m.data[2];
		return m;
	}

	/**
		Matrix postfix increment.

		@returns New matrix with @c m+1.
	*/
	template<class T>
	inline tmat3x3<T>
	operator++(
		tmat3x3<T> const& m,
		signed
	) {
		return tmat3x3<T>::operations::postfix_increment(m);
	}

	/**
		Matrix postfix decrement.

		@returns New matrix with @c m-1.
	*/
	template<class T>
	inline tmat3x3<T>
	operator--(
		tmat3x3<T> const& m,
		signed
	) {
		return tmat3x3<T>::operations::postfix_decrement(m);
	}
/// @}

/** @name mat3x3 unary operators */ /// @{
	/**
		Matrix unary plus.

		@returns New matrix with exact value of @a m.
	*/
	template<class T>
	inline tmat3x3<T>
	operator+(
		tmat3x3<T> const& m
	) {
		return tmat3x3<T>{m};
	}

	/**
		Matrix unary minus.

		@returns New matrix with @c -m.
	*/
	template<class T>
	inline tmat3x3<T>
	operator-(
		tmat3x3<T> const& m
	) {
		return tmat3x3<T>::operations::unary_negative(m);
	}
/// @}

/** @name mat3x3 arithmetic operators */ /// @{
	/**
		Matrix right-hand value addition (component-wise).

		@returns New matrix with @a m plus @a s.
	*/
	template<class T>
	inline tmat3x3<T>
	operator+(
		tmat3x3<T> const& m,
		T const& s
	) {
		return tmat3x3<T>::operations::scalar_add(m, s);
	}
	/**
		Matrix left-hand value addition (component-wise).

		@returns New matrix with @a s plus @a m.
	*/
	template<class T>
	inline tmat3x3<T>
	operator+(
		T const& s,
		tmat3x3<T> const& m
	) {
		return tmat3x3<T>::operations::scalar_add(m, s);
	}
	/**
		Matrix addition.

		@returns New matrix with @a m plus @a n.
	*/
	template<class T>
	inline tmat3x3<T>
	operator+(
		tmat3x3<T> const& m,
		tmat3x3<T> const& n
	) {
		return tmat3x3<T>::operations::add(m, n);
	}

	/**
		Matrix right-hand value subtraction (component-wise).

		@returns New matrix with @a m minus @a s.
	*/
	template<class T>
	inline tmat3x3<T>
	operator-(
		tmat3x3<T> const& m,
		T const& s
	) {
		return tmat3x3<T>::operations::scalar_subtract_rhs(m, s);
	}
	/**
		Matrix left-hand value subtraction (component-wise).

		@returns New matrix with @a s minus @a m.
	*/
	template<class T>
	inline tmat3x3<T>
	operator-(
		T const& s,
		tmat3x3<T> const& m
	) {
		return tmat3x3<T>::operations::scalar_subtract_lhs(m, s);
	}
	/**
		Matrix subtraction.

		@returns New matrix with @a m minus @a n.
	*/
	template<class T>
	inline tmat3x3<T>
	operator-(
		tmat3x3<T> const& m,
		tmat3x3<T> const& n
	) {
		return tmat3x3<T>::operations::subtract(m, n);
	}

	/**
		Matrix right-hand scalar multiplication (component-wise).

		@returns New matrix with @a m times @a s.
	*/
	template<class T>
	inline tmat3x3<T>
	operator*(
		tmat3x3<T> const& m,
		T const& s
	) {
		return tmat3x3<T>::operations::scalar_multiply(m, s);
	}
	/**
		Matrix left-hand scalar multiplication (component-wise).

		@returns New matrix with @a s times @a m.
	*/
	template<class T>
	inline tmat3x3<T>
	operator*(
		T const& s,
		tmat3x3<T> const& m
	) {
		return tmat3x3<T>::operations::scalar_multiply(m, s);
	}
	/**
		Matrix right-hand (row) vector multiplication (proper product).

		@returns New column vector with @a m times @a v.
	*/
	template<class T>
	inline typename tmat3x3<T>::col_type
	operator*(
		tmat3x3<T> const& m,
		typename tmat3x3<T>::row_type const& v
	) {
		return tmat3x3<T>::operations::row_multiply(m, v);
	}
	/**
		Matrix left-hand (column) vector multiplication (proper product).

		@returns New row vector with @a v times @a m.
	*/
	template<class T>
	inline typename tmat3x3<T>::row_type
	operator*(
		typename tmat3x3<T>::col_type const& v,
		tmat3x3<T> const& m
	) {
		return tmat3x3<T>::operations::col_multiply(m, v);
	}
	/**
		Matrix multiplication (proper product).

		@returns New matrix with @a m times @a n.
	*/
	template<class T>
	inline tmat2x3<T>
	operator*(
		tmat3x3<T> const& m,
		tmat2x3<T> const& n
	) {
		return tmat3x3<T>::operations::multiply(m, n);
	}
	/**
		Matrix multiplication (proper product).

		@returns New matrix with @a m times @a n.
	*/
	template<class T>
	inline tmat3x3<T>
	operator*(
		tmat3x3<T> const& m,
		tmat3x3<T> const& n
	) {
		return tmat3x3<T>::operations::multiply(m, n);
	}
	/**
		Matrix multiplication (proper product).

		@returns New matrix with @a m times @a n.
	*/
	template<class T>
	inline tmat4x3<T>
	operator*(
		tmat3x3<T> const& m,
		tmat4x3<T> const& n
	) {
		return tmat3x3<T>::operations::multiply(m, n);
	}

	/**
		Matrix right-hand value division (component-wise).

		@returns New matrix with @a m divided by @a s.
	*/
	template<class T>
	inline tmat3x3<T>
	operator/(
		tmat3x3<T> const& m,
		T const& s
	) {
		return tmat3x3<T>::operations::scalar_divide_rhs(m, s);
	}
	/**
		Matrix left-hand value division (component-wise).

		@returns New matrix with @a s divided by @a m.
	*/
	template<class T>
	inline tmat3x3<T>
	operator/(
		T const& s,
		tmat3x3<T> const& m
	) {
		return tmat3x3<T>::operations::scalar_divide_lhs(m, s);
	}
	/**
		Matrix right-hand vector division (proper quotient).

		@returns New column vector with @a m divided by @a v.
	*/
	template<class T>
	inline typename tmat3x3<T>::col_type
	operator/(
		tmat3x3<T> const& m,
		typename tmat3x3<T>::row_type const& v
	) {
		return tmat3x3<T>::operations::row_divide(m, v);
	}
	/**
		Matrix left-hand vector division (proper quotient).

		@returns New row vector with @a v divided by @a m.
	*/
	template<class T>
	inline typename tmat3x3<T>::row_type
	operator/(
		typename tmat3x3<T>::col_type const& v,
		tmat3x3<T> const& m
	) {
		return tmat3x3<T>::operations::col_divide(m, v);
	}
	/**
		Matrix division (proper quotient).

		@returns New matrix with @a m divided by @a n.
	*/
	template<class T>
	inline tmat3x3<T>
	operator/(
		tmat3x3<T> const& m,
		tmat3x3<T> const& n
	) {
		return tmat3x3<T>::operations::divide(m, n);
	}
/// @}

/** @} */ // end of doc-group mat3x3
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am
