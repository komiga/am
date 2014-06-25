/**
@file detail/linear/tmat2x3.hpp
@brief 2x3 matrix.

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../../config.hpp"
#include "./type_traits.hpp"

#include <cassert>
#include <type_traits>

namespace am {
namespace detail {
namespace linear {

// Forward declarations
/** @cond INTERNAL */
template<class T> struct tvec2;
template<class T> struct tvec3;
template<class T> struct tmat2x2;
template<class T> struct tmat2x3;
template<class T> struct tmat3x2;
template<class T> struct tmat3x3;
template<class T> struct tmat4x2;
template<class T> struct tmat4x3;

AM_DETAIL_TYPE_IS_MATRIX(tmat2x3);
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
	@addtogroup mat2x3
	@{
*/

/**
	Generic 2x3 matrix.

	@tparam T A floating-point type.
*/
template<
	class T
>
struct tmat2x3 {
public:
	/** @cond INTERNAL */
	AM_STATIC_ASSERT(
		true == std::is_floating_point<T>::value,
		"T must be a floating-point type"
	);
	/** @endcond */

	/** Type of @c *this. */
	using type = tmat2x3<T>;
	/** Type of transpose. */
	using transpose_type = tmat3x2<T>;
	/** Type of components. */
	using value_type = T;
	/** Type of rows. */
	using row_type = tvec2<T>;
	/** Type of columns. */
	using col_type = tvec3<T>;
	/** Size/length type. */
	using size_type = std::size_t;

	/** Dummy enum for constructing uninitialized matrices. */
	enum ctor_no_init {no_init};

	/** Raw columns. */
	col_type data[2];

/** @cond INTERNAL */
	struct operations;
/** @endcond */

/** @name Constructors */ /// @{
	/**
		Construct to identity.
	*/
	tmat2x3() : data{
		col_type{T(1), T(0), T(0)},
		col_type{T(0), T(1), T(0)}
	} {}
	/**
		Construct uninitialized.
	*/
	explicit
	tmat2x3(
		ctor_no_init
	) {}

	/**
		Construct to main diagonal.

		@param s Value.
	*/
	explicit
	tmat2x3(
		value_type const& s
	) : data{
		col_type{s, T(0), T(0)},
		col_type{T(0), s, T(0)}
	} {}
	/**
		Construct to main diagonal.

		@tparam U An arithmetic type.
		@param s Value.
	*/
	template<
		class U
	>
	explicit
	tmat2x3(
		U const& s
	) : data{
		col_type{T(s), T(0), T(0)},
		col_type{T(0), T(s), T(0)}
	} {}

	/**
		Construct to values.

		@param x1,y1,z1 First column.
		@param x2,y2,z2 Second column.
	*/
	explicit
	tmat2x3(
		value_type const& x1, value_type const& y1, value_type const& z1,
		value_type const& x2, value_type const& y2, value_type const& z2
	) : data{
		col_type{x1, y1, z1},
		col_type{x2, y2, z2}
	} {}
	/**
		Construct to values.

		@tparam X1,Y1,Z1, X2,Y2,Z2 An arithmetic type.
		@param x1,y1,z1 First column.
		@param x2,y2,z2 Second column.
	*/
	template<
		class X1, class Y1, class Z1,
		class X2, class Y2, class Z2
	>
	explicit
	tmat2x3(
		X1 const& x1, Y1 const& y1, Z1 const& z1,
		X2 const& x2, Y2 const& y2, Z2 const& z2
	) : data{
		col_type{T(x1), T(y1), T(z1)},
		col_type{T(x2), T(y2), T(z2)}
	} {}

	/**
		Construct to column vectors.

		@param c1 First column.
		@param c2 Second column.
	*/
	explicit
	tmat2x3(
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
		class C1,
		class C2
	>
	explicit
	tmat2x3(
		tvec3<C1> const& c1,
		tvec3<C2> const& c2
	) : data{
		col_type{c1},
		col_type{c2}
	} {}

	/**
		Construct to matrix.

		@param m Matrix to copy.
	*/
	tmat2x3(
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
	template<
		class U
	>
	tmat2x3(
		tmat2x3<U> const& m
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
	static constexpr size_type
	size() {
		return size_type(2);
	}
	/**
		Get size of column vector.

		@returns @c 3.
	*/
	static constexpr size_type
	col_size() {
		return col_type::size();
	}
	/**
		Get size of row vector.

		@returns @c 2.
	*/
	static constexpr size_type
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

/** @name Assignment operators */ /// @{
	/**
		Assign to matrix.

		@returns @c *this after assignment.
		@tparam U A floating-point type.
		@param m Matrix to copy.
	*/
	template<class U>
	type&
	operator=(
		tmat2x3<U> const& m
	) {
		data[0] = m.data[0];
		data[1] = m.data[1];
		return *this;
	}
/// @}
}; // struct tmat2x3

/** @} */ // end of doc-group mat2x3
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am
