/**
@file detail/linear/tmat2x4.hpp
@brief 2x4 matrix.

@author Tim Howard
@copyright 2012-2013 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_DETAIL_LINEAR_TMAT2X4_HPP_
#define AM_DETAIL_LINEAR_TMAT2X4_HPP_

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
template<typename T> struct tvec4;
template<typename T> struct tmat2x4;
template<typename T> struct tmat3x2;
template<typename T> struct tmat3x4;
template<typename T> struct tmat4x2;
template<typename T> struct tmat4x4;

AM_DETAIL_TYPE_IS_MATRIX(tmat2x4);
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
	@addtogroup mat2x4
	@{
*/

/**
	Generic 2x4 matrix.
	@tparam T A floating-point type.
*/
template<typename T>
struct tmat2x4 {
public:
	/** @cond INTERNAL */
	AM_STATIC_ASSERT(
		true==std::is_floating_point<T>::value,
		"T must be a floating-point type"
	);
	/** @endcond */

	/** Type of @c *this. */
	typedef tmat2x4<T> type;
	/** Type of transpose. */
	typedef tmat4x2<T> transpose_type;
	/** Type of components. */
	typedef T value_type;
	/** Type of rows. */
	typedef tvec2<T> row_type;
	/** Type of columns. */
	typedef tvec4<T> col_type;
	/** Size/length type. */
	typedef std::size_t size_type;

	/** Dummy enum for constructing uninitialized matrices. */
	enum ctor_no_init {no_init};

	/** Raw columns. */
	col_type data[2];

/** @cond INTERNAL */
	struct operations {
	typedef type const& type_cref;
	typedef value_type const& value_cref;
	typedef row_type const& row_cref;
	typedef col_type const& col_cref;

	static transpose_type transpose(type_cref m) {
		return transpose_type{
			m.data[0].x, m.data[1].x,
			m.data[0].y, m.data[1].y,
			m.data[0].z, m.data[1].z,
			m.data[0].w, m.data[1].w};
	}

	static type
	postfix_increment(
		type_cref m
	) {
		return type{
			m.data[0]++,
			m.data[1]++};
	}
	static type
	postfix_decrement(
		type_cref m
	) {
		return type{
			m.data[0]--,
			m.data[1]--};
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
			m.data[0].y * v.x + m.data[1].y * v.y,
			m.data[0].z * v.x + m.data[1].z * v.y,
			m.data[0].w * v.x + m.data[1].w * v.y};
	}
	static row_type
	col_multiply(
		type_cref m,
		col_cref v
	) {
		return row_type{
			m.data[0].x * v.x + m.data[0].y * v.y + m.data[0].z * v.z + m.data[0].w * v.w,
			m.data[1].x * v.x + m.data[1].y * v.y + m.data[1].z * v.z + m.data[1].w * v.w};
	}

	static type
	multiply(
		type_cref m,
		tmat2x2<T> const& n
	) {
		return type{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y,
			m.data[0].z * n.data[0].x + m.data[1].z * n.data[0].y,
			m.data[0].w * n.data[0].x + m.data[1].w * n.data[0].y,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y,
			m.data[0].z * n.data[1].x + m.data[1].z * n.data[1].y,
			m.data[0].w * n.data[1].x + m.data[1].w * n.data[1].y};
	}
	static tmat3x4<T>
	multiply(
		type_cref m,
		tmat3x2<T> const& n
	) {
		return tmat3x4<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y,
			m.data[0].z * n.data[0].x + m.data[1].z * n.data[0].y,
			m.data[0].w * n.data[0].x + m.data[1].w * n.data[0].y,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y,
			m.data[0].z * n.data[1].x + m.data[1].z * n.data[1].y,
			m.data[0].w * n.data[1].x + m.data[1].w * n.data[1].y,
			m.data[0].x * n.data[2].x + m.data[1].x * n.data[2].y,
			m.data[0].y * n.data[2].x + m.data[1].y * n.data[2].y,
			m.data[0].z * n.data[2].x + m.data[1].z * n.data[2].y,
			m.data[0].w * n.data[2].x + m.data[1].w * n.data[2].y};
	}
	static tmat4x4<T>
	multiply(
		type_cref m,
		tmat4x2<T> const& n
	) {
		return tmat4x4<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y,
			m.data[0].z * n.data[0].x + m.data[1].z * n.data[0].y,
			m.data[0].w * n.data[0].x + m.data[1].w * n.data[0].y,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y,
			m.data[0].z * n.data[1].x + m.data[1].z * n.data[1].y,
			m.data[0].w * n.data[1].x + m.data[1].w * n.data[1].y,
			m.data[0].x * n.data[2].x + m.data[1].x * n.data[2].y,
			m.data[0].y * n.data[2].x + m.data[1].y * n.data[2].y,
			m.data[0].z * n.data[2].x + m.data[1].z * n.data[2].y,
			m.data[0].w * n.data[2].x + m.data[1].w * n.data[2].y,
			m.data[0].x * n.data[3].x + m.data[1].x * n.data[3].y,
			m.data[0].y * n.data[3].x + m.data[1].y * n.data[3].y,
			m.data[0].z * n.data[3].x + m.data[1].z * n.data[3].y,
			m.data[0].w * n.data[3].x + m.data[1].w * n.data[3].y};
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
	};
/** @endcond */ // INTERNAL

/** @name Constructors */ /// @{
	/**
		Construct to identity.
	*/
	tmat2x4() : data{
		col_type{T(1), T(0), T(0), T(0)},
		col_type{T(0), T(1), T(0), T(0)}
	} {}
	/**
		Construct uninitialized.
	*/
	explicit
	tmat2x4(
		ctor_no_init
	) {}

	/**
		Construct to main diagonal.
		@param s Value.
	*/
	explicit
	tmat2x4(
		value_type const& s
	) : data{
		col_type{s, T(0), T(0), T(0)},
		col_type{T(0), s, T(0), T(0)}
	} {}
	/**
		Construct to main diagonal.
		@tparam U An arithmetic type.
		@param s Value.
	*/
	template<typename U>
	explicit
	tmat2x4(
		U const& s
	) : data{
		col_type{T(s), T(0), T(0), T(0)},
		col_type{T(0), T(s), T(0), T(0)}
	} {}

	/**
		Construct to values.
		@param x1,y1,z1,w1 First column.
		@param x2,y2,z2,w2 Second column.
	*/
	explicit
	tmat2x4(
		value_type const& x1, value_type const& y1,
		value_type const& z1, value_type const& w1,
		value_type const& x2, value_type const& y2,
		value_type const& z2, value_type const& w2
	) : data{
		col_type{x1, y1, z1, w1},
		col_type{x2, y2, z2, w2}
	} {}
	/**
		Construct to values.
		@tparam X1,Y1,Z1,W1, X2,Y2,Z2,W2 An arithmetic type.
		@param x1,y1,z1,w1 First column.
		@param x2,y2,z2,w2 Second column.
	*/
	template<
		typename X1, typename Y1, typename Z1, typename W1,
		typename X2, typename Y2, typename Z2, typename W2
	>
	explicit
	tmat2x4(
		X1 const& x1, Y1 const& y1, Z1 const& z1, W1 const& w1,
	 	X2 const& x2, Y2 const& y2, Z2 const& z2, W2 const& w2
	) : data{
		col_type{T(x1), T(y1), T(z1), T(w1)},
		col_type{T(x2), T(y2), T(z2), T(w2)}
	} {}

	/**
		Construct to column vectors.
		@param c1 First column.
		@param c2 Second column.
	*/
	explicit
	tmat2x4(
		col_type const& c1,
		col_type const& c2
	) : data{
		c1,
		c2
	} {}
	/**
		Construct to column vectors.
		@tparam C1, C2 An arithmetic type.
		@param c1 First column.
		@param c2 Second column.
	*/
	template<
		typename C1,
		typename C2
	>
	explicit
	tmat2x4(
		tvec4<C1> const& c1,
		tvec4<C2> const& c2
	) : data{
		col_type{c1},
		col_type{c2}
	} {}

	/**
		Construct to matrix.
		@param m Matrix to copy.
	*/
	tmat2x4(
		type const& m
	) : data{
		m.data[0],
		m.data[1]
	} {}
	/**
		Construct to matrix.
		@tparam U A floating-point type.
		@param m Matrix to copy.
	*/
	template<typename U>
	tmat2x4(
		tmat2x4<U> const& m
	) : data{
		col_type{m.data[0]},
		col_type{m.data[1]}
	} {}
/// @}

/** @name Properties */ /// @{
	/**
		Get number of columns.
		@returns @c 2.
	*/
	static AM_CONSTEXPR size_type
	size() {
		return size_type(2);
	}
	/**
		Get size of column vector.
		@returns @c 4.
	*/
	static AM_CONSTEXPR size_type
	col_size() {
		return col_type::size();
	}
	/**
		Get size of row vector.
		@returns @c 2.
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
		assert(size()>i);
		return data[i];
	}
	/** @copydoc operator[](size_type const&) */
	col_type const&
	operator[](
		size_type const& i
	) const {
		assert(size()>i);
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
			data[0]==m.data[0] &&
			data[1]==m.data[1];
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
			data[0]!=m.data[0] ||
			data[1]!=m.data[1];
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
		tmat2x4<U> const& m
	) {
		data[0]=m.data[0];
		data[1]=m.data[1];
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
		data[0]+=T(s);
		data[1]+=T(s);
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
		tmat2x4<U> const& m
	) {
		data[0]+=m.data[0];
		data[1]+=m.data[1];
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
		data[0]-=T(s);
		data[1]-=T(s);
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
		tmat2x4<U> const& m
	) {
		data[0]-=m.data[0];
		data[1]-=m.data[1];
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
		data[0]*=T(s);
		data[1]*=T(s);
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
		data[0]/=T(s);
		data[1]/=T(s);
		return *this;
	}
/// @}
}; // struct tmat2x4

/** @name mat2x4 increment and decrement operators */ /// @{
	/**
		Matrix postfix increment.
		@returns New matrix with @c m+1.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat2x4<T>
	operator++(
		tmat2x4<T> const& m,
		signed
	) {
		return tmat2x4<T>::operations::postfix_increment(m);
	}
	/**
		Matrix postfix decrement.
		@returns New matrix with @c m-1.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat2x4<T>
	operator--(
		tmat2x4<T> const& m,
		signed
	) {
		return tmat2x4<T>::operations::postfix_decrement(m);
	}
/// @}

/** @name mat2x4 unary operators */ /// @{
	/**
		Matrix unary plus.
		@returns New matrix with exact value of @a m.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat2x4<T>
	operator+(
		tmat2x4<T> const& m
	) {
		return tmat2x4<T>{m};
	}
	/**
		Matrix unary minus.
		@returns New matrix with @c -m.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat2x4<T>
	operator-(
		tmat2x4<T> const& m
	) {
		return tmat2x4<T>::operations::unary_negative(m);
	}
/// @}

/** @name mat2x4 arithmetic operators */ /// @{
	/**
		Matrix right-hand value addition (component-wise).
		@returns New matrix with @a m plus @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Value (right-hand).
	*/
	template<typename T>
	inline tmat2x4<T>
	operator+(
		tmat2x4<T> const& m,
		T const& s
	) {
		return tmat2x4<T>::operations::scalar_add(m, s);
	}
	/**
		Matrix left-hand value addition (component-wise).
		@returns New matrix with @a s plus @a m.
		@tparam T A floating-point type.
		@param s Value (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat2x4<T>
	operator+(
		T const& s,
		tmat2x4<T> const& m
	) {
		return tmat2x4<T>::operations::scalar_add(m, s);
	}
	/**
		Matrix addition.
		@returns New matrix with @a m plus @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat2x4<T>
	operator+(
		tmat2x4<T> const& m,
		tmat2x4<T> const& n
	) {
		return tmat2x4<T>::operations::add(m, n);
	}
	/**
		Matrix right-hand value subtraction (component-wise).
		@returns New matrix with @a m minus @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Value (right-hand).
	*/
	template<typename T>
	inline tmat2x4<T>
	operator-(
		tmat2x4<T> const& m,
		T const& s
	) {
		return tmat2x4<T>::operations::scalar_subtract_rhs(m, s);
	}
	/**
		Matrix left-hand value subtraction (component-wise).
		@returns New matrix with @a s minus @a m.
		@tparam T A floating-point type.
		@param s Value (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat2x4<T>
	operator-(
		T const& s,
		tmat2x4<T> const& m
	) {
		return tmat2x4<T>::operations::scalar_subtract_lhs(m, s);
	}
	/**
		Matrix subtraction.
		@returns New matrix with @a m minus @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat2x4<T>
	operator-(
		tmat2x4<T> const& m,
		tmat2x4<T> const& n
	) {
		return tmat2x4<T>::operations::subtract(m, n);
	}
	/**
		Matrix right-hand scalar multiplication (component-wise).
		@returns New matrix with @a m times @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Scalar (right-hand).
	*/
	template<typename T>
	inline tmat2x4<T>
	operator*(
		tmat2x4<T> const& m,
		T const& s
	) {
		return tmat2x4<T>::operations::scalar_multiply(m, s);
	}
	/**
		Matrix left-hand scalar multiplication (component-wise).
		@returns New matrix with @a s times @a m.
		@tparam T A floating-point type.
		@param s Scalar (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat2x4<T>
	operator*(
		T const& s,
		tmat2x4<T> const& m
	) {
		return tmat2x4<T>::operations::scalar_multiply(m, s);
	}
	/**
		Matrix right-hand (row) vector multiplication (proper product).
		@returns New column vector with @a m times @a v.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param v Vector (right-hand).
	*/
	template<typename T>
	inline
	typename tmat2x4<T>::col_type
	operator*(
		tmat2x4<T> const& m,
		typename tmat2x4<T>::row_type const& v
	) {
		return tmat2x4<T>::operations::row_multiply(m, v);
	}
	/**
		Matrix left-hand (column) vector multiplication (proper product).
		@returns New row vector with @a v times @a m.
		@tparam T A floating-point type.
		@param v Vector (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline
	typename tmat2x4<T>::row_type
	operator*(
		typename tmat2x4<T>::col_type const& v,
		tmat2x4<T> const& m
	) {
		return tmat2x4<T>::operations::col_multiply(m, v);
	}
	/**
		Matrix multiplication (proper product).
		@returns New matrix with @a m times @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat2x4<T>
	operator*(
		tmat2x4<T> const& m,
		tmat2x2<T> const& n
	) {
		return tmat2x4<T>::operations::multiply(m, n);
	}
	/**
		Matrix multiplication (proper product).
		@returns New matrix with @a m times @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat3x4<T>
	operator*(
		tmat2x4<T> const& m,
		tmat3x2<T> const& n
	) {
		return tmat2x4<T>::operations::multiply(m, n);
	}
	/**
		Matrix multiplication (proper product).
		@returns New matrix with @a m times @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat4x4<T>
	operator*(
		tmat2x4<T> const& m,
		tmat4x2<T> const& n
	) {
		return tmat2x4<T>::operations::multiply(m, n);
	}
	/**
		Matrix right-hand value division (component-wise).
		@returns New matrix with @a m divided by @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Value (right-hand).
	*/
	template<typename T>
	inline tmat2x4<T>
	operator/(
		tmat2x4<T> const& m,
		T const& s
	) {
		return tmat2x4<T>::operations::scalar_divide_rhs(m, s);
	}
	/**
		Matrix left-hand value division (component-wise).
		@returns New matrix with @a s divided by @a m.
		@tparam T A floating-point type.
		@param s Value (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat2x4<T>
	operator/(
		T const& s,
		tmat2x4<T> const& m
	) {
		return tmat2x4<T>::operations::scalar_divide_lhs(m, s);
	}
/// @}

/** @} */ // end of doc-group mat2x4
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am

#endif // AM_DETAIL_LINEAR_TMAT2X4_HPP_
