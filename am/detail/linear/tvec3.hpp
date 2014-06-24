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
#include <cmath>
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

/** @name Fields */ /// @{
	value_type x; /**< X value. */
	value_type y; /**< Y value. */
	value_type z; /**< Z value. */
/// @}

/** @cond INTERNAL */
	struct operations {
	using type_cref = type const&;
	using value_cref = value_type const&;

	static value_type
	length(
		type_cref v
	) {
		return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	static value_type
	distance(
		type_cref v,
		type_cref r
	) {
		return operations::length(r - v);
	}

	static value_type
	dot(
		type_cref v,
		type_cref r
	) {
		return v.x * r.x + v.y * r.y + v.z * r.z;
	}

	static type
	cross(
		type_cref v,
		type_cref r
	) {
		return type{
			v.y * r.z - r.y * v.z,
			v.z * r.x - r.z * v.x,
			v.x * r.y - r.x * v.y};
	}

	static type
	normalize(
		type_cref v
	) {
		return
			v * (value_type(1) / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	}

	static type
	faceforward(
		type_cref n,
		type_cref i,
		type_cref ng
	) {
		return dot(ng, i) < 0 ? n : -n;
	}

	static type
	reflect(
		type_cref i,
		type_cref n
	) {
		return i - value_type(2) * n * dot(n, i);
	}

	static type
	refract(
		type_cref i,
		type_cref n,
		value_cref eta
	) {
		value_type const d = dot(n, i);
		value_type const k = value_type(1) - eta * eta * (value_type(1) - d * d);
		return k < value_type(0)
			? type{value_type(0)}
			: type{eta * i - (eta * d + std::sqrt(k)) * n};
	}
	};
/** @endcond */ // INTERNAL

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

/** @name Comparison operators */ /// @{
	/**
		Equivalence operator.

		@returns
		- @c true if the two vectors are equal,
		- @c false if they are not.
		@param v Vector to compare with.
	*/
	bool
	operator==(
		type const& v
	) const {
		return
			this->x == v.x &&
			this->y == v.y &&
			this->z == v.z;
	}

	/**
		Non-equivalence operator.

		@returns
		- @c false if the two vectors are equal,
		- @c true if they are not.
		@param v Vector to compare with.
	*/
	bool
	operator!=(
		type const& v
	) const {
		return
			this->x != v.x ||
			this->y != v.y ||
			this->z != v.z;
	}
/// @}

/** @name Increment and decrement operators */ /// @{
	/**
		Prefix increment.

		@returns @c *this after operation.
	*/
	type&
	operator++() {
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}

	/**
		Prefix decrement.

		@returns @c *this after operation.
	*/
	type&
	operator--() {
		--this->x;
		--this->y;
		--this->z;
		return *this;
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

/** @name Arithmetic assignment operators */ /// @{
	/**
		Add value to all components.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to add.
	*/
	template<class U>
	type&
	operator+=(
		U const& s
	) {
		this->x += T(s);
		this->y += T(s);
		this->z += T(s);
		return *this;
	}
	/**
		Add vector.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to add.
	*/
	template<class U>
	type&
	operator+=(
		tvec3<U> const& v
	) {
		this->x += T(v.x);
		this->y += T(v.y);
		this->z += T(v.z);
		return *this;
	}

	/**
		Subtract value from all components.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to subtract.
	*/
	template<class U>
	type&
	operator-=(
		U const& s
	) {
		this->x -= T(s);
		this->y -= T(s);
		this->z -= T(s);
		return *this;
	}
	/**
		Subtract vector.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to subtract.
	*/
	template<class U>
	type&
	operator-=(
		tvec3<U> const& v
	) {
		this->x -= T(v.x);
		this->y -= T(v.y);
		this->z -= T(v.z);
		return *this;
	}

	/**
		Multiply by scalar.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Scalar.
	*/
	template<class U>
	type&
	operator*=(
		U const& s
	) {
		this->x *= T(s);
		this->y *= T(s);
		this->z *= T(s);
		return *this;
	}
	/**
		Multiply by vector (direct component product).

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to multiply by.
	*/
	template<class U>
	type&
	operator*=(
		tvec3<U> const& v
	) {
		this->x *= T(v.x);
		this->y *= T(v.y);
		this->z *= T(v.z);
		return *this;
	}

	/**
		Divide all components by value.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to divide by.
	*/
	template<class U>
	type&
	operator/=(
		U const& s
	) {
		this->x /= T(s);
		this->y /= T(s);
		this->z /= T(s);
		return *this;
	}
	/**
		Divide by vector (direct component quotient).

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to divide by.
	*/
	template<class U>
	type&
	operator/=(
		tvec3<U> const& v
	) {
		this->x /= T(v.x);
		this->y /= T(v.y);
		this->z /= T(v.z);
		return *this;
	}

	/**
		Modulo all components by value.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Divisor.
	*/
	template<class U>
	type&
	operator%=(
		U const& s
	) {
		this->x %= T(s);
		this->y %= T(s);
		this->z %= T(s);
		return *this;
	}
	/**
		Modulo by vector.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Divisor vector.
	*/
	template<class U>
	type&
	operator%=(
		tvec3<U> const& v
	) {
		this->x %= T(v.x);
		this->y %= T(v.y);
		this->z %= T(v.z);
		return *this;
	}
/// @}

/** @name Bitwise assignment operators */ /// @{
	/**
		Bitwise-AND all components by value.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to AND with.
	*/
	template<class U>
	type&
	operator&=(
		U const& s
	) {
		this->x &= T(s);
		this->y &= T(s);
		this->z &= T(s);
		return *this;
	}
	/**
		Bitwise-AND vector.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to AND with.
	*/
	template<class U>
	type&
	operator&=(
		tvec3<U> const& v
	) {
		this->x &= T(v.x);
		this->y &= T(v.y);
		this->z &= T(v.z);
		return *this;
	}

	/**
		Bitwise-OR all components by value.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to OR with.
	*/
	template<class U>
	type&
	operator|=(
		U const& s
	) {
		this->x |= T(s);
		this->y |= T(s);
		this->z |= T(s);
		return *this;
	}
	/**
		Bitwise-OR vector.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to OR with.
	*/
	template<class U>
	type&
	operator|=(
		tvec3<U> const& v
	) {
		this->x |= T(v.x);
		this->y |= T(v.y);
		this->z |= T(v.z);
		return *this;
	}

	/**
		Bitwise-XOR all components by value.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to XOR with.
	*/
	template<class U>
	type&
	operator^=(
		U const& s
	) {
		this->x ^= T(s);
		this->y ^= T(s);
		this->z ^= T(s);
		return *this;
	}
	/**
		Bitwise-XOR vector.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to XOR with.
	*/
	template<class U>
	type&
	operator^=(
		tvec3<U> const& v
	) {
		this->x ^= T(v.x);
		this->y ^= T(v.y);
		this->z ^= T(v.z);
		return *this;
	}

	/**
		Bitwise left-shift all components by value.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Left-shift value amount.
	*/
	template<class U>
	type&
	operator<<=(
		U const& s
	) {
		this->x <<= T(s);
		this->y <<= T(s);
		this->z <<= T(s);
		return *this;
	}
	/**
		Bitwise left-shift vector.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Left-shift vector amount.
	*/
	template<class U>
	type&
	operator<<=(
		tvec3<U> const& v
	) {
		this->x <<= T(v.x);
		this->y <<= T(v.y);
		this->z <<= T(v.z);
		return *this;
	}

	/**
		Bitwise right-shift all components by value.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Right-shift value amount.
	*/
	template<class U>
	type&
	operator>>=(
		U const& s
	) {
		this->x >>= T(s);
		this->y >>= T(s);
		this->z >>= T(s);
		return *this;
	}
	/**
		Bitwise right-shift vector.

		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Right-shift vector amount.
	*/
	template<class U>
	type&
	operator>>=(
		tvec3<U> const& v
	) {
		this->x >>= T(v.x);
		this->y >>= T(v.y);
		this->z >>= T(v.z);
		return *this;
	}
/// @}
}; // struct tvec3

/** @name vec3 increment and decrement operators */ /// @{
	/**
		Vector postfix increment.

		@returns New vector with @c x+1.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<class T>
	inline tvec3<T>
	operator++(
		tvec3<T> const& x,
		signed
	) {
		return tvec3<T>{x.x + T(1), x.y + T(1), x.z + T(1)};
	}

	/**
		Vector postfix decrement.

		@returns New vector with @c x-1.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<class T>
	inline tvec3<T>
	operator--(
		tvec3<T> const& x,
		signed
	) {
		return tvec3<T>{x.x - T(1), x.y - T(1), x.z - T(1)};
	}
/// @}

/** @name vec3 unary operators */ /// @{
	/**
		Vector unary plus.

		@returns New vector with exact value of @a x.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<class T>
	inline tvec3<T>
	operator+(
		tvec3<T> const& x
	) {
		return tvec3<T>{x.x, x.y, x.z};
	}

	/**
		Vector unary minus.

		@returns New vector with @c -x.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<class T>
	inline tvec3<T>
	operator-(
		tvec3<T> const& x
	) {
		return tvec3<T>{-x.x,
						-x.y,
						-x.z};
	}

	/**
		Vector unary bitwise-NOT.

		@returns New vector with @c ~x.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<class T>
	inline tvec3<T>
	operator~(
		tvec3<T> const& x
	) {
		return tvec3<T>{~x.x,
						~x.y,
						~x.z};
	}
/// @}

/** @name vec3 arithmetic operators */ /// @{
	/**
		Vector right-hand value addition (all components).

		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator+(
		tvec3<T> const& x,
		T const& y
	) {
		return tvec3<T>{x.x + y,
						x.y + y,
						x.z + y};
	}
	/**
		Vector left-hand value addition (all components).

		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator+(
		T const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x + y.x,
						x + y.y,
						x + y.z};
	}
	/**
		Vector addition.

		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator+(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x.x + y.x,
						x.y + y.y,
						x.z + y.z};
	}

	/**
		Vector right-hand value subtraction (all components).

		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator-(
		tvec3<T> const& x,
		T const& y
	) {
		return tvec3<T>{x.x - y,
						x.y - y,
						x.z - y};
	}
	/**
		Vector left-hand value subtraction (all components).

		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator-(
		T const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x - y.x,
						x - y.y,
						x - y.z};
	}
	/**
		Vector subtraction.

		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator-(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x.x - y.x,
						x.y - y.y,
						x.z - y.z};
	}

	/**
		Vector right-hand scalar multiplication (all components).
		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator*(
		tvec3<T> const& x,
		T const& y
	) {
		return tvec3<T>{x.x * y,
						x.y * y,
						x.z * y};
	}
	/**
		Vector left-hand scalar multiplication (all components).

		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator*(
		T const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x * y.x,
						x * y.y,
						x * y.z};
	}
	/**
		Vector multiplication (direct component product).

		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator*(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x.x * y.x,
						x.y * y.y,
						x.z * y.z};
	}

	/**
		Vector right-hand value division (all components).

		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator/(
		tvec3<T> const& x,
		T const& y
	) {
		return tvec3<T>{x.x / y,
						x.y / y,
						x.z / y};
	}
	/**
		Vector left-hand value division (all components).

		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator/(
		T const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x / y.x,
						x / y.y,
						x / y.z};
	}
	/**
		Vector division (direct component quotient).

		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator/(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x.x / y.x,
						x.y / y.y,
						x.z / y.z};
	}

	/**
		Vector right-hand value modulo (all components).

		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator%(
		tvec3<T> const& x,
		T const& y
	) {
		return tvec3<T>{x.x % y,
						x.y % y,
						x.z % y};
	}
	/**
		Vector left-hand value modulo (all components).

		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator%(
		T const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x % y.x,
						x % y.y,
						x % y.z};
	}
	/**
		Vector modulo.

		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator%(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x.x % y.x,
						x.y % y.y,
						x.z % y.z};
	}
/// @}

/** @name vec3 bitwise operators */ /// @{
	/**
		Vector right-hand value bitwise-AND (all components).

		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator&(
		tvec3<T> const& x,
		T const& y
	) {
		return tvec3<T>{x.x & y,
						x.y & y,
						x.z & y};
	}
	/**
		Vector left-hand value bitwise-AND (all components).

		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator&(
		T const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x & y.x,
						x & y.y,
						x & y.z};
	}
	/**
		Vector bitwise-AND.

		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator&(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x.x & y.x,
						x.y & y.y,
						x.z & y.z};
	}

	/**
		Vector right-hand value bitwise-OR (all components).

		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator|(
		tvec3<T> const& x,
		T const& y
	) {
		return tvec3<T>{x.x | y,
						x.y | y,
						x.z | y};
	}
	/**
		Vector left-hand value bitwise-OR (all components).

		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator|(
		T const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x | y.x,
						x | y.y,
						x | y.z};
	}
	/**
		Vector bitwise-OR.

		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator|(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x.x | y.x,
						x.y | y.y,
						x.z | y.z};
	}

	/**
		Vector right-hand value bitwise-XOR (all components).

		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator^(
		tvec3<T> const& x,
		T const& y
	) {
		return tvec3<T>{x.x ^ y,
						x.y ^ y,
						x.z ^ y};
	}
	/**
		Vector left-hand value bitwise-XOR (all components).

		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator^(
		T const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x ^ y.x,
						x ^ y.y,
						x ^ y.z};
	}
	/**
		Vector bitwise-XOR.

		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator^(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x.x ^ y.x,
						x.y ^ y.y,
						x.z ^ y.z};
	}

	/**
		Vector right-hand value bitwise left-shift (all components).

		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator<<(
		tvec3<T> const& x,
		T const& y
	) {
		return tvec3<T>{x.x << y,
						x.y << y,
						x.z << y};
	}
	/**
		Vector left-hand value bitwise left-shift (all components).

		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator<<(
		T const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x << y.x,
						x << y.y,
						x << y.z};
	}
	/**
		Vector bitwise left-shift.

		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator<<(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x.x << y.x,
						x.y << y.y,
						x.z << y.z};
	}

	/**
		Vector right-hand value bitwise right-shift (all components).
		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator>>(
		tvec3<T> const& x,
		T const& y
	) {
		return tvec3<T>{x.x >> y,
						x.y >> y,
						x.z >> y};
	}
	/**
		Vector left-hand value bitwise right-shift (all components).

		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator>>(
		T const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x >> y.x,
						x >> y.y,
						x >> y.z};
	}
	/**
		Vector bitwise right-shift.

		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<class T>
	inline tvec3<T>
	operator>>(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return tvec3<T>{x.x >> y.x,
						x.y >> y.y,
						x.z >> y.z};
	}
/// @}

/** @} */ // end of doc-group vec3
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am
