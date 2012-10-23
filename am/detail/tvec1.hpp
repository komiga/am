/**
@file detail/tvec1.hpp
@brief 1-dimensional vector.

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_DETAIL_TVEC1_HPP_
#define AM_DETAIL_TVEC1_HPP_

#include "../config.hpp"

#include <cassert>
#include <type_traits>

namespace am {
namespace detail {

// Forward declarations
template<typename T> struct tvec1;
template<typename T> struct tvec2;
template<typename T> struct tvec3;
template<typename T> struct tvec4;

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
*/
template<typename T>
struct tvec1 {
	/** @cond INTERNAL */
	AM_STATIC_ASSERT(true==std::is_arithmetic<T>::value, "T must be an arithmetic type");
	/** @endcond */

	/** Type of @c *this. */
	typedef tvec1<T> type;
	/** Type of components. */
	typedef T value_type;
	/** Size/length type. */
	typedef std::size_t size_type;

	/** Dummy enum for constructing uninitialized vectors. */
	enum ctor_no_init {no_init};

	value_type x; /**< X value. */

/** @name Constructors */ /// @{
	/**
		Construct zeroed.
	*/
	inline tvec1() : x(T(0)) {}
	/**
		Construct uninitialized.
	*/
	inline explicit tvec1(ctor_no_init) {}
	/**
		Construct to value.
		@param c1 X value.
	*/
	inline explicit tvec1(value_type const& c1) : x(c1) {}
	/**
		Construct to value.
		@tparam U An arithmetic type.
		@param c1 X value.
	*/
	template<typename U>
	inline explicit tvec1(U const& c1) : x(T(c1)) {}

	/**
		Construct to vector.
		@param v Vector to copy.
	*/
	inline tvec1(type const& v) : x(v.x) {}
	/**
		Construct to vector.
		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<typename U>
	inline tvec1(tvec1<U> const& v) : x(T(v.x)) {}

	/**
		Construct to higher-dimension vector.
		@note Higher-dimension components will be ignored.
		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<typename U>
	inline explicit tvec1(tvec2<U> const& v) : x(T(v.x)) {}
	/** @copydoc tvec1(tvec2<U> const&) */
	template<typename U>
	inline explicit tvec1(tvec3<U> const& v) : x(T(v.x)) {}
	/** @copydoc tvec1(tvec2<U> const&) */
	template<typename U>
	inline explicit tvec1(tvec4<U> const& v) : x(T(v.x)) {}
/// @}

/** @name Properties */ /// @{
	/**
		Get vector length.
		@returns @c 1.
	*/
	inline AM_CONSTEXPR size_type length() const { return size_type(1); }
	/**
		Get value at index.
		@returns The value at @a i.
		@param i Index to retrieve.
	*/
	inline value_type& operator[](size_type const& i) {
		assert(length()>i);
		return this->x;
	}
	/** @copydoc operator[](size_type const&) */
	inline value_type const& operator[](size_type const& i) const {
		assert(length()>i);
		return this->x;
	}
/// @}

/** @name Comparison operators */ /// @{
	/**
		Equivalence operator.
		@returns @c true if the two vectors are equal, @c false if they are not.
		@param v Vector to compare with.
	*/
	inline bool operator==(type const& v) const {
		return this->x==v.x;
	}
	/**
		Non-equivalence operator.
		@returns @c false if the two vectors are equal, @c true if they are not.
		@param v Vector to compare with.
	*/
	inline bool operator!=(type const& v) const {
		return this->x!=v.x;
	}
/// @}

/** @name Increment and decrement operators */ /// @{
	/**
		Prefix increment.
		@returns @c *this after operation.
	*/
	inline type& operator++() {
		++this->x;
		return *this;
	}
	/**
		Prefix decrement.
		@returns @c *this after operation.
	*/
	inline type& operator--() {
		--this->x;
		return *this;
	}
/// @}

/** @name Assignment operators */ /// @{
	/**
		Assign to value.
		@returns @c *this after assignment.
		@tparam U An arithmetic type.
		@param s Value.
	*/
	template<typename U>
	inline type& operator=(U const& s) {
		this->x=T(s);
		return *this;
	}
	/**
		Assign to vector.
		@returns @c *this after assignment.
		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<typename U>
	inline type& operator=(tvec1<U> const& v) {
		this->x=T(v.x);
		return *this;
	}
/// @}

/** @name Arithmetic assignment operators */ /// @{
	/**
		Add value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to add.
	*/
	template<typename U>
	inline type& operator+=(U const& s) {
		this->x+=T(s);
		return *this;
	}
	/**
		Add vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to add.
	*/
	template<typename U>
	inline type& operator+=(tvec1<U> const& v) {
		this->x+=T(v.x);
		return *this;
	}
	/**
		Subtract value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to subtract.
	*/
	template<typename U>
	inline type& operator-=(U const& s) {
		this->x-=T(s);
		return *this;
	}
	/**
		Subtract vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to subtract.
	*/
	template<typename U>
	inline type& operator-=(tvec1<U> const& v) {
		this->x-=T(v.x);
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
		this->x*=T(s);
		return *this;
	}
	/**
		Multiply by vector (direct component product).
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to multiply by.
	*/
	template<typename U>
	inline type& operator*=(tvec1<U> const& v) {
		this->x*=T(v.x);
		return *this;
	}
	/**
		Divide by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to divide by.
	*/
	template<typename U>
	inline type& operator/=(U const& s) {
		this->x/=T(s);
		return *this;
	}
	/**
		Divide by vector (direct component quotient).
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to divide by.
	*/
	template<typename U>
	inline type& operator/=(tvec1<U> const& v) {
		this->x/=T(v.x);
		return *this;
	}
	/**
		Modulo by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Divisor.
	*/
	template<typename U>
	inline type& operator%=(U const& s) {
		this->x%=T(s);
		return *this;
	}
	/**
		Modulo by vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Divisor vector.
	*/
	template<typename U>
	inline type& operator%=(tvec1<U> const& v) {
		this->x%=T(v.x);
		return *this;
	}
/// @}

/** @name Bitwise assignment operators */ /// @{
	/**
		Bitwise-AND value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to AND with.
	*/
	template<typename U>
	inline type& operator&=(U const& s) {
		this->x&=T(s);
		return *this;
	}
	/**
		Bitwise-AND vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to AND with.
	*/
	template<typename U>
	inline type& operator&=(tvec1<U> const& v) {
		this->x&=T(v.x);
		return *this;
	}
	/**
		Bitwise-OR value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to OR with.
	*/
	template<typename U>
	inline type& operator|=(U const& s) {
		this->x|=T(s);
		return *this;
	}
	/**
		Bitwise-OR vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to OR with.
	*/
	template<typename U>
	inline type& operator|=(tvec1<U> const& v) {
		this->x|=T(v.x);
		return *this;
	}
	/**
		Bitwise-XOR value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to XOR with.
	*/
	template<typename U>
	inline type& operator^=(U const& s) {
		this->x^=T(s);
		return *this;
	}
	/**
		Bitwise-XOR vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to XOR with.
	*/
	template<typename U>
	inline type& operator^=(tvec1<U> const& v) {
		this->x^=T(v.x);
		return *this;
	}
	/**
		Bitwise left-shift value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Left-shift value amount.
	*/
	template<typename U>
	inline type& operator<<=(U const& s) {
		this->x<<=T(s);
		return *this;
	}
	/**
		Bitwise left-shift vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Left-shift vector amount.
	*/
	template<typename U>
	inline type& operator<<=(tvec1<U> const& v) {
		this->x<<=T(v.x);
		return *this;
	}
	/**
		Bitwise right-shift value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Right-shift value amount.
	*/
	template<typename U>
	inline type& operator>>=(U const& s) {
		this->x>>=T(s);
		return *this;
	}
	/**
		Bitwise right-shift vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Right-shift vector amount.
	*/
	template<typename U>
	inline type& operator>>=(tvec1<U> const& v) {
		this->x>>=T(v.x);
		return *this;
	}
/// @}
};

/** @name Increment and decrement operators */ /// @{
	/**
		Vector postfix increment.
		@returns New vector with @c x+1.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec1<T> operator++(tvec1<T> const& x, int) {
		return tvec1<T>{x.x+T(1)};
	}
	/**
		Vector postfix decrement.
		@returns New vector with @c x-1.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec1<T> operator--(tvec1<T> const& x, int) {
		return tvec1<T>{x.x-T(1)};
	}
/// @}

/** @name Unary operators */ /// @{
	/**
		Vector unary plus.
		@returns New vector with exact value of @a x.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec1<T> operator+(tvec1<T> const& x) {
		return tvec1<T>{x.x};
	}
	/**
		Vector unary minus.
		@returns New vector with @c -x.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec1<T> operator-(tvec1<T> const& x) {
		return tvec1<T>{-x.x};
	}
	/**
		Vector unary bitwise-NOT.
		@returns New vector with @c ~x.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec1<T> operator~(tvec1<T> const& x) {
		return tvec1<T>{~x.x};
	}
/// @}

/** @name Arithmetic operators */ /// @{
	/**
		Vector right-hand value addition.
		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator+(tvec1<T> const& x, T const& y) {
		return tvec1<T>{x.x + y};
	}
	/**
		Vector left-hand value addition.
		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator+(T const& x, tvec1<T> const& y) {
		return tvec1<T>{  x + y.x};
	}
	/**
		Vector addition.
		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator+(tvec1<T> const& x, tvec1<T> const& y) {
		return tvec1<T>{x.x + y.x};
	}
	/**
		Vector right-hand value subtraction.
		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator-(tvec1<T> const& x, T const& y) {
		return tvec1<T>{x.x - y};
	}
	/**
		Vector left-hand value subtraction.
		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator-(T const& x, tvec1<T> const& y) {
		return tvec1<T>{  x - y.x};
	}
	/**
		Vector subtraction.
		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator-(tvec1<T> const& x, tvec1<T> const& y) {
		return tvec1<T>{x.x - y.x};
	}
	/**
		Vector right-hand scalar multiplication.
		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator*(tvec1<T> const& x, T const& y) {
		return tvec1<T>{x.x * y};
	}
	/**
		Vector left-hand scalar multiplication.
		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator*(T const& x, tvec1<T> const& y) {
		return tvec1<T>{  x * y.x};
	}
	/**
		Vector multiplication (direct component product).
		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator*(tvec1<T> const& x, tvec1<T> const& y) {
		return tvec1<T>{x.x * y.x};
	}
	/**
		Vector right-hand value division.
		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator/(tvec1<T> const& x, T const& y) {
		return tvec1<T>{x.x / y};
	}
	/**
		Vector left-hand value division.
		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator/(T const& x, tvec1<T> const& y) {
		return tvec1<T>{  x / y.x};
	}
	/**
		Vector division (direct component quotient).
		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator/(tvec1<T> const& x, tvec1<T> const& y) {
		return tvec1<T>{x.x / y.x};
	}
	/**
		Vector right-hand value modulo.
		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator%(tvec1<T> const& x, T const& y) {
		return tvec1<T>{x.x % y};
	}
	/**
		Vector left-hand value modulo.
		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator%(T const& x, tvec1<T> const& y) {
		return tvec1<T>{  x % y.x};
	}
	/**
		Vector modulo.
		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator%(tvec1<T> const& x, tvec1<T> const& y) {
		return tvec1<T>{x.x % y.x};
	}
/// @}

/** @name Bitwise operators */ /// @{
	/**
		Vector right-hand value bitwise-AND.
		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator&(tvec1<T> const& x, T const& y) {
		return tvec1<T>{x.x & y};
	}
	/**
		Vector left-hand value bitwise-AND.
		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator&(T const& x, tvec1<T> const& y) {
		return tvec1<T>{  x & y.x};
	}
	/**
		Vector bitwise-AND.
		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator&(tvec1<T> const& x, tvec1<T> const& y) {
		return tvec1<T>{x.x & y.x};
	}
	/**
		Vector right-hand value bitwise-OR.
		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator|(tvec1<T> const& x, T const& y) {
		return tvec1<T>{x.x | y};
	}
	/**
		Vector left-hand value bitwise-OR.
		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator|(T const& x, tvec1<T> const& y) {
		return tvec1<T>{  x | y.x};
	}
	/**
		Vector bitwise-OR.
		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator|(tvec1<T> const& x, tvec1<T> const& y) {
		return tvec1<T>{x.x | y.x};
	}
	/**
		Vector right-hand value bitwise-XOR.
		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator^(tvec1<T> const& x, T const& y) {
		return tvec1<T>{x.x ^ y};
	}
	/**
		Vector left-hand value bitwise-XOR.
		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator^(T const& x, tvec1<T> const& y) {
		return tvec1<T>{  x ^ y.x};
	}
	/**
		Vector bitwise-XOR.
		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator^(tvec1<T> const& x, tvec1<T> const& y) {
		return tvec1<T>{x.x ^ y.x};
	}
	/**
		Vector right-hand value bitwise left-shift.
		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator<<(tvec1<T> const& x, T const& y) {
		return tvec1<T>{x.x << y};
	}
	/**
		Vector left-hand value bitwise left-shift.
		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator<<(T const& x, tvec1<T> const& y) {
		return tvec1<T>{  x << y.x};
	}
	/**
		Vector bitwise left-shift.
		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator<<(tvec1<T> const& x, tvec1<T> const& y) {
		return tvec1<T>{x.x << y.x};
	}
	/**
		Vector right-hand value bitwise right-shift.
		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator>>(tvec1<T> const& x, T const& y) {
		return tvec1<T>{x.x >> y};
	}
	/**
		Vector left-hand value bitwise right-shift.
		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator>>(T const& x, tvec1<T> const& y) {
		return tvec1<T>{  x >> y.x};
	}
	/**
		Vector bitwise right-shift.
		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec1<T> operator>>(tvec1<T> const& x, tvec1<T> const& y) {
		return tvec1<T>{x.x >> y.x};
	}
/// @}

/** @} */ // end of doc-group vec1
/** @} */ // end of doc-group vector

} // namespace detail
} // namespace am

#endif // AM_DETAIL_TVEC1_HPP_
