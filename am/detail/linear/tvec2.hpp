/**
@file detail/linear/tvec2.hpp
@brief 2-dimensional vector.

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
template<class T> struct tvec4;

AM_DETAIL_TYPE_IS_VECTOR(tvec2);
/** @endcond */

/**
	@addtogroup linear
	@{
*/
/**
	@addtogroup vector
	@{
*/
/**
	@addtogroup vec2
	@{
*/

/**
	Generic 2-dimensional vector.

	@tparam T An arithmetic type.
*/
template<
	class T
>
struct tvec2 {
	/** @cond INTERNAL */
	AM_STATIC_ASSERT(
		true == std::is_arithmetic<T>::value,
		"T must be an arithmetic type"
	);
	/** @endcond */

	/** Type of @c *this. */
	using type = tvec2<T>;
	/** Type of components. */
	using value_type = T;
	/** Size/length type. */
	using size_type = std::size_t;

	/** Dummy enum for constructing uninitialized vectors. */
	enum ctor_no_init {no_init};

/** @cond INTERNAL */
	struct operations;
/** @endcond */ // INTERNAL

/** @name Fields */ /// @{
	value_type x; /**< X value. */
	value_type y; /**< Y value. */
/// @}

/** @name Constructors */ /// @{
	/**
		Construct zeroed.
	*/
	tvec2() :
		x{T(0)}, y{T(0)}
	{}
	/**
		Construct uninitialized.
	*/
	explicit
	tvec2(
		ctor_no_init
	) {}

	/**
		Construct all components to value.

		@param s Value.
	*/
	explicit
	tvec2(
		value_type const& s
	) :
		x{s}, y{s}
	{}
	/**
		Construct all components to value.

		@tparam U An arithmetic type.
		@param s Value.
	*/
	template<
		class U
	>
	explicit
	tvec2(
		U const& s
	) :
		x{T(s)}, y{T(s)}
	{}

	/**
		Construct to values.

		@param c1 X value.
		@param c2 Y value.
	*/
	explicit
	tvec2(
		value_type const& c1,
		value_type const& c2
	) :
		x{c1}, y{c2}
	{}
	/**
		Construct to values.

		@tparam U, V An arithmetic type.
		@param c1 X value.
		@param c2 Y value.
	*/
	template<
		class U,
		class V
	>
	explicit
	tvec2(
		U const& c1,
		V const& c2
	) :
		x{T(c1)}, y{T(c2)}
	{}

	/**
		Construct to vector.

		@param v Vector to copy.
	*/
	tvec2(type const& v) = default;

	/**
		Construct to vector.

		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<
		class U
	>
	tvec2(
		tvec2<U> const& v
	) :
		x{T(v.x)}, y{T(v.y)}
	{}
	
	/**
		Construct to higher-dimension vector.

		@note Higher-dimension components will be ignored.

		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<
		class U
	>
	explicit
	tvec2(
		tvec3<U> const& v
	) :
		x{T(v.x)}, y{T(v.y)}
	{}
	/** @copydoc tvec2(tvec3<U> const&) */
	template<
		class U
	>
	explicit
	tvec2(
		tvec4<U> const& v
	) :
		x{T(v.x)}, y{T(v.y)}
	{}
/// @}

/** @name Properties */ /// @{
	/**
		Get number of components.

		@returns @c 2.
	*/
	static constexpr size_type
	size() {
		return size_type(2);
	}

	/**
		Get value at index.

		@note An assert will catch invalid indices;
		see fields for completely raw access.

		@returns The value at @a i.
		@param i Index to retrieve.
	*/
	value_type&
	operator[](
		size_type const& i
	) {
		assert(size() > i);
		return (&x)[i];
	}
	/** @copydoc operator[](size_type const&) */
	value_type const&
	operator[](
		size_type const& i
	) const {
		assert(size() > i);
		return (&x)[i];
	}
/// @}

/** @name Assignment operators */ /// @{
	/**
		Assign all components to value.

		@returns @c *this after assignment.
		@tparam U An arithmetic type.
		@param s Value.
	*/
	template<class U>
	type&
	operator=(
		U const& s
	) {
		this->x = T(s);
		this->y = T(s);
		return *this;
	}

	/**
		Assign to vector.

		@returns @c *this after assignment.
		@param v Vector to copy.
	*/
	type&
	operator=(type const& v) = default;

	/**
		Assign to vector.

		@returns @c *this after assignment.
		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<class U>
	type&
	operator=(
		tvec2<U> const& v
	) {
		this->x = T(v.x);
		this->y = T(v.y);
		return *this;
	}
/// @}
}; // struct tvec2

/** @} */ // end of doc-group vec2
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am
