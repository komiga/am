/**
@file detail/linear/tmat4x2.hpp
@brief 4x2 matrix.

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
template<class T> struct tvec4;
template<class T> struct tmat2x2;
template<class T> struct tmat2x4;
template<class T> struct tmat3x2;
template<class T> struct tmat3x4;
template<class T> struct tmat4x2;
template<class T> struct tmat4x4;

AM_DETAIL_TYPE_IS_MATRIX(tmat4x2);
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
	@addtogroup mat4x2
	@{
*/

/**
	Generic 4x2 matrix.

	@tparam T A floating-point type.
*/
template<
	class T
>
struct tmat4x2 {
public:
	/** @cond INTERNAL */
	AM_STATIC_ASSERT(
		true == std::is_floating_point<T>::value,
		"T must be a floating-point type"
	);
	/** @endcond */

	/** Type of @c *this. */
	using type = tmat4x2<T>;
	/** Type of transpose. */
	using transpose_type = tmat2x4<T>;
	/** Type of components. */
	using value_type = T;
	/** Type of rows. */
	using row_type = tvec4<T>;
	/** Type of columns. */
	using col_type = tvec2<T>;
	/** Size/length type. */
	using size_type = std::size_t;

	/** Dummy enum for constructing uninitialized matrices. */
	enum ctor_no_init {no_init};

/** @cond INTERNAL */
	struct operations;
/** @endcond */

	/** Raw columns. */
	col_type data[4];

/** @name Constructors */ /// @{
	/**
		Construct to identity.
	*/
	tmat4x2() : data{
		col_type{T(1), T(0)},
		col_type{T(0), T(1)},
		col_type{T(0), T(0)},
		col_type{T(0), T(0)}
	} {}
	/**
		Construct uninitialized.
	*/
	explicit
	tmat4x2(
		ctor_no_init
	) {}

	/**
		Construct to main diagonal.

		@param s Value.
	*/
	explicit
	tmat4x2(
		value_type const& s
	) : data{
		col_type{s, T(0)},
		col_type{T(0), s},
		col_type{T(0), T(0)},
		col_type{T(0), T(0)}
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
	tmat4x2(
		U const& s
	) : data{
		col_type{T(s), T(0)},
		col_type{T(0), T(s)},
		col_type{T(0), T(0)},
		col_type{T(0), T(0)}
	} {}

	/**
		Construct to values.

		@param x1,y1 First column.
		@param x2,y2 Second column.
		@param x3,y3 Third column.
		@param x4,y4 Fourth column.
	*/
	explicit
	tmat4x2(
		value_type const& x1, value_type const& y1,
		value_type const& x2, value_type const& y2,
		value_type const& x3, value_type const& y3,
		value_type const& x4, value_type const& y4
	) : data{
		col_type{x1, y1},
		col_type{x2, y2},
		col_type{x3, y3},
		col_type{x4, y4}
	} {}
	/**
		Construct to values.

		@tparam X1,Y1, X2,Y2, X3,Y3, X4,Y4 An arithmetic type.
		@param x1,y1 First column.
		@param x2,y2 Second column.
		@param x3,y3 Third column.
		@param x4,y4 Fourth column.
	*/
	template<
		class X1, class Y1,
		class X2, class Y2,
		class X3, class Y3,
		class X4, class Y4
	>
	explicit
	tmat4x2(
		X1 const& x1, Y1 const& y1,
		X2 const& x2, Y2 const& y2,
		X3 const& x3, Y3 const& y3,
		X4 const& x4, Y4 const& y4
	) : data{
		col_type{T(x1), T(y1)},
		col_type{T(x2), T(y2)},
		col_type{T(x3), T(y3)},
		col_type{T(x4), T(y4)}
	} {}

	/**
		Construct to column vectors.

		@param c1 First column.
		@param c2 Second column.
		@param c3 Third column.
		@param c4 Fourth column.
	*/
	explicit
	tmat4x2(
		col_type const& c1,
		col_type const& c2,
		col_type const& c3,
		col_type const& c4
	) : data{
		c1,
		c2,
		c3,
		c4
	} {}
	/**
		Construct to column vectors.

		@tparam C1, C2, C3, C4 An arithmetic type.
		@param c1 First column.
		@param c2 Second column.
		@param c3 Third column.
		@param c4 Fourth column.
	*/
	template<
		class C1,
		class C2,
		class C3,
		class C4
	>
	explicit
	tmat4x2(
		tvec2<C1> const& c1,
		tvec2<C2> const& c2,
		tvec2<C3> const& c3,
		tvec2<C4> const& c4
	) : data{
		col_type{c1},
		col_type{c2},
		col_type{c3},
		col_type{c4}
	} {}

	/**
		Construct to matrix.

		@param m Matrix to copy.
	*/
	tmat4x2(type const& m) = default;

	/**
		Construct to matrix.

		@tparam U A floating-point type.
		@param m Matrix to copy.
	*/
	template<
		class U
	>
	tmat4x2(
		tmat4x2<U> const& m
	) : data{
		col_type{m.data[0]},
		col_type{m.data[1]},
		col_type{m.data[2]},
		col_type{m.data[3]}
	} {}
/// @}

/** @name Properties */ /// @{
	/**
		Get number of columns.

		@returns @c 4.
	*/
	static constexpr size_type
	size() {
		return size_type(4);
	}
	/**
		Get size of column vector.

		@returns @c 2.
	*/
	static constexpr size_type
	col_size() {
		return col_type::size();
	}
	/**
		Get size of row vector.

		@returns @c 4.
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
		@param m Matrix to copy.
	*/
	type&
	operator=(type const& m) = default;

	/**
		Assign to matrix.

		@returns @c *this after assignment.
		@tparam U A floating-point type.
		@param m Matrix to copy.
	*/
	template<class U>
	type&
	operator=(
		tmat4x2<U> const& m
	) {
		data[0] = m.data[0];
		data[1] = m.data[1];
		data[2] = m.data[2];
		data[3] = m.data[3];
		return *this;
	}
/// @}

}; // struct tmat4x2

/** @} */ // end of doc-group mat4x2
/** @} */ // end of doc-group matrix
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am
