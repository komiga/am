/**
@file detail/linear/tvec3.hpp
@brief 3-dimensional vector.

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

AM_DETAIL_TYPE_IS_VECTOR(tvec3);
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
	@addtogroup vec3
	@{
*/

/**
	Generic 3-dimensional vector.

	@tparam T An arithmetic type.
*/
template<
	class T
>
struct tvec3 {
	/** @cond INTERNAL */
	AM_STATIC_ASSERT(
		true == std::is_arithmetic<T>::value,
		"T must be an arithmetic type"
	);
	/** @endcond */

	/** Type of @c *this. */
	using type = tvec3<T>;
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
	value_type z; /**< Z value. */
/// @}

/** @name Constructors */ /// @{
	/**
		Construct zeroed.
	*/
	tvec3() :
		x{T(0)}, y{T(0)}, z{T(0)}
	{}
	/**
		Construct uninitialized.
	*/
	explicit
	tvec3(
		ctor_no_init
	) {}

	/**
		Construct all components to value.

		@param s Value.
	*/
	explicit
	tvec3(
		value_type const& s
	) :
		x{s}, y{s}, z{s}
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
	tvec3(
		U const& s
	) :
		x{T(s)}, y{T(s)}, z{T(s)}
	{}

	/**
		Construct to values.

		@param c1 X value.
		@param c2 Y value.
		@param c3 Z value.
	*/
	explicit
	tvec3(
		value_type const& c1,
		value_type const& c2,
		value_type const& c3
	) :
		x{c1}, y{c2}, z{c3}
	{}
	/**
		Construct to values.

		@tparam U, V, H An arithmetic type.
		@param c1 X value.
		@param c2 Y value.
		@param c3 Z value.
	*/
	template<
		class U,
		class V,
		class H
	>
	explicit
	tvec3(
		U const& c1,
		V const& c2,
		H const& c3
	) :
		x{T(c1)}, y{T(c2)}, z{T(c3)}
	{}

	/**
		Construct to vector.

		@param v Vector to copy.
	*/
	tvec3(
		type const& v
	) :
		x{v.x}, y{v.y}, z{v.z}
	{}
	/**
		Construct to vector.

		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<
		class U
	>
	tvec3(
		tvec3<U> const& v
	) :
		x{T(v.x)}, y{T(v.y)}, z{T(v.z)}
	{}

	/**
		Construct to X value and YZ vector.

		@tparam U, V An arithmetic type.
		@param c1 X value.
		@param v Y and Z vector.
	*/
	template<
		class U,
		class V
	>
	explicit
	tvec3(
		U const& c1,
		tvec2<V> const& v
	) :
		x{T(c1)}, y{T(v.x)}, z{T(v.y)}
	{}
	/**
		Construct to XY vector and Z value.

		@tparam U, V An arithmetic type.
		@param v X and Y vector.
		@param c3 Z value.
	*/
	template<
		class U,
		class V
	>
	explicit
	tvec3(
		tvec2<U> const& v,
		V const& c3
	) :
		x{T(v.x)}, y{T(v.y)}, z{T(c3)}
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
	tvec3(
		tvec4<U> const& v
	) :
		x{T(v.x)}, y{T(v.y)}, z{T(v.z)}
	{}
/// @}

/** @name Properties */ /// @{
	/**
		Get number of components.

		@returns @c 3.
	*/
	static constexpr size_type
	size() {
		return size_type(3);
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
		this->z = T(s);
		return *this;
	}
	/**
		Assign to vector.

		@returns @c *this after assignment.
		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<class U>
	type&
	operator=(
		tvec3<U> const& v
	) {
		this->x = T(v.x);
		this->y = T(v.y);
		this->z = T(v.z);
		return *this;
	}
/// @}
}; // struct tvec3

/** @} */ // end of doc-group vec3
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am
