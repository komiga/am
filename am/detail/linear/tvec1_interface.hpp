/**
@file detail/linear/tvec1_interface.hpp
@brief 1-dimensional vector (interface).

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../../config.hpp"
#include "./tvec1.hpp"

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
	@addtogroup vec1
	@{
*/

/** @cond INTERNAL */
template<class T>
struct tvec1<T>::operations {
	using type = typename tvec1<T>::type;
	using type_cref = type const&;
	using value_type = typename type::value_type;
	using value_cref = typename type::value_type const&;

	static value_type
	length(
		type_cref v
	) {
		return std::abs(v.x);
	}

	static value_type
	distance(
		type_cref v,
		type_cref r
	) {
		return std::abs(r.x - v.x);
	}

	static value_type
	dot(
		type_cref v,
		type_cref r
	) {
		return v.x * r.x;
	}

	static type
	normalize(
		type_cref v
	) {
		return v.x < value_type(0) ? type(-1) : type(1);
	}

	static type
	faceforward(
		type_cref n,
		type_cref i,
		type_cref ng
	) {
		return dot(ng, i) < 0 ? type{n} : type{-n.x};
	}

	static type
	reflect(
		type_cref i,
		type_cref n
	) {
		return i.x - value_type(2) * n.x * dot(n, i);
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
			: type{eta * i.x - (eta * d + std::sqrt(k)) * n.x};
	}
}; // struct tvec1<T>::operations
/** @endcond */ // INTERNAL

/** @name vec1 comparison operators */ /// @{
	/**
		Equivalence operator.

		@returns
		- @c true if the two vectors are equal,
		- @c false if they are not.
	*/
	template<class T>
	inline bool
	operator==(
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return x.x == y.x;
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
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return x.x != y.x;
	}
/// @}

/** @name vec1 arithmetic assignment operators */ /// @{
	/**
		Add value.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator+=(
		tvec1<T>& x,
		U const& s
	) {
		x.x += T(s);
		return x;
	}
	/**
		Add vector.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator+=(
		tvec1<T>& x,
		tvec1<U> const& y
	) {
		x.x += T(y.x);
		return x;
	}

	/**
		Subtract value.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator-=(
		tvec1<T>& x,
		U const& s
	) {
		x.x -= T(s);
		return x;
	}
	/**
		Subtract vector.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator-=(
		tvec1<U> const& x,
		tvec1<U> const& y
	) {
		x.x -= T(y.x);
		return x;
	}

	/**
		Multiply by scalar.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator*=(
		tvec1<T>& x,
		U const& s
	) {
		x.x *= T(s);
		return x;
	}
	/**
		Multiply by vector (direct component product).

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator*=(
		tvec1<T>& x,
		tvec1<U> const& y
	) {
		x.x *= T(y.x);
		return x;
	}

	/**
		Divide by value.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator/=(
		tvec1<T>& x,
		U const& s
	) {
		x.x /= T(s);
		return x;
	}
	/**
		Divide by vector (direct component quotient).

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator/=(
		tvec1<T>& x,
		tvec1<U> const& y
	) {
		x.x /= T(y.x);
		return x;
	}

	/**
		Modulo by value.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator%=(
		tvec1<T>& x,
		U const& s
	) {
		x.x %= T(s);
		return x;
	}
	/**
		Modulo by vector.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator%=(
		tvec1<T>& x,
		tvec1<U> const& y
	) {
		x.x %= T(y.x);
		return x;
	}
/// @}

/** @name vec1 bitwise assignment operators */ /// @{
	/**
		Bitwise-AND value.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator&=(
		tvec1<T>& x,
		U const& s
	) {
		x.x &= T(s);
		return x;
	}
	/**
		Bitwise-AND vector.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator&=(
		tvec1<T>& x,
		tvec1<U> const& y
	) {
		x.x &= T(y.x);
		return x;
	}

	/**
		Bitwise-OR value.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator|=(
		tvec1<T>& x,
		U const& s
	) {
		x.x |= T(s);
		return x;
	}
	/**
		Bitwise-OR vector.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator|=(
		tvec1<T>& x,
		tvec1<U> const& y
	) {
		x.x |= T(y.x);
		return x;
	}

	/**
		Bitwise-XOR value.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator^=(
		tvec1<T>& x,
		U const& s
	) {
		x.x ^= T(s);
		return x;
	}
	/**
		Bitwise-XOR vector.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator^=(
		tvec1<T>& x,
		tvec1<U> const& y
	) {
		x.x ^= T(y.x);
		return x;
	}

	/**
		Bitwise left-shift value.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator<<=(
		tvec1<T>& x,
		U const& s
	) {
		x.x <<= T(s);
		return x;
	}
	/**
		Bitwise left-shift vector.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator<<=(
		tvec1<T>& x,
		tvec1<U> const& y
	) {
		x.x <<= T(y.x);
		return x;
	}

	/**
		Bitwise right-shift value.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator>>=(
		tvec1<T>& x,
		U const& s
	) {
		x.x >>= T(s);
		return x;
	}
	/**
		Bitwise right-shift vector.

		@returns @a x after assignment.
	*/
	template<class T, class U>
	inline tvec1<T>&
	operator>>=(
		tvec1<T>& x,
		tvec1<U> const& y
	) {
		x.x >>= T(y.x);
		return x;
	}
/// @}

/** @name vec1 increment and decrement operators */ /// @{
	/**
		Vector prefix increment.

		@returns @a x after operation.
	*/
	template<class T>
	inline tvec1<T>&
	operator++(
		tvec1<T>& x
	) {
		++x.x;
		return x;
	}

	/**
		Vector prefix decrement.

		@returns @a x after operation.
	*/
	template<class T>
	inline tvec1<T>&
	operator--(
		tvec1<T>& x
	) {
		--x.x;
		return x;
	}

	/**
		Vector postfix increment.

		@returns New vector with @c x+1.
	*/
	template<class T>
	inline tvec1<T>
	operator++(
		tvec1<T> const& x,
		signed
	) {
		return tvec1<T>{x.x + T(1)};
	}

	/**
		Vector postfix decrement.

		@returns New vector with @c x-1.
	*/
	template<class T>
	inline tvec1<T>
	operator--(
		tvec1<T> const& x,
		signed
	) {
		return tvec1<T>{x.x - T(1)};
	}
/// @}

/** @name vec1 unary operators */ /// @{
	/**
		Vector unary plus.

		@returns New vector with exact value of @a x.
	*/
	template<class T>
	inline tvec1<T>
	operator+(
		tvec1<T> const& x
	) {
		return tvec1<T>{x.x};
	}

	/**
		Vector unary minus.

		@returns New vector with @c -x.
	*/
	template<class T>
	inline tvec1<T>
	operator-(
		tvec1<T> const& x
	) {
		return tvec1<T>{-x.x};
	}

	/**
		Vector unary bitwise-NOT.

		@returns New vector with @c ~x.
	*/
	template<class T>
	inline tvec1<T>
	operator~(
		tvec1<T> const& x
	) {
		return tvec1<T>{~x.x};
	}
/// @}

/** @name vec1 arithmetic operators */ /// @{
	/**
		Vector right-hand value addition.

		@returns New vector with @a x plus @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator+(
		tvec1<T> const& x,
		T const& y
	) {
		return tvec1<T>{x.x + y};
	}
	/**
		Vector left-hand value addition.

		@returns New vector with @a x plus @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator+(
		T const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x + y.x};
	}
	/**
		Vector addition.

		@returns New vector with @a x plus @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator+(
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x.x + y.x};
	}

	/**
		Vector right-hand value subtraction.

		@returns New vector with @a x minus @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator-(
		tvec1<T> const& x,
		T const& y
	) {
		return tvec1<T>{x.x - y};
	}
	/**
		Vector left-hand value subtraction.

		@returns New vector with @a x minus @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator-(
		T const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x - y.x};
	}
	/**
		Vector subtraction.

		@returns New vector with @a x minus @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator-(
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x.x - y.x};
	}

	/**
		Vector right-hand scalar multiplication.

		@returns New vector with @a x times @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator*(
		tvec1<T> const& x,
		T const& y
	) {
		return tvec1<T>{x.x * y};
	}
	/**
		Vector left-hand scalar multiplication.

		@returns New vector with @a x times @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator*(
		T const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x * y.x};
	}
	/**
		Vector multiplication (direct component product).

		@returns New vector with @a x times @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator*(
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x.x * y.x};
	}

	/**
		Vector right-hand value division.

		@returns New vector with @a x divided by @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator/(
		tvec1<T> const& x,
		T const& y
	) {
		return tvec1<T>{x.x / y};
	}
	/**
		Vector left-hand value division.

		@returns New vector with @a x divided by @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator/(
		T const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x / y.x};
	}
	/**
		Vector division (direct component quotient).

		@returns New vector with @a x divided by @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator/(
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x.x / y.x};
	}

	/**
		Vector right-hand value modulo.

		@returns New vector with @a x modulo @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator%(
		tvec1<T> const& x,
		T const& y
	) {
		return tvec1<T>{x.x % y};
	}
	/**
		Vector left-hand value modulo.

		@returns New vector with @a x modulo @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator%(
		T const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x % y.x};
	}
	/**
		Vector modulo.

		@returns New vector with @a x modulo @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator%(
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x.x % y.x};
	}
/// @}

/** @name vec1 bitwise operators */ /// @{
	/**
		Vector right-hand value bitwise-AND.

		@returns New vector with @a x AND @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator&(
		tvec1<T> const& x,
		T const& y
	) {
		return tvec1<T>{x.x & y};
	}
	/**
		Vector left-hand value bitwise-AND.

		@returns New vector with @a x AND @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator&(
		T const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x & y.x};
	}
	/**
		Vector bitwise-AND.

		@returns New vector with @a x AND @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator&(
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x.x & y.x};
	}

	/**
		Vector right-hand value bitwise-OR.

		@returns New vector with @a x OR @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator|(
		tvec1<T> const& x,
		T const& y
	) {
		return tvec1<T>{x.x | y};
	}
	/**
		Vector left-hand value bitwise-OR.

		@returns New vector with @a x OR @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator|(
		T const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x | y.x};
	}
	/**
		Vector bitwise-OR.

		@returns New vector with @a x OR @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator|(
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x.x | y.x};
	}

	/**
		Vector right-hand value bitwise-XOR.

		@returns New vector with @a x XOR @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator^(
		tvec1<T> const& x,
		T const& y
	) {
		return tvec1<T>{x.x ^ y};
	}
	/**
		Vector left-hand value bitwise-XOR.

		@returns New vector with @a x XOR @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator^(
		T const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x ^ y.x};
	}
	/**
		Vector bitwise-XOR.

		@returns New vector with @a x XOR @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator^(
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x.x ^ y.x};
	}

	/**
		Vector right-hand value bitwise left-shift.

		@returns New vector with @a x left-shift @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator<<(
		tvec1<T> const& x,
		T const& y
	) {
		return tvec1<T>{x.x << y};
	}
	/**
		Vector left-hand value bitwise left-shift.

		@returns New vector with @a x left-shift @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator<<(
		T const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x << y.x};
	}
	/**
		Vector bitwise left-shift.

		@returns New vector with @a x left-shift @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator<<(
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x.x << y.x};
	}

	/**
		Vector right-hand value bitwise right-shift.

		@returns New vector with @a x right-shift @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator>>(
		tvec1<T> const& x,
		T const& y
	) {
		return tvec1<T>{x.x >> y};
	}
	/**
		Vector left-hand value bitwise right-shift.

		@returns New vector with @a x right-shift @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator>>(
		T const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x >> y.x};
	}
	/**
		Vector bitwise right-shift.

		@returns New vector with @a x right-shift @a y.
	*/
	template<class T>
	inline tvec1<T>
	operator>>(
		tvec1<T> const& x,
		tvec1<T> const& y
	) {
		return tvec1<T>{x.x >> y.x};
	}
/// @}

/** @} */ // end of doc-group vec1
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am
