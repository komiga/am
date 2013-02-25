/**
@file detail/linear/tvec2.hpp
@brief 2-dimensional vector.

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_DETAIL_LINEAR_TVEC2_HPP_
#define AM_DETAIL_LINEAR_TVEC2_HPP_

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
template<typename T> struct tvec2;
template<typename T> struct tvec3;
template<typename T> struct tvec4;

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
template<typename T>
struct tvec2 {
	/** @cond INTERNAL */
	AM_STATIC_ASSERT(
		true==std::is_arithmetic<T>::value,
		"T must be an arithmetic type"
	);
	/** @endcond */

	/** Type of @c *this. */
	typedef tvec2<T> type;
	/** Type of components. */
	typedef T value_type;
	/** Size/length type. */
	typedef std::size_t size_type;

	/** Dummy enum for constructing uninitialized vectors. */
	enum ctor_no_init {no_init};

/** @name Fields */ /// @{
	value_type x; /**< X value. */
	value_type y; /**< Y value. */
/// @}

/** @cond INTERNAL */
	struct operations {
	typedef type const& type_cref;
	typedef value_type const& value_cref;

	static value_type length(type_cref v) {
		return std::sqrt(v.x * v.x + v.y * v.y);
	}
	static value_type distance(type_cref v, type_cref r) {
		return operations::length(r - v);
	}
	static value_type dot(type_cref v, type_cref r) {
		return v.x * r.x + v.y * r.y;
	}
	static type normalize(type_cref v) {
		return v * (value_type(1) / std::sqrt(v.x * v.x + v.y * v.y));
	}
	static type faceforward(type_cref n, type_cref i, type_cref ng) {
		return dot(ng, i) < 0 ? n : -n;
	}
	static type reflect(type_cref i, type_cref n) {
		return i - value_type(2) * n * dot(n, i);
	}
	static type refract(type_cref i, type_cref n, value_cref eta) {
		value_type const d=dot(n, i);
		value_type const k=value_type(1) - eta * eta * (value_type(1) - d * d);
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
	tvec2() :
		x{T(0)}, y{T(0)} {}
	/**
		Construct uninitialized.
	*/
	explicit tvec2(ctor_no_init) {}

	/**
		Construct all components to value.
		@param s Value.
	*/
	explicit tvec2(value_type const& s) :
		x{s}, y{s} {}
	/**
		Construct all components to value.
		@tparam U An arithmetic type.
		@param s Value.
	*/
	template<typename U>
	explicit tvec2(U const& s) :
		x{T(s)}, y{T(s)} {}

	/**
		Construct to values.
		@param c1 X value.
		@param c2 Y value.
	*/
	explicit tvec2(value_type const& c1, value_type const& c2) :
		x{c1}, y{c2} {}
	/**
		Construct to values.
		@tparam U, V An arithmetic type.
		@param c1 X value.
		@param c2 Y value.
	*/
	template<typename U, typename V>
	explicit tvec2(U const& c1, V const& c2) :
		x{T(c1)}, y{T(c2)} {}

	/**
		Construct to vector.
		@param v Vector to copy.
	*/
	tvec2(type const& v) :
		x{v.x}, y{v.y} {}
	/**
		Construct to vector.
		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<typename U>
	tvec2(tvec2<U> const& v) :
		x{T(v.x)}, y{T(v.y)} {}
	
	/**
		Construct to higher-dimension vector.
		@note Higher-dimension components will be ignored.
		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<typename U>
	explicit tvec2(tvec3<U> const& v) :
		x{T(v.x)}, y{T(v.y)} {}
	/** @copydoc tvec2(tvec3<U> const&) */
	template<typename U>
	explicit tvec2(tvec4<U> const& v) :
		x{T(v.x)}, y{T(v.y)} {}
/// @}

/** @name Properties */ /// @{
	/**
		Get number of components.
		@returns @c 2.
	*/
	static AM_CONSTEXPR size_type size() { return size_type(2); }
	/**
		Get value at index.
		@note An assert will catch invalid indices;
		see fields for completely raw access.
		@returns The value at @a i.
		@param i Index to retrieve.
	*/
	value_type& operator[](size_type const& i) {
		assert(size()>i);
		return (&x)[i];
	}
	/** @copydoc operator[](size_type const&) */
	value_type const& operator[](size_type const& i) const {
		assert(size()>i);
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
	bool operator==(type const& v) const {
		return
			this->x==v.x &&
			this->y==v.y;
	}
	/**
		Non-equivalence operator.
		@returns
		- @c false if the two vectors are equal,
		- @c true if they are not.
		@param v Vector to compare with.
	*/
	bool operator!=(type const& v) const {
		return
			this->x!=v.x ||
			this->y!=v.y;
	}
/// @}

/** @name Increment and decrement operators */ /// @{
	/**
		Prefix increment.
		@returns @c *this after operation.
	*/
	type& operator++() {
		++this->x;
		++this->y;
		return *this;
	}
	/**
		Prefix decrement.
		@returns @c *this after operation.
	*/
	type& operator--() {
		--this->x;
		--this->y;
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
	template<typename U>
	type& operator=(U const& s) {
		this->x=T(s);
		this->y=T(s);
		return *this;
	}
	/**
		Assign to vector.
		@returns @c *this after assignment.
		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<typename U>
	type& operator=(tvec2<U> const& v) {
		this->x=T(v.x);
		this->y=T(v.y);
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
	type& operator+=(U const& s) {
		this->x+=T(s);
		this->y+=T(s);
		return *this;
	}
	/**
		Add vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to add.
	*/
	template<typename U>
	type& operator+=(tvec2<U> const& v) {
		this->x+=T(v.x);
		this->y+=T(v.y);
		return *this;
	}
	/**
		Subtract value from all components.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to subtract.
	*/
	template<typename U>
	type& operator-=(U const& s) {
		this->x-=T(s);
		this->y-=T(s);
		return *this;
	}
	/**
		Subtract vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to subtract.
	*/
	template<typename U>
	type& operator-=(tvec2<U> const& v) {
		this->x-=T(v.x);
		this->y-=T(v.y);
		return *this;
	}
	/**
		Multiply by scalar.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Scalar.
	*/
	template<typename U>
	type& operator*=(U const& s) {
		this->x*=T(s);
		this->y*=T(s);
		return *this;
	}
	/**
		Multiply by vector (direct component product).
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to multiply by.
	*/
	template<typename U>
	type& operator*=(tvec2<U> const& v) {
		this->x*=T(v.x);
		this->y*=T(v.y);
		return *this;
	}
	/**
		Divide all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to divide by.
	*/
	template<typename U>
	type& operator/=(U const& s) {
		this->x/=T(s);
		this->y/=T(s);
		return *this;
	}
	/**
		Divide by vector (direct component quotient).
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to divide by.
	*/
	template<typename U>
	type& operator/=(tvec2<U> const& v) {
		this->x/=T(v.x);
		this->y/=T(v.y);
		return *this;
	}
	/**
		Modulo all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Divisor.
	*/
	template<typename U>
	type& operator%=(U const& s) {
		this->x%=T(s);
		this->y%=T(s);
		return *this;
	}
	/**
		Modulo by vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Divisor vector.
	*/
	template<typename U>
	type& operator%=(tvec2<U> const& v) {
		this->x%=T(v.x);
		this->y%=T(v.y);
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
	template<typename U>
	type& operator&=(U const& s) {
		this->x&=T(s);
		this->y&=T(s);
		return *this;
	}
	/**
		Bitwise-AND vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to AND with.
	*/
	template<typename U>
	type& operator&=(tvec2<U> const& v) {
		this->x&=T(v.x);
		this->y&=T(v.y);
		return *this;
	}
	/**
		Bitwise-OR all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to OR with.
	*/
	template<typename U>
	type& operator|=(U const& s) {
		this->x|=T(s);
		this->y|=T(s);
		return *this;
	}
	/**
		Bitwise-OR vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to OR with.
	*/
	template<typename U>
	type& operator|=(tvec2<U> const& v) {
		this->x|=T(v.x);
		this->y|=T(v.y);
		return *this;
	}
	/**
		Bitwise-XOR all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to XOR with.
	*/
	template<typename U>
	type& operator^=(U const& s) {
		this->x^=T(s);
		this->y^=T(s);
		return *this;
	}
	/**
		Bitwise-XOR vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to XOR with.
	*/
	template<typename U>
	type& operator^=(tvec2<U> const& v) {
		this->x^=T(v.x);
		this->y^=T(v.y);
		return *this;
	}
	/**
		Bitwise left-shift all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Left-shift value amount.
	*/
	template<typename U>
	type& operator<<=(U const& s) {
		this->x<<=T(s);
		this->y<<=T(s);
		return *this;
	}
	/**
		Bitwise left-shift vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Left-shift vector amount.
	*/
	template<typename U>
	type& operator<<=(tvec2<U> const& v) {
		this->x<<=T(v.x);
		this->y<<=T(v.y);
		return *this;
	}
	/**
		Bitwise right-shift all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Right-shift value amount.
	*/
	template<typename U>
	type& operator>>=(U const& s) {
		this->x>>=T(s);
		this->y>>=T(s);
		return *this;
	}
	/**
		Bitwise right-shift vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Right-shift vector amount.
	*/
	template<typename U>
	type& operator>>=(tvec2<U> const& v) {
		this->x>>=T(v.x);
		this->y>>=T(v.y);
		return *this;
	}
/// @}
}; // struct tvec2

/** @name vec2 increment and decrement operators */ /// @{
	/**
		Vector postfix increment.
		@returns New vector with @c x+1.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec2<T> operator++(tvec2<T> const& x, signed) {
		return tvec2<T>{x.x+T(1), x.y+T(1)};
	}
	/**
		Vector postfix decrement.
		@returns New vector with @c x-1.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec2<T> operator--(tvec2<T> const& x, signed) {
		return tvec2<T>{x.x-T(1), x.y-T(1)};
	}
/// @}

/** @name vec2 unary operators */ /// @{
	/**
		Vector unary plus.
		@returns New vector with exact value of @a x.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec2<T> operator+(tvec2<T> const& x) {
		return tvec2<T>{x.x, x.y};
	}
	/**
		Vector unary minus.
		@returns New vector with @c -x.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec2<T> operator-(tvec2<T> const& x) {
		return tvec2<T>{	-x.x,
							-x.y};
	}
	/**
		Vector unary bitwise-NOT.
		@returns New vector with @c ~x.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec2<T> operator~(tvec2<T> const& x) {
		return tvec2<T>{	~x.x,
							~x.y};
	}
/// @}

/** @name vec2 arithmetic operators */ /// @{
	/**
		Vector right-hand value addition (all components).
		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator+(tvec2<T> const& x, T const& y) {
		return tvec2<T>{x.x + y,
						x.y + y};
	}
	/**
		Vector left-hand value addition (all components).
		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator+(T const& x, tvec2<T> const& y) {
		return tvec2<T>{  x + y.x,
						  x + y.y};
	}
	/**
		Vector addition.
		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator+(tvec2<T> const& x, tvec2<T> const& y) {
		return tvec2<T>{x.x + y.x,
						x.y + y.y};
	}
	/**
		Vector right-hand value subtraction (all components).
		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator-(tvec2<T> const& x, T const& y) {
		return tvec2<T>{x.x - y,
						x.y - y};
	}
	/**
		Vector left-hand value subtraction (all components).
		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator-(T const& x, tvec2<T> const& y) {
		return tvec2<T>{  x - y.x,
						  x - y.y};
	}
	/**
		Vector subtraction.
		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator-(tvec2<T> const& x, tvec2<T> const& y) {
		return tvec2<T>{x.x - y.x,
						x.y - y.y};
	}
	/**
		Vector right-hand scalar multiplication (all components).
		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator*(tvec2<T> const& x, T const& y) {
		return tvec2<T>{x.x * y,
						x.y * y};
	}
	/**
		Vector left-hand scalar multiplication (all components).
		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator*(T const& x, tvec2<T> const& y) {
		return tvec2<T>{  x * y.x,
						  x * y.y};
	}
	/**
		Vector multiplication (direct component product).
		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator*(tvec2<T> const& x, tvec2<T> const& y) {
		return tvec2<T>{x.x * y.x,
						x.y * y.y};
	}
	/**
		Vector right-hand value division (all components).
		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator/(tvec2<T> const& x, T const& y) {
		return tvec2<T>{x.x / y,
						x.y / y};
	}
	/**
		Vector left-hand value division (all components).
		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator/(T const& x, tvec2<T> const& y) {
		return tvec2<T>{  x / y.x,
						  x / y.y};
	}
	/**
		Vector division (direct component quotient).
		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator/(tvec2<T> const& x, tvec2<T> const& y) {
		return tvec2<T>{x.x / y.x,
						x.y / y.y};
	}
	/**
		Vector right-hand value modulo (all components).
		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator%(tvec2<T> const& x, T const& y) {
		return tvec2<T>{x.x % y,
						x.y % y};
	}
	/**
		Vector left-hand value modulo (all components).
		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator%(T const& x, tvec2<T> const& y) {
		return tvec2<T>{  x % y.x,
						  x % y.y};
	}
	/**
		Vector modulo.
		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator%(tvec2<T> const& x, tvec2<T> const& y) {
		return tvec2<T>{x.x % y.x,
						x.y % y.y};
	}
/// @}

/** @name vec2 bitwise operators */ /// @{
	/**
		Vector right-hand value bitwise-AND (all components).
		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator&(tvec2<T> const& x, T const& y) {
		return tvec2<T>{x.x & y,
						x.y & y};
	}
	/**
		Vector left-hand value bitwise-AND (all components).
		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator&(T const& x, tvec2<T> const& y) {
		return tvec2<T>{  x & y.x,
						  x & y.y};
	}
	/**
		Vector bitwise-AND.
		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator&(tvec2<T> const& x, tvec2<T> const& y) {
		return tvec2<T>{x.x & y.x,
						x.y & y.y};
	}
	/**
		Vector right-hand value bitwise-OR (all components).
		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator|(tvec2<T> const& x, T const& y) {
		return tvec2<T>{x.x | y,
						x.y | y};
	}
	/**
		Vector left-hand value bitwise-OR (all components).
		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator|(T const& x, tvec2<T> const& y) {
		return tvec2<T>{  x | y.x,
						  x | y.y};
	}
	/**
		Vector bitwise-OR.
		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator|(tvec2<T> const& x, tvec2<T> const& y) {
		return tvec2<T>{x.x | y.x,
						x.y | y.y};
	}
	/**
		Vector right-hand value bitwise-XOR (all components).
		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator^(tvec2<T> const& x, T const& y) {
		return tvec2<T>{x.x ^ y,
						x.y ^ y};
	}
	/**
		Vector left-hand value bitwise-XOR (all components).
		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator^(T const& x, tvec2<T> const& y) {
		return tvec2<T>{  x ^ y.x,
						  x ^ y.y};
	}
	/**
		Vector bitwise-XOR.
		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator^(tvec2<T> const& x, tvec2<T> const& y) {
		return tvec2<T>{x.x ^ y.x,
						x.y ^ y.y};
	}
	/**
		Vector right-hand value bitwise left-shift (all components).
		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator<<(tvec2<T> const& x, T const& y) {
		return tvec2<T>{x.x << y,
						x.y << y};
	}
	/**
		Vector left-hand value bitwise left-shift (all components).
		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator<<(T const& x, tvec2<T> const& y) {
		return tvec2<T>{  x << y.x,
						  x << y.y};
	}
	/**
		Vector bitwise left-shift.
		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator<<(tvec2<T> const& x, tvec2<T> const& y) {
		return tvec2<T>{x.x << y.x,
						x.y << y.y};
	}
	/**
		Vector right-hand value bitwise right-shift (all components).
		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator>>(tvec2<T> const& x, T const& y) {
		return tvec2<T>{x.x >> y,
						x.y >> y};
	}
	/**
		Vector left-hand value bitwise right-shift (all components).
		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator>>(T const& x, tvec2<T> const& y) {
		return tvec2<T>{  x >> y.x,
						  x >> y.y};
	}
	/**
		Vector bitwise right-shift.
		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec2<T> operator>>(tvec2<T> const& x, tvec2<T> const& y) {
		return tvec2<T>{x.x >> y.x,
						x.y >> y.y};
	}
/// @}

/** @} */ // end of doc-group vec2
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace detail
} // namespace am

#endif // AM_DETAIL_LINEAR_TVEC2_HPP_
