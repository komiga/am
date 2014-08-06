/**
@file detail/linear/tvec3_interface.hpp
@brief 3-dimensional vector (interface).

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../../config.hpp"
#include "./tvec3.hpp"

#include <cmath>

namespace am {
namespace detail {
namespace linear {

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

/** @cond INTERNAL */
template<class T>
struct tvec3<T>::operations {
	using type = typename tvec3<T>::type;
	using type_cref = type const&;
	using value_type = typename type::value_type;
	using value_cref = typename type::value_type const&;

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
}; // struct tvec3<T>::operators
/** @endcond */ // INTERNAL

/** @name vec3 comparison operators */ /// @{
	/**
		Equivalence operator.

		@returns
		- @c true if the two vectors are equal,
		- @c false if they are not.
	*/
	template<class T>
	inline bool
	operator==(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return
			x.x == y.x &&
			x.y == y.y &&
			x.z == y.z;
	}

	/**
		Non-equivalence operator.

		@returns
		- @c false if the two vectors are equal,
		- @c true if they are not.
	*/
	template<class T>
	inline bool
	operator!=(
		tvec3<T> const& x,
		tvec3<T> const& y
	) {
		return
			x.x != y.x ||
			x.y != y.y ||
			x.z != y.z;
	}
/// @}

/** @name vec3 arithmetic assignment operators */ /// @{
	/**
		Add value to all components.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator+=(
		tvec3<T>& x,
		U const& s
	) {
		x.x += T(s);
		x.y += T(s);
		x.z += T(s);
		return x;
	}
	/**
		Add vector.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator+=(
		tvec3<T>& x,
		tvec3<U> const& y
	) {
		x.x += T(y.x);
		x.y += T(y.y);
		x.z += T(y.z);
		return x;
	}

	/**
		Subtract value from all components.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator-=(
		tvec3<T>& x,
		U const& s
	) {
		x.x -= T(s);
		x.y -= T(s);
		x.z -= T(s);
		return x;
	}
	/**
		Subtract vector.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator-=(
		tvec3<T>& x,
		tvec3<U> const& y
	) {
		x.x -= T(y.x);
		x.y -= T(y.y);
		x.z -= T(y.z);
		return x;
	}

	/**
		Multiply by scalar.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator*=(
		tvec3<T>& x,
		U const& s
	) {
		x.x *= T(s);
		x.y *= T(s);
		x.z *= T(s);
		return x;
	}
	/**
		Multiply by vector (direct component product).

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator*=(
		tvec3<T>& x,
		tvec3<U> const& y
	) {
		x.x *= T(y.x);
		x.y *= T(y.y);
		x.z *= T(y.z);
		return x;
	}

	/**
		Divide all components by value.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator/=(
		tvec3<T>& x,
		U const& s
	) {
		x.x /= T(s);
		x.y /= T(s);
		x.z /= T(s);
		return x;
	}
	/**
		Divide by vector (direct component quotient).

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator/=(
		tvec3<T>& x,
		tvec3<U> const& y
	) {
		x.x /= T(y.x);
		x.y /= T(y.y);
		x.z /= T(y.z);
		return x;
	}

	/**
		Modulo all components by value.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator%=(
		tvec3<T>& x,
		U const& s
	) {
		x.x %= T(s);
		x.y %= T(s);
		x.z %= T(s);
		return x;
	}
	/**
		Modulo by vector.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator%=(
		tvec3<T>& x,
		tvec3<U> const& y
	) {
		x.x %= T(y.x);
		x.y %= T(y.y);
		x.z %= T(y.z);
		return x;
	}
/// @}

/** @name vec3 bitwise assignment operators */ /// @{
	/**
		Bitwise-AND all components by value.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator&=(
		tvec3<T>& x,
		U const& s
	) {
		x.x &= T(s);
		x.y &= T(s);
		x.z &= T(s);
		return x;
	}
	/**
		Bitwise-AND vector.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator&=(
		tvec3<T>& x,
		tvec3<U> const& y
	) {
		x.x &= T(y.x);
		x.y &= T(y.y);
		x.z &= T(y.z);
		return x;
	}

	/**
		Bitwise-OR all components by value.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator|=(
		tvec3<T>& x,
		U const& s
	) {
		x.x |= T(s);
		x.y |= T(s);
		x.z |= T(s);
		return x;
	}
	/**
		Bitwise-OR vector.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator|=(
		tvec3<T>& x,
		tvec3<U> const& y
	) {
		x.x |= T(y.x);
		x.y |= T(y.y);
		x.z |= T(y.z);
		return x;
	}

	/**
		Bitwise-XOR all components by value.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator^=(
		tvec3<T>& x,
		U const& s
	) {
		x.x ^= T(s);
		x.y ^= T(s);
		x.z ^= T(s);
		return x;
	}
	/**
		Bitwise-XOR vector.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator^=(
		tvec3<T>& x,
		tvec3<U> const& y
	) {
		x.x ^= T(y.x);
		x.y ^= T(y.y);
		x.z ^= T(y.z);
		return x;
	}

	/**
		Bitwise left-shift all components by value.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator<<=(
		tvec3<T>& x,
		U const& s
	) {
		x.x <<= T(s);
		x.y <<= T(s);
		x.z <<= T(s);
		return x;
	}
	/**
		Bitwise left-shift vector.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator<<=(
		tvec3<T>& x,
		tvec3<U> const& y
	) {
		x.x <<= T(y.x);
		x.y <<= T(y.y);
		x.z <<= T(y.z);
		return x;
	}

	/**
		Bitwise right-shift all components by value.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator>>=(
		tvec3<T>& x,
		U const& s
	) {
		x.x >>= T(s);
		x.y >>= T(s);
		x.z >>= T(s);
		return x;
	}
	/**
		Bitwise right-shift vector.

		@returns @a x after operation.
	*/
	template<class T, class U>
	inline tvec3<T>&
	operator>>=(
		tvec3<T>& x,
		tvec3<U> const& y
	) {
		x.x >>= T(y.x);
		x.y >>= T(y.y);
		x.z >>= T(y.z);
		return x;
	}
/// @}

/** @name vec3 increment and decrement operators */ /// @{
	/**
		Prefix increment.

		@returns @a x after operation.
	*/
	template<class T>
	inline tvec3<T>&
	operator++(
		tvec3<T>& x
	) {
		++x.x;
		++x.y;
		++x.z;
		return x;
	}

	/**
		Prefix decrement.

		@returns @a x after operation.
	*/
	template<class T>
	inline tvec3<T>&
	operator--(
		tvec3<T>& x
	) {
		--x.x;
		--x.y;
		--x.z;
		return x;
	}

	/**
		Vector postfix increment.

		@returns @a x before operation.
	*/
	template<class T>
	inline tvec3<T> operator++(
		tvec3<T>& x,
		signed
	) {
		tvec3<T> c{x};
		++x;
		return c;
	}

	/**
		Vector postfix decrement.

		@returns @a x before operation.
	*/
	template<class T>
	inline tvec3<T> operator--(
		tvec3<T>& x,
		signed
	) {
		tvec3<T> c{x};
		--x;
		return c;
	}
/// @}

/** @name vec3 unary operators */ /// @{
	/**
		Vector unary plus.

		@returns New vector with exact value of @a x.
	*/
	template<class T>
	inline tvec3<T> operator+(
		tvec3<T> const& x
	) {
		return tvec3<T>{x.x, x.y, x.z};
	}

	/**
		Vector unary minus.

		@returns New vector with @c -x.
	*/
	template<class T>
	inline tvec3<T> operator-(
		tvec3<T> const& x
	) {
		return tvec3<T>{-x.x,
						-x.y,
						-x.z};
	}

	/**
		Vector unary bitwise-NOT.

		@returns New vector with @c ~x.
	*/
	template<class T>
	inline tvec3<T> operator~(
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
	*/
	template<class T>
	inline tvec3<T> operator+(
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
	*/
	template<class T>
	inline tvec3<T> operator+(
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
	*/
	template<class T>
	inline tvec3<T> operator+(
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
	*/
	template<class T>
	inline tvec3<T> operator-(
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
	*/
	template<class T>
	inline tvec3<T> operator-(
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
	*/
	template<class T>
	inline tvec3<T> operator-(
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
	*/
	template<class T>
	inline tvec3<T> operator*(
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
	*/
	template<class T>
	inline tvec3<T> operator*(
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
	*/
	template<class T>
	inline tvec3<T> operator*(
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
	*/
	template<class T>
	inline tvec3<T> operator/(
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
	*/
	template<class T>
	inline tvec3<T> operator/(
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
	*/
	template<class T>
	inline tvec3<T> operator/(
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
	*/
	template<class T>
	inline tvec3<T> operator%(
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
	*/
	template<class T>
	inline tvec3<T> operator%(
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
	*/
	template<class T>
	inline tvec3<T> operator%(
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
	*/
	template<class T>
	inline tvec3<T> operator&(
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
	*/
	template<class T>
	inline tvec3<T> operator&(
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
	*/
	template<class T>
	inline tvec3<T> operator&(
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
	*/
	template<class T>
	inline tvec3<T> operator|(
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
	*/
	template<class T>
	inline tvec3<T> operator|(
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
	*/
	template<class T>
	inline tvec3<T> operator|(
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
	*/
	template<class T>
	inline tvec3<T> operator^(
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
	*/
	template<class T>
	inline tvec3<T> operator^(
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
	*/
	template<class T>
	inline tvec3<T> operator^(
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
	*/
	template<class T>
	inline tvec3<T> operator<<(
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
	*/
	template<class T>
	inline tvec3<T> operator<<(
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
	*/
	template<class T>
	inline tvec3<T> operator<<(
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
	*/
	template<class T>
	inline tvec3<T> operator>>(
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
	*/
	template<class T>
	inline tvec3<T> operator>>(
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
	*/
	template<class T>
	inline tvec3<T> operator>>(
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
