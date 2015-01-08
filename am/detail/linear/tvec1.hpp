/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief 1-dimensional vector.
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
template<class T> struct tvec1;
template<class T> struct tvec2;
template<class T> struct tvec3;
template<class T> struct tvec4;

AM_DETAIL_TYPE_IS_VECTOR(tvec1);
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
	@addtogroup vec1
	@{
*/

/**
	Generic 1-dimensional vector.

	@tparam T An arithmetic type.
*/
template<
	class T
>
struct tvec1 {
	/** @cond INTERNAL */
	AM_STATIC_ASSERT(
		true == std::is_arithmetic<T>::value,
		"T must be an arithmetic type"
	);
	/** @endcond */

	/** Type of @c *this. */
	using type = tvec1<T>;
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
/// @}

/** @name Constructors */ /// @{
	/**
		Construct zeroed.
	*/
	tvec1() :
		x{T(0)}
	{}
	/**
		Construct uninitialized.
	*/
	explicit
	tvec1(
		ctor_no_init
	) {}
	/**
		Construct to value.

		@param c1 X value.
	*/
	explicit
	tvec1(
		value_type const& c1
	) :
		x{c1}
	{}
	/**
		Construct to value.

		@tparam U An arithmetic type.
		@param c1 X value.
	*/
	template<
		class U
	>
	explicit
	tvec1(
		U const& c1
	) :
		x{T(c1)}
	{}

	/**
		Construct to vector.

		@param v Vector to copy.
	*/
	tvec1(type const& v) = default;

	/**
		Construct to vector.

		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<
		class U
	>
	tvec1(
		tvec1<U> const& v
	) :
		x{T(v.x)}
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
	tvec1(
		tvec2<U> const& v
	) :
		x{T(v.x)}
	{}
	/** @copydoc tvec1(tvec2<U> const&) */
	template<
		class U
	>
	explicit
	tvec1(
		tvec3<U> const& v
	) :
		x{T(v.x)}
	{}
	/** @copydoc tvec1(tvec2<U> const&) */
	template<
		class U
	>
	explicit
	tvec1(
		tvec4<U> const& v
	) :
		x{T(v.x)}
	{}
/// @}

/** @name Properties */ /// @{
	/**
		Get number of components.

		@returns @c 1.
	*/
	static constexpr size_type
	size() {
		return size_type(1);
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
		(void)i;
		assert(size() > i);
		return this->x;
	}
	/** @copydoc operator[](size_type const&) */
	value_type const&
	operator[](
		size_type const& i
	) const {
		(void)i;
		assert(size() > i);
		return this->x;
	}
/// @}

/** @name Assignment operators */ /// @{
	/**
		Assign to value.

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
		tvec1<U> const& v
	) {
		this->x = T(v.x);
		return *this;
	}
/// @}
}; // struct tvec1

/** @} */ // end of doc-group vec1
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am
