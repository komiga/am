/**
@file detail/linear/tmat4x3.hpp
@brief 4x3 matrix.

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_DETAIL_LINEAR_TMAT4X3_HPP_
#define AM_DETAIL_LINEAR_TMAT4X3_HPP_

#include "../../config.hpp"
#include "./type_traits.hpp"

#include <cassert>
#include <type_traits>

namespace am {
namespace detail {
namespace linear {

// Forward declarations
/** @cond INTERNAL */
template<typename T> struct tvec3;
template<typename T> struct tvec4;
template<typename T> struct tmat2x3;
template<typename T> struct tmat2x4;
template<typename T> struct tmat3x3;
template<typename T> struct tmat3x4;
template<typename T> struct tmat4x3;
template<typename T> struct tmat4x4;

AM_DETAIL_TYPE_IS_MATRIX(tmat4x3);
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
	@addtogroup mat4x3
	@{
*/

/**
	Generic 4x3 matrix.
	@tparam T A floating-point type.
*/
template<typename T>
struct tmat4x3 {
public:
	/** @cond INTERNAL */
	AM_STATIC_ASSERT(true==std::is_floating_point<T>::value, "T must be a floating-point type");
	/** @endcond */

	/** Type of @c *this. */
	typedef tmat4x3<T> type;
	/** Type of transpose. */
	typedef tmat3x4<T> transpose_type;
	/** Type of components. */
	typedef T value_type;
	/** Type of rows. */
	typedef tvec4<T> row_type;
	/** Type of columns. */
	typedef tvec3<T> col_type;
	/** Size/length type. */
	typedef std::size_t size_type;

	/** Dummy enum for constructing uninitialized matrices. */
	enum ctor_no_init {no_init};

	/** Raw columns. */
	col_type data[4];

/** @cond INTERNAL */
	struct operations {
	typedef type const& type_cref;
	typedef value_type const& value_cref;
	typedef row_type const& row_cref;
	typedef col_type const& col_cref;

	inline static transpose_type transpose(type_cref m) {
		return transpose_type{
			m.data[0].x, m.data[1].x, m.data[2].x, m.data[3].x,
			m.data[0].y, m.data[1].y, m.data[2].y, m.data[3].y,
			m.data[0].z, m.data[1].z, m.data[2].z, m.data[3].z};
	}

	inline static type postfix_increment(type_cref m) {
		return type{
			m.data[0]++,
			m.data[1]++,
			m.data[2]++,
			m.data[3]++};
	}
	inline static type postfix_decrement(type_cref m) {
		return type{
			m.data[0]--,
			m.data[1]--,
			m.data[2]--,
			m.data[3]--};
	}

	inline static type unary_negative(type_cref m) {
		return type{
			-m.data[0],
			-m.data[1],
			-m.data[2],
			-m.data[3]};
	}

	inline static type scalar_add(type_cref m, value_cref s) {
		return type{
			m.data[0] + s,
			m.data[1] + s,
			m.data[2] + s,
			m.data[3] + s};
	}

	inline static type add(type_cref m, type_cref n) {
		return type{
			m.data[0] + n.data[0],
			m.data[1] + n.data[1],
			m.data[2] + n.data[2],
			m.data[3] + n.data[3]};
	}

	inline static type scalar_subtract_rhs(type_cref m, value_cref s) {
		return type{
			m.data[0] - s,
			m.data[1] - s,
			m.data[2] - s,
			m.data[3] - s};
	}
	inline static type scalar_subtract_lhs(type_cref m, value_cref s) {
		return type{
			s - m.data[0],
			s - m.data[1],
			s - m.data[2],
			s - m.data[3]};
	}

	inline static type subtract(type_cref m, type_cref n) {
		return type{
			m.data[0] - n.data[0],
			m.data[1] - n.data[1],
			m.data[2] - n.data[2],
			m.data[3] - n.data[3]};
	}

	inline static type scalar_multiply(type_cref m, value_cref s) {
		return type{
			m.data[0] * s,
			m.data[1] * s,
			m.data[2] * s,
			m.data[3] * s};
	}

	inline static col_type row_multiply(type_cref m, row_cref v) {
		return col_type{
			m.data[0].x * v.x + m.data[1].x * v.y + m.data[2].x * v.z + m.data[3].x * v.w,
			m.data[0].y * v.x + m.data[1].y * v.y + m.data[2].y * v.z + m.data[3].y * v.w,
			m.data[0].z * v.x + m.data[1].z * v.y + m.data[2].z * v.z + m.data[3].z * v.w};
	}
	inline static row_type col_multiply(type_cref m, col_cref v) {
		return row_type{
			m.data[0].x * v.x + m.data[0].y * v.y + m.data[0].z * v.z,
			m.data[1].x * v.x + m.data[1].y * v.y + m.data[1].z * v.z,
			m.data[2].x * v.x + m.data[2].y * v.y + m.data[2].z * v.z,
			m.data[3].x * v.x + m.data[3].y * v.y + m.data[3].z * v.z};
	}

	inline static tmat2x3<T> multiply(type_cref m, tmat2x4<T> const& n) {
		return tmat2x3<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y + m.data[2].x * n.data[0].z + m.data[3].x * n.data[0].w,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y + m.data[2].y * n.data[0].z + m.data[3].y * n.data[0].w,
			m.data[0].z * n.data[0].x + m.data[1].z * n.data[0].y + m.data[2].z * n.data[0].z + m.data[3].z * n.data[0].w,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y + m.data[2].x * n.data[1].z + m.data[3].x * n.data[1].w,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y + m.data[2].y * n.data[1].z + m.data[3].y * n.data[1].w,
			m.data[0].z * n.data[1].x + m.data[1].z * n.data[1].y + m.data[2].z * n.data[1].z + m.data[3].z * n.data[1].w};
	}
	inline static tmat3x3<T> multiply(type_cref m, tmat3x4<T> const& n) {
		return tmat3x3<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y + m.data[2].x * n.data[0].z + m.data[3].x * n.data[0].w,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y + m.data[2].y * n.data[0].z + m.data[3].y * n.data[0].w,
			m.data[0].z * n.data[0].x + m.data[1].z * n.data[0].y + m.data[2].z * n.data[0].z + m.data[3].z * n.data[0].w,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y + m.data[2].x * n.data[1].z + m.data[3].x * n.data[1].w,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y + m.data[2].y * n.data[1].z + m.data[3].y * n.data[1].w,
			m.data[0].z * n.data[1].x + m.data[1].z * n.data[1].y + m.data[2].z * n.data[1].z + m.data[3].z * n.data[1].w,
			m.data[0].x * n.data[2].x + m.data[1].x * n.data[2].y + m.data[2].x * n.data[2].z + m.data[3].x * n.data[2].w,
			m.data[0].y * n.data[2].x + m.data[1].y * n.data[2].y + m.data[2].y * n.data[2].z + m.data[3].y * n.data[2].w,
			m.data[0].z * n.data[2].x + m.data[1].z * n.data[2].y + m.data[2].z * n.data[2].z + m.data[3].z * n.data[2].w};
	}
	inline static tmat4x3<T> multiply(type_cref m, tmat4x4<T> const& n) {
		return tmat4x3<T>{
			m.data[0].x * n.data[0].x + m.data[1].x * n.data[0].y + m.data[2].x * n.data[0].z + m.data[3].x * n.data[0].w,
			m.data[0].y * n.data[0].x + m.data[1].y * n.data[0].y + m.data[2].y * n.data[0].z + m.data[3].y * n.data[0].w,
			m.data[0].z * n.data[0].x + m.data[1].z * n.data[0].y + m.data[2].z * n.data[0].z + m.data[3].z * n.data[0].w,
			m.data[0].x * n.data[1].x + m.data[1].x * n.data[1].y + m.data[2].x * n.data[1].z + m.data[3].x * n.data[1].w,
			m.data[0].y * n.data[1].x + m.data[1].y * n.data[1].y + m.data[2].y * n.data[1].z + m.data[3].y * n.data[1].w,
			m.data[0].z * n.data[1].x + m.data[1].z * n.data[1].y + m.data[2].z * n.data[1].z + m.data[3].z * n.data[1].w,
			m.data[0].x * n.data[2].x + m.data[1].x * n.data[2].y + m.data[2].x * n.data[2].z + m.data[3].x * n.data[2].w,
			m.data[0].y * n.data[2].x + m.data[1].y * n.data[2].y + m.data[2].y * n.data[2].z + m.data[3].y * n.data[2].w,
			m.data[0].z * n.data[2].x + m.data[1].z * n.data[2].y + m.data[2].z * n.data[2].z + m.data[3].z * n.data[2].w,
			m.data[0].x * n.data[3].x + m.data[1].x * n.data[3].y + m.data[2].x * n.data[3].z + m.data[3].x * n.data[3].w,
			m.data[0].y * n.data[3].x + m.data[1].y * n.data[3].y + m.data[2].y * n.data[3].z + m.data[3].y * n.data[3].w,
			m.data[0].z * n.data[3].x + m.data[1].z * n.data[3].y + m.data[2].z * n.data[3].z + m.data[3].z * n.data[3].w};
	}

	inline static type scalar_divide_rhs(type_cref m, value_cref s) {
		return type{
			m.data[0] / s,
			m.data[1] / s,
			m.data[2] / s,
			m.data[3] / s};
	}
	inline static type scalar_divide_lhs(type_cref m, value_cref s) {
		return type{
			s / m.data[0],
			s / m.data[1],
			s / m.data[2],
			s / m.data[3]};
	}
	};
/** @endcond */ // INTERNAL

/** @name Constructors */ /// @{
	/**
		Construct to identity.
	*/
	inline tmat4x3() /** @cond INTERNAL */: data{
		col_type{T(1), T(0), T(0)},
		col_type{T(0), T(1), T(0)},
		col_type{T(0), T(0), T(1)},
		col_type{T(0), T(0), T(0)}}/** @endcond */ {}
	/**
		Construct uninitialized.
	*/
	inline explicit tmat4x3(ctor_no_init) {}

	/**
		Construct to main diagonal.
		@param s Value.
	*/
	inline explicit tmat4x3(value_type const& s) /** @cond INTERNAL */: data{
		col_type{s, T(0), T(0)},
		col_type{T(0), s, T(0)},
		col_type{T(0), T(0), s},
		col_type{T(0), T(0), T(0)}}/** @endcond */ {}
	/**
		Construct to main diagonal.
		@tparam U An arithmetic type.
		@param s Value.
	*/
	template<typename U>
	inline explicit tmat4x3(U const& s) /** @cond INTERNAL */: data{
		col_type{T(s), T(0), T(0)},
		col_type{T(0), T(s), T(0)},
		col_type{T(0), T(0), T(s)},
		col_type{T(0), T(0), T(0)}}/** @endcond */ {}

	/**
		Construct to values.
		@param x1 X value of first column.
		@param y1 Y value of first column.
		@param z1 Z value of first column.
		@param x2 X value of second column.
		@param y2 Y value of second column.
		@param z2 Z value of second column.
		@param x3 X value of third column.
		@param y3 Y value of third column.
		@param z3 Z value of third column.
		@param x4 X value of fourth column.
		@param y4 Y value of fourth column.
		@param z4 Z value of fourth column.
	*/
	inline explicit tmat4x3(value_type const& x1, value_type const& y1, value_type const& z1,
							value_type const& x2, value_type const& y2, value_type const& z2,
							value_type const& x3, value_type const& y3, value_type const& z3,
							value_type const& x4, value_type const& y4, value_type const& z4) /** @cond INTERNAL */: data{
		col_type{x1, y1, z1},
		col_type{x2, y2, z2},
		col_type{x3, y3, z3},
		col_type{x4, y4, z4}}/** @endcond */ {}
	/**
		Construct to values.
		@tparam X1,Y1,Z1, X2,Y2,Z2, X3,Y3,Z3, X4,Y4,Z4 An arithmetic type.
		@param x1 X value of first column.
		@param y1 Y value of first column.
		@param z1 Z value of first column.
		@param x2 X value of second column.
		@param y2 Y value of second column.
		@param z2 Z value of second column.
		@param x3 X value of third column.
		@param y3 Y value of third column.
		@param z3 Z value of third column.
		@param x4 X value of fourth column.
		@param y4 Y value of fourth column.
		@param z4 Z value of fourth column.
	*/
	template<typename X1, typename Y1, typename Z1, typename X2, typename Y2, typename Z2, typename X3, typename Y3, typename Z3, typename X4, typename Y4, typename Z4>
	inline explicit tmat4x3(X1 const& x1, Y1 const& y1, Z1 const& z1,
							X2 const& x2, Y2 const& y2, Z2 const& z2,
							X3 const& x3, Y3 const& y3, Z3 const& z3,
							X4 const& x4, Y4 const& y4, Z4 const& z4) /** @cond INTERNAL */: data{
		col_type{T(x1), T(y1), T(z1)},
		col_type{T(x2), T(y2), T(z2)},
		col_type{T(x3), T(y3), T(z3)},
		col_type{T(x4), T(y4), T(z4)}}/** @endcond */ {}

	/**
		Construct to column vectors.
		@param c1 First column.
		@param c2 Second column.
		@param c3 Third column.
		@param c4 Fourth column.
	*/
	inline explicit tmat4x3(col_type const& c1,
							col_type const& c2,
							col_type const& c3,
							col_type const& c4) /** @cond INTERNAL */: data{
		c1,
		c2,
		c3,
		c4}/** @endcond */ {}
	/**
		Construct to column vectors.
		@tparam C1, C2, C3, C4 An arithmetic type.
		@param c1 First column.
		@param c2 Second column.
		@param c3 Third column.
		@param c4 Fourth column.
	*/
	template<typename C1, typename C2, typename C3, typename C4>
	inline explicit tmat4x3(tvec2<C1> const& c1,
							tvec2<C2> const& c2,
							tvec2<C3> const& c3,
							tvec2<C4> const& c4) /** @cond INTERNAL */: data{
		col_type{c1},
		col_type{c2},
		col_type{c3},
		col_type{c4}}/** @endcond */ {}

	/**
		Construct to matrix.
		@param m Matrix to copy.
	*/
	inline tmat4x3(type const& m) /** @cond INTERNAL */: data{
		m.data[0],
		m.data[1],
		m.data[2],
		m.data[3]}/** @endcond */ {}
	/**
		Construct to matrix.
		@tparam U A floating-point type.
		@param m Matrix to copy.
	*/
	template<typename U>
	inline tmat4x3(tmat4x3<U> const& m) /** @cond INTERNAL */: data{
		col_type{m.data[0]},
		col_type{m.data[1]},
		col_type{m.data[2]},
		col_type{m.data[3]}}/** @endcond */ {}
/// @}

/** @name Properties */ /// @{
	/**
		Get number of columns.
		@returns @c 4.
	*/
	inline static AM_CONSTEXPR size_type size() { return size_type(4); }
	/**
		Get size of column vector.
		@returns @c 3.
	*/
	inline static AM_CONSTEXPR size_type col_size() { return col_type::size(); }
	/**
		Get size of row vector.
		@returns @c 4.
	*/
	inline static AM_CONSTEXPR size_type row_size() { return row_type::size(); }
	/**
		Get column at index.
		@returns The column at @a i.
		@param i Index to retrieve.
	*/
	inline col_type& operator[](size_type const& i) {
		assert(size()>i);
		return data[i];
	}
	/** @copydoc operator[](size_type const&) */
	inline col_type const& operator[](size_type const& i) const {
		assert(size()>i);
		return data[i];
	}
/// @}

/** @name Comparison operators */ /// @{
	/**
		Equivalence operator.
		@returns @c true if the two matrices are equal, @c false if they are not.
		@param m Matrix to compare with.
	*/
	inline bool operator==(type const& m) const {
		return
			data[0]==m.data[0] &&
			data[1]==m.data[1] &&
			data[2]==m.data[2] &&
			data[3]==m.data[3];
	}
	/**
		Non-equivalence operator.
		@returns @c false if the two matrices are equal, @c true if they are not.
		@param m Matrix to compare with.
	*/
	inline bool operator!=(type const& m) const {
		return
			data[0]!=m.data[0] ||
			data[1]!=m.data[1] ||
			data[2]!=m.data[2] ||
			data[3]!=m.data[3];
	}
/// @}

/** @name Increment and decrement operators */ /// @{
	/**
		Prefix increment.
		@returns @c *this after operation.
	*/
	inline type& operator++() {
		++data[0];
		++data[1];
		++data[2];
		++data[3];
		return *this;
	}
	/**
		Prefix decrement.
		@returns @c *this after operation.
	*/
	inline type& operator--() {
		--data[0];
		--data[1];
		--data[2];
		--data[3];
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
	inline type& operator=(tmat4x3<U> const& m) {
		data[0]=m.data[0];
		data[1]=m.data[1];
		data[2]=m.data[2];
		data[3]=m.data[3];
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
	inline type& operator+=(U const& s) {
		data[0]+=T(s);
		data[1]+=T(s);
		data[2]+=T(s);
		data[3]+=T(s);
		return *this;
	}
	/**
		Add matrix.
		@returns @c *this after operation.
		@tparam U A floating-point type.
		@param m Matrix to add.
	*/
	template<typename U>
	inline type& operator+=(tmat4x3<U> const& m) {
		data[0]+=m.data[0];
		data[1]+=m.data[1];
		data[2]+=m.data[2];
		data[3]+=m.data[3];
		return *this;
	}
	/**
		Subtract value from all components.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to subtract.
	*/
	template<typename U>
	inline type& operator-=(U const& s) {
		data[0]-=T(s);
		data[1]-=T(s);
		data[2]-=T(s);
		data[3]-=T(s);
		return *this;
	}
	/**
		Subtract matrix.
		@returns @c *this after operation.
		@tparam U A floating-point type.
		@param m Matrix to subtract.
	*/
	template<typename U>
	inline type& operator-=(tmat4x3<U> const& m) {
		data[0]-=m.data[0];
		data[1]-=m.data[1];
		data[2]-=m.data[2];
		data[3]-=m.data[3];
		return *this;
	}
	/**
		Multiply by scalar.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Scalar.
	*/
	template<typename U>
	inline type& operator*=(U const& s) {
		data[0]*=T(s);
		data[1]*=T(s);
		data[2]*=T(s);
		data[3]*=T(s);
		return *this;
	}
	/**
		Divide all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to divide by.
	*/
	template<typename U>
	inline type& operator/=(U const& s) {
		data[0]/=T(s);
		data[1]/=T(s);
		data[2]/=T(s);
		data[3]/=T(s);
		return *this;
	}
/// @}
};

/** @name mat4x3 increment and decrement operators */ /// @{
	/**
		Matrix postfix increment.
		@returns New matrix with @c m+1.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat4x3<T> operator++(tmat4x3<T> const& m, int) {
		return tmat4x3<T>::operations::postfix_increment(m);
	}
	/**
		Matrix postfix decrement.
		@returns New matrix with @c m-1.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat4x3<T> operator--(tmat4x3<T> const& m, int) {
		return tmat4x3<T>::operations::postfix_decrement(m);
	}
/// @}

/** @name mat4x3 unary operators */ /// @{
	/**
		Matrix unary plus.
		@returns New matrix with exact value of @a m.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat4x3<T> operator+(tmat4x3<T> const& m) {
		return tmat4x3<T>{m};
	}
	/**
		Matrix unary minus.
		@returns New matrix with @c -m.
		@tparam T A floating-point type.
		@param m Matrix.
	*/
	template<typename T>
	inline tmat4x3<T> operator-(tmat4x3<T> const& m) {
		return tmat4x3<T>::operations::unary_negative(m);
	}
/// @}

/** @name mat4x3 arithmetic operators */ /// @{
	/**
		Matrix right-hand value addition (component-wise).
		@returns New matrix with @a m plus @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Value (right-hand).
	*/
	template<typename T>
	inline tmat4x3<T> operator+(tmat4x3<T> const& m, T const& s) {
		return tmat4x3<T>::operations::scalar_add(m, s);
	}
	/**
		Matrix left-hand value addition (component-wise).
		@returns New matrix with @a s plus @a m.
		@tparam T A floating-point type.
		@param s Value (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat4x3<T> operator+(T const& s, tmat4x3<T> const& m) {
		return tmat4x3<T>::operations::scalar_add(m, s);
	}
	/**
		Matrix addition.
		@returns New matrix with @a m plus @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat4x3<T> operator+(tmat4x3<T> const& m, tmat4x3<T> const& n) {
		return tmat4x3<T>::operations::add(m, n);
	}
	/**
		Matrix right-hand value subtraction (component-wise).
		@returns New matrix with @a m minus @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Value (right-hand).
	*/
	template<typename T>
	inline tmat4x3<T> operator-(tmat4x3<T> const& m, T const& s) {
		return tmat4x3<T>::operations::scalar_subtract_rhs(m, s);
	}
	/**
		Matrix left-hand value subtraction (component-wise).
		@returns New matrix with @a s minus @a m.
		@tparam T A floating-point type.
		@param s Value (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat4x3<T> operator-(T const& s, tmat4x3<T> const& m) {
		return tmat4x3<T>::operations::scalar_subtract_lhs(m, s);
	}
	/**
		Matrix subtraction.
		@returns New matrix with @a m minus @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat4x3<T> operator-(tmat4x3<T> const& m, tmat4x3<T> const& n) {
		return tmat4x3<T>::operations::subtract(m, n);
	}
	/**
		Matrix right-hand scalar multiplication (component-wise).
		@returns New matrix with @a m times @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Scalar (right-hand).
	*/
	template<typename T>
	inline tmat4x3<T> operator*(tmat4x3<T> const& m, T const& s) {
		return tmat4x3<T>::operations::scalar_multiply(m, s);
	}
	/**
		Matrix left-hand scalar multiplication (component-wise).
		@returns New matrix with @a s times @a m.
		@tparam T A floating-point type.
		@param s Scalar (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat4x3<T> operator*(T const& s, tmat4x3<T> const& m) {
		return tmat4x3<T>::operations::scalar_multiply(m, s);
	}
	/**
		Matrix right-hand (row) vector multiplication (proper product).
		@returns New column vector with @a m times @a v.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param v Vector (right-hand).
	*/
	template<typename T>
	inline typename tmat4x3<T>::col_type operator*(tmat4x3<T> const& m, typename tmat4x3<T>::row_type const& v) {
		return tmat4x3<T>::operations::row_multiply(m, v);
	}
	/**
		Matrix left-hand (column) vector multiplication (proper product).
		@returns New row vector with @a v times @a m.
		@tparam T A floating-point type.
		@param v Vector (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline typename tmat4x3<T>::row_type operator*(typename tmat4x3<T>::col_type const& v, tmat4x3<T> const& m) {
		return tmat4x3<T>::operations::col_multiply(m, v);
	}
	/**
		Matrix multiplication (proper product).
		@returns New matrix with @a m times @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat2x3<T> operator*(tmat4x3<T> const& m, tmat2x4<T> const& n) {
		return tmat4x3<T>::operations::multiply(m, n);
	}
	/**
		Matrix multiplication (proper product).
		@returns New matrix with @a m times @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat3x3<T> operator*(tmat4x3<T> const& m, tmat3x4<T> const& n) {
		return tmat4x3<T>::operations::multiply(m, n);
	}
	/**
		Matrix multiplication (proper product).
		@returns New matrix with @a m times @a n.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param n Matrix (right-hand).
	*/
	template<typename T>
	inline tmat4x3<T> operator*(tmat4x3<T> const& m, tmat4x4<T> const& n) {
		return tmat4x3<T>::operations::multiply(m, n);
	}
	/**
		Matrix right-hand value division (component-wise).
		@returns New matrix with @a m divided by @a s.
		@tparam T A floating-point type.
		@param m Matrix (left-hand).
		@param s Value (right-hand).
	*/
	template<typename T>
	inline tmat4x3<T> operator/(tmat4x3<T> const& m, T const& s) {
		return tmat4x3<T>::operations::scalar_divide_rhs(m, s);
	}
	/**
		Matrix left-hand value division (component-wise).
		@returns New matrix with @a s divided by @a m.
		@tparam T A floating-point type.
		@param s Value (left-hand).
		@param m Matrix (right-hand).
	*/
	template<typename T>
	inline tmat4x3<T> operator/(T const& s, tmat4x3<T> const& m) {
		return tmat4x3<T>::operations::scalar_divide_lhs(m, s);
	}
/// @}

/** @} */ // end of doc-group mat4x3
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am

#endif // AM_DETAIL_LINEAR_TMAT4X3_HPP_