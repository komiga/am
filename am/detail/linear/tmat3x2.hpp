/**
@file detail/linear/tmat3x2.hpp
@brief 3x2 matrix.

@author Tim Howard
@copyright 2012-2013 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_DETAIL_LINEAR_TMAT3X2_HPP_
#define AM_DETAIL_LINEAR_TMAT3X2_HPP_

#include "../../config.hpp"
#include "./type_traits.hpp"

#include <cassert>
#include <type_traits>

namespace am {
namespace detail {
namespace linear {

// Forward declarations
/** @cond INTERNAL */
template<typename T> struct tvec2;
template<typename T> struct tvec3;
template<typename T> struct tmat2x2;
template<typename T> struct tmat2x3;
template<typename T> struct tmat3x2;
template<typename T> struct tmat3x3;
template<typename T> struct tmat4x2;
template<typename T> struct tmat4x3;

AM_DETAIL_TYPE_IS_MATRIX(tmat3x2);
/** @endcond */

/**
	@addtogroup linear
	@{
*/
/**
	@addtogroup matrix
	@{
*/
/**
	@addtogroup mat3x2
	@{
*/

/**
	Generic 3x2 matrix.
	@tparam T A floating-point type.
*/
template<
	typename T
>
struct tmat3x2 {
public:
	/** @cond INTERNAL */
	AM_STATIC_ASSERT(
		true == std::is_floating_point<T>::value,
		"T must be a floating-point type"
	);
	/** @endcond */

	/** Type of @c *this. */
	using type = tmat3x2<T>;
	/** Type of transpose. */
	using transpose_type = tmat2x3<T>;
	/** Type of components. */
	using value_type = T;
	/** Type of rows. */
	using row_type = tvec3<T>;
	/** Type of columns. */
	using col_type = tvec2<T>;
	/** Size/length type. */
	using size_type = std::size_t;

	/** Dummy enum for constructing uninitialized matrices. */
	enum ctor_no_init {no_init};

	/** Raw columns. */
	col_type data[3];

/** @cond INTERNAL */
	struct operations {
	using type_cref = type const&;
	using value_cref = value_type const&;
	using row_cref = row_type const&;
	using col_cref = col_type const&;

	static transpose_type
	transpose(
		type_cref m
	) {
		return transpose_type{
			m.data[0].x, m.data[1].x, m.data[2].x,
			m.data[0].y, m.data[1].y, m.data[2].y};
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
			m.data[0].y * v.x + m.data[1].y * v.y + m.data[2].y * v.z};
	}
	static row_type
	col_multiply(
		type_cref m,
		col_cref v
	) {
		return row_type{
			m.data[0].x * v.x + m.data[0].y * v.y,
			m.data[1].x * v.x + m.data[1].y * v.y,
			m.data[2].x * v.x + m.data[2].y * v.y};
	}

	static tmat2x2<T>
	multiply(
		type_cref m,
		tmat2x3<T> const& n
	) {
		return tmat2x2<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y + m.data[2].x * n.data[0].z,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y + m.data[2].y * n.data[0].z,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y + m.data[2].x * n.data[1].z,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y + m.data[2].y * n.data[1].z};
	}
	static tmat3x2<T>
	multiply(
		type_cref m,
		tmat3x3<T> const& n
	) {
		return tmat3x2<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y + m.data[2].x * n.data[0].z,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y + m.data[2].y * n.data[0].z,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y + m.data[2].x * n.data[1].z,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y + m.data[2].y * n.data[1].z,
			m.data[0].x * n.data[2].x + m.data[1].x * n.data[2].y + m.data[2].x * n.data[2].z,
			m.data[0].y * n.data[2].x + m.data[1].y * n.data[2].y + m.data[2].y * n.data[2].z};
	}
	static tmat4x2<T>
	multiply(
		type_cref m,
		tmat4x3<T> const& n
	) {
		return tmat4x2<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y + m.data[2].x * n.data[0].z,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y + m.data[2].y * n.data[0].z,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y + m.data[2].x * n.data[1].z,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y + m.data[2].y * n.data[1].z,
			m.data[0].x * n.data[2].x + m.data[1].x * n.data[2].y + m.data[2].x * n.data[2].z,
			m.data[0].y * n.data[2].x + m.data[1].y * n.data[2].y + m.data[2].y * n.data[2].z,
			m.data[0].x * n.data[3].x + m.data[1].x * n.data[3].y + m.data[2].x * n.data[3].z,
			m.data[0].y * n.data[3].x + m.data[1].y * n.data[3].y + m.data[2].y * n.data[3].z};
	}

	static type
	scalar_divide_rhs(
		type_cref m,
		value_cref s
	) {
		return type{
			m.data[0] / s,
			m.data[1] / s,
			m.data[2] / s};
	}
	static type
	scalar_divide_lhs(
		type_cref m,
		value_cref s
	) {
		return type{
			s / m.data[0],
			s / m.data[1],
			s / m.data[2]};
	}
	};
/** @endcond */ // INTERNAL

/** @name Constructors */ /// @{
	/**
		Construct to identity.
	*/
	tmat3x2() : data{
		col_type{T(1), T(0)},
		col_type{T(0), T(1)},
		col_type{T(0), T(0)}
	} {}
	/**
		Construct uninitialized.
	*/
	explicit
	tmat3x2(
		ctor_no_init
	) {}

	/**
		Construct to main diagonal.
		@param s Value.
	*/
	explicit
	tmat3x2(
		value_type const& s
	) : data{
		col_type{s, T(0)},
		col_type{T(0), s},
		col_type{T(0), T(0)}
	} {}
	/**
		Construct to main diagonal.
		@tparam U An arithmetic type.
		@param s Value.
	*/
	template<
		typename U
	>
	explicit
	tmat3x2(
		U const& s
	) : data{
		col_type{T(s), T(0)},
		col_type{T(0), T(s)},
		col_type{T(0), T(0)}
	} {}

	/**
		Construct to values.
		@param x1,y1 First column.
		@param x2,y2 Second column.
		@param x3,y3 Third column.
	*/
	explicit
	tmat3x2(
		value_type const& x1, value_type const& y1,
		value_type const& x2, value_type const& y2,
		value_type const& x3, value_type const& y3
	) : data{
		col_type{x1, y1},
		col_type{x2, y2},
		col_type{x3, y3}
	} {}
	/**
		Construct to values.
		@tparam X1,Y1, X2,Y2, X3,Y3 An arithmetic type.
		@param x1,y1 First column.
		@param x2,y2 Second column.
		@param x3,y3 Third column.
	*/
	template<
		typename X1, typename Y1,
		typename X2, typename Y2,
		typename X3, typename Y3
	>
	explicit
	tmat3x2(
		X1 const& x1, Y1 const& y1,
		X2 const& x2, Y2 const& y2,
		X3 const& x3, Y3 const& y3
	) : data{
		col_type{T(x1), T(y1)},
		col_type{T(x2), T(y2)},
		col_type{T(x3), T(y3)}
	} {}

	/**
		Construct to column vectors.
		@param c1 First column.
		@param c2 Second column.
		@param c3 Third column.
	*/
	explicit
	tmat3x2(
		col_type const& c1,
		col_type const& c2,
		col_type const& c3
	) : data{
		c1,
		c2,
		c3
	} {}
	/**
		Construct to column vectors.
		@tparam C1, C2, C3 An arithmetic type.
		@param c1 First column.
		@param c2 Second column.
		@param c3 Third column.
	*/
	template<
		typename C1,
		typename C2,
		typename C3
	>
	explicit
	tmat3x2(
		tvec2<C1> const& c1,
		tvec2<C2> const& c2,
		tvec2<C3> const& c3
	) : data{
		col_type{c1},
		col_type{c2},
		col_type{c3}
	} {}

	/**
		Construct to matrix.
		@param m Matrix to copy.
	*/
	tmat3x2(
		type const& m
	) : data{
		m.data[0],
		m.data[1],
		m.data[2]
	} {}
	/**
		Construct to matrix.
		@tparam U A floating-point type.
		@param m Matrix to copy.
	*/
	template<
		typename U
	>
	tmat3x2(
		tmat3x2<U> const& m
	) : data{
		col_type{m.data[0]},
		col_type{m.data[1]},
		col_type{m.data[2]}
	} {}
/// @}

/** @name Properties */ /// @{
	/**
		Get number of columns.
		@returns @c 3.
	*/
	static AM_CONSTEXPR size_type
	size() {
		return size_type(3);
	}
	/**
		Get size of column vector.
		@returns @c 2.
	*/
	static AM_CONSTEXPR size_type
	col_size() {
		return col_type::size();
	}
	/**
		Get size of row vector.
		@returns @c 3.
	*/
	static AM_CONSTEXPR size_type
	row_size() {
		return row_type::size();
	}
	/**
		Get column at index.
		@note An assert will catch invalid indices;
		see @c data for completely raw access.
		@returns The column at @a i.
		@param i Index to retrieve.
	*/
	col_type&
	operator[](
		size_type const& i
	) {
		assert(size() > i);
		return data[i];
	}
	/** @copydoc operator[](size_type const&) */
	col_type const&
	operator[](
		size_type const& i
	) const {
		assert(size() > i);
		return data[i];
	}
/// @}

/** @name Comparison operators */ /// @{
	/**
		Equivalence operator.
		@returns
		- @c true if the two matrices are equal,
		- @c false if they are not.
		@param m Matrix to compare with.
	*/
	bool
	operator==(
		type const& m
	) const {
		return
			data[0] == m.data[0] &&
			data[1] == m.data[1] &&
			data[2] == m.data[2];
	}
	/**
		Non-equivalence operator.
		@returns
		- @c false if the two matrices are equal,
		- @c true if they are not.
		@param m Matrix to compare with.
	*/
	bool
	operator!=(
		type const& m
	) const {
		return
			data[0] != m.data[0] ||
			data[1] != m.data[1] ||
			data[2] != m.data[2];
	}
/// @}

/** @name Increment and decrement operators */ /// @{
	/**
		Prefix increment.
		@returns @c *this after operation.
	*/
	type&
	operator++() {
		++data[0];
		++data[1];
		++data[2];
		return *this;
	}
	/**
		Prefix decrement.
		@returns @c *this after operation.
	*/
	type&
	operator--() {
		--data[0];
		--data[1];
		--data[2];
		return *this;
	}
/// @}

/** @name Assignment operators */ /// @{
	/**
		Assign to matrix.
		@returns @c *this after assignment.
		@tparam U A floating-point type.
		@param m Matrix to copy.
	*/
	template<typename U>
	type&
	operator=(
		tmat3x2<U> const& m
	) {
		data[0] = m.data[0];
		data[1] = m.data[1];
		data[2] = m.data[2];
		return *this;
	}
/// @}

/** @name Arithmetic assignment operators */ /// @{
	/**
		Add value to all components.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to add.
	*/
	template<typename U>
	type&
	operator+=(
		U const& s
	) {
		data[0] += T(s);
		data[1] += T(s);
		data[2] += T(s);
		return *this;
	}
	/**
		Add matrix.
		@returns @c *this after operation.
		@tparam U A floating-point type.
		@param m Matrix to add.
	*/
	template<typename U>
	type&
	operator+=(
		tmat3x2<U> const& m
	) {
		data[0] += m.data[0];
		data[1] += m.data[1];
		data[2] += m.data[2];
		return *this;
	}
	/**
		Subtract value from all components.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to subtract.
	*/
	template<typename U>
	type&
	operator-=(
		U const& s
	) {
		data[0] -= T(s);
		data[1] -= T(s);
		data[2] -= T(s);
		return *this;
	}
	/**
		Subtract matrix.
		@returns @c *this after operation.
		@tparam U A floating-point type.
		@param m Matrix to subtract.
	*/
	template<typename U>
	type&
	operator-=(
		tmat3x2<U> const& m
	) {
		data[0] -= m.data[0];
		data[1] -= m.data[1];
		data[2] -= m.data[2];
		return *this;
	}
	/**
		Multiply by scalar.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Scalar.
	*/
	template<typename U>
	type&
	operator*=(
		U const& s
	) {
		data[0] *= T(s);
		data[1] *= T(s);
		data[2] *= T(s);
		return *this;
	}
	/**
		Divide all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to divide by.
	*/
	template<typename U>
	type&
	operator/=(
		U const& s
	) {
		data[0] /= T(s);
		data[1] /= T(s);
		data[2] /= T(s);
		return *this;
	}
/// @}
}; // struct tmat3x2

/** @name mat3x2 increment and decrement operators */ /// @{
	/**
		Matrix postfix increment.
		@returns New matrix with @c m+1.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat3x2<T>
	operator++(
		tmat3x2<T> const& m,
		signed
	) {
		return tmat3x2<T>::operations::postfix_increment(m);
	}
	/**
		Matrix postfix decrement.
		@returns New matrix with @c m-1.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat3x2<T>
	operator--(
		tmat3x2<T> const& m,
		signed
	) {
		return tmat3x2<T>::operations::postfix_decrement(m);
	}
/// @}

/** @name mat3x2 unary operators */ /// @{
	/**
		Matrix unary plus.
		@returns New matrix with exact value of @a m.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat3x2<T>
	operator+(
		tmat3x2<T> const& m
	) {
		return tmat3x2<T>{m};
	}
	/**
		Matrix unary minus.
		@returns New matrix with @c -m.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat3x2<T>
	operator-(
		tmat3x2<T> const& m
	) {
		return tmat3x2<T>::operations::unary_negative(m);
	}
/// @}

/** @name mat3x2 arithmetic operators */ /// @{
	/**
		Matrix right-hand value addition (component-wise).
		@returns New matrix with @a m plus @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Value (right-hand).
	*/
	template<typename T>
	inline tmat3x2<T>
	operator+(
		tmat3x2<T> const& m,
		T const& s
	) {
		return tmat3x2<T>::operations::scalar_add(m, s);
	}
	/**
		Matrix left-hand value addition (component-wise).
		@returns New matrix with @a s plus @a m.
		@tparam T A floating-point type.
		@param s Value (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat3x2<T>
	operator+(
		T const& s,
		tmat3x2<T> const& m
	) {
		return tmat3x2<T>::operations::scalar_add(m, s);
	}
	/**
		Matrix addition.
		@returns New matrix with @a m plus @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat3x2<T>
	operator+(
		tmat3x2<T> const& m,
		tmat3x2<T> const& n
	) {
		return tmat3x2<T>::operations::add(m, n);
	}
	/**
		Matrix right-hand value subtraction (component-wise).
		@returns New matrix with @a m minus @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Value (right-hand).
	*/
	template<typename T>
	inline tmat3x2<T>
	operator-(
		tmat3x2<T> const& m,
		T const& s
	) {
		return tmat3x2<T>::operations::scalar_subtract_rhs(m, s);
	}
	/**
		Matrix left-hand value subtraction (component-wise).
		@returns New matrix with @a s minus @a m.
		@tparam T A floating-point type.
		@param s Value (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat3x2<T>
	operator-(
		T const& s,
		tmat3x2<T> const& m
	) {
		return tmat3x2<T>::operations::scalar_subtract_lhs(m, s);
	}
	/**
		Matrix subtraction.
		@returns New matrix with @a m minus @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat3x2<T>
	operator-(
		tmat3x2<T> const& m,
		tmat3x2<T> const& n
	) {
		return tmat3x2<T>::operations::subtract(m, n);
	}
	/**
		Matrix right-hand scalar multiplication (component-wise).
		@returns New matrix with @a m times @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Scalar (right-hand).
	*/
	template<typename T>
	inline tmat3x2<T>
	operator*(
		tmat3x2<T> const& m,
		T const& s
	) {
		return tmat3x2<T>::operations::scalar_multiply(m, s);
	}
	/**
		Matrix left-hand scalar multiplication (component-wise).
		@returns New matrix with @a s times @a m.
		@tparam T A floating-point type.
		@param s Scalar (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat3x2<T>
	operator*(
		T const& s,
		tmat3x2<T> const& m
	) {
		return tmat3x2<T>::operations::scalar_multiply(m, s);
	}
	/**
		Matrix right-hand (row) vector multiplication (proper product).
		@returns New column vector with @a m times @a v.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param v Vector (right-hand).
	*/
	template<typename T>
	inline typename tmat3x2<T>::col_type
	operator*(
		tmat3x2<T> const& m,
		typename tmat3x2<T>::row_type const& v
	) {
		return tmat3x2<T>::operations::row_multiply(m, v);
	}
	/**
		Matrix left-hand (column) vector multiplication (proper product).
		@returns New row vector with @a v times @a m.
		@tparam T A floating-point type.
		@param v Vector (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline typename tmat3x2<T>::row_type
	operator*(
		typename tmat3x2<T>::col_type const& v,
		tmat3x2<T> const& m
	) {
		return tmat3x2<T>::operations::col_multiply(m, v);
	}
	/**
		Matrix multiplication (proper product).
		@returns New matrix with @a m times @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat2x2<T> operator*(
		tmat3x2<T> const& m,
		tmat2x3<T> const& n
	) {
		return tmat3x2<T>::operations::multiply(m, n);
	}
	/**
		Matrix multiplication (proper product).
		@returns New matrix with @a m times @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat3x2<T>
	operator*(
		tmat3x2<T> const& m,
		tmat3x3<T> const& n
	) {
		return tmat3x2<T>::operations::multiply(m, n);
	}
	/**
		Matrix multiplication (proper product).
		@returns New matrix with @a m times @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat4x2<T> operator*(
		tmat3x2<T> const& m,
		tmat4x3<T> const& n
	) {
		return tmat3x2<T>::operations::multiply(m, n);
	}
	/**
		Matrix right-hand value division (component-wise).
		@returns New matrix with @a m divided by @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Value (right-hand).
	*/
	template<typename T>
	inline tmat3x2<T>
	operator/(
		tmat3x2<T> const& m,
		T const& s
	) {
		return tmat3x2<T>::operations::scalar_divide_rhs(m, s);
	}
	/**
		Matrix left-hand value division (component-wise).
		@returns New matrix with @a s divided by @a m.
		@tparam T A floating-point type.
		@param s Value (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat3x2<T>
	operator/(
		T const& s,
		tmat3x2<T> const& m
	) {
		return tmat3x2<T>::operations::scalar_divide_lhs(m, s);
	}
/// @}

/** @} */ // end of doc-group mat3x2
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am

#endif // AM_DETAIL_LINEAR_TMAT3X2_HPP_
