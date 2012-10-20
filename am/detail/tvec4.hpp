/**
@file detail/tvec4.hpp
@brief 4-dimensional vector.

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_DETAIL_TVEC4_HPP_
#define AM_DETAIL_TVEC4_HPP_

#include "../config.hpp"

#include <type_traits>

namespace am {
namespace detail {

// Forward declarations
template<typename T> struct tvec2;
template<typename T> struct tvec3;
template<typename T> struct tvec4;

/**
	@addtogroup vector
	@{
*/
/**
	@addtogroup vec4
	@{
*/

/**
	Generic 4-dimensional vector.
*/
template<typename T>
struct tvec4 {
	/** @cond INTERNAL */
	AM_STATIC_ASSERT(true==std::is_arithmetic<T>::value, "T must be an arithmetic type");
	/** @endcond */

	/** Type of @c *this. */
	typedef tvec4<T> type;
	/** Type of components. */
	typedef T value_type;
	/** Size/length type. */
	typedef std::size_t size_type;

	/** Dummy enum for constructing uninitialized vectors. */
	enum ctor_no_init {no_init};

	value_type x; /**< X value. */
	value_type y; /**< Y value. */
	value_type z; /**< Z value. */
	value_type w; /**< W value. */

/** @name Constructors */ /// @{
	/**
		Construct zeroed.
	*/
	inline tvec4() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
	/**
		Construct uninitialized.
	*/
	inline explicit tvec4(ctor_no_init) {}

	/**
		Construct all components to value.
		@param s Value.
	*/
	inline explicit tvec4(value_type const& s) : x(s), y(s), z(s), w(s) {}
	/**
		Construct all components to value.
		@tparam U An arithmetic type.
		@param s Value.
	*/
	template<typename U>
	inline explicit tvec4(U const& s) : x(T(s)), y(T(s)), z(T(s)), w(T(s)) {}

	/**
		Construct to values.
		@param c1 X value.
		@param c2 Y value.
		@param c3 Z value.
		@param c4 W value.
	*/
	inline explicit tvec4(value_type const& c1, value_type const& c2, value_type const& c3, value_type const& c4) : x(c1), y(c2), z(c3), w(c4) {}
	/**
		Construct to values.
		@tparam U, V, H, L An arithmetic type.
		@param c1 X value.
		@param c2 Y value.
		@param c3 Z value.
		@param c4 W value.
	*/
	template<typename U, typename V, typename H, typename L>
	inline explicit tvec4(U const& c1, V const& c2, H const& c3, L const& c4) : x(T(c1)), y(T(c2)), z(T(c3)), w(T(c4)) {}

	/**
		Construct to vector.
		@param v Vector to copy.
	*/
	inline tvec4(type const& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	/**
		Construct to vector.
		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<typename U>
	inline tvec4(tvec4<U> const& v) : x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w)) {}

	/**
		Construct to X value and YZW vector.
		@tparam U, V An arithmetic type.
		@param c1 X value.
		@param v Y, Z, and W vector.
	*/
	template<typename U, typename V>
	inline explicit tvec4(U const& c1, tvec3<V> const& v) : x(T(c1)), y(T(v.x)), z(T(v.y)), w(T(v.z)) {}
	/**
		Construct to XYZ vector and W value.
		@tparam U, V An arithmetic type.
		@param v X, Y, and Z vector.
		@param c4 W value.
	*/
	template<typename U, typename V>
	inline explicit tvec4(tvec3<U> const& v, V const& c4) : x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(c4)) {}

	/**
		Construct to X value, Y value, and ZW vector.
		@tparam U, V, H An arithmetic type.
		@param c1 X value.
		@param c2 Y value.
		@param v Z and W vector.
	*/
	template<typename U, typename V, typename H>
	inline explicit tvec4(U const& c1, V const& c2, tvec2<H> const& v) : x(T(c1)), y(T(c2)), z(T(v.x)), w(T(v.y)) {}
	/**
		Construct to XY vector, Z value, and W value.
		@tparam U, V, H An arithmetic type.
		@param v X and Y vector.
		@param c3 Z value.
		@param c4 W value.
	*/
	template<typename U, typename V, typename H>
	inline explicit tvec4(tvec3<U> const& v, V const& c3, H const& c4) : x(T(v.x)), y(T(v.y)), z(T(c3)), w(T(c4)) {}
/// @}

/** @name Properties */ /// @{
	/**
		Get vector length.
		@returns @c 4.
	*/
	inline AM_CONSTEXPR size_type length() const { return size_type(4); }
	/**
		Get value at index.
		@returns The value at @a i.
		@param i Index to retrieve.
	*/
	inline value_type& operator[](size_type const& i) {
		assert(length()>i);
		return (&x)[i];
	}
	/** @copydoc operator[](size_type const&) */
	inline value_type const& operator[](size_type const& i) const {
		assert(length()>i);
		return (&x)[i];
	}
/// @}

/** @name Comparison operators */ /// @{
	/**
		Equivalence operator.
		@returns @c true if the two vectors are equal, @c false if they are not.
		@param v Vector to compare with.
	*/
	inline bool operator==(type const& v) const {
		return
			this->x==v.x &&
			this->y==v.y &&
			this->z==v.z &&
			this->w==v.w;
	}
	/**
		Non-equivalence operator.
		@returns @c false if the two vectors are equal, @c true if they are not.
		@param v Vector to compare with.
	*/
	inline bool operator!=(type const& v) const {
		return
			this->x!=v.x &&
			this->y!=v.y &&
			this->z!=v.z &&
			this->w!=v.w;
	}
/// @}

/** @name Increment and decrement operators */ /// @{
	/**
		Prefix increment.
		@returns @c *this after operation.
	*/
	inline type& operator++() {
		++this->x;
		++this->y;
		++this->z;
		++this->w;
		return *this;
	}
	/**
		Prefix decrement.
		@returns @c *this after operation.
	*/
	inline type& operator--() {
		--this->x;
		--this->y;
		--this->z;
		--this->w;
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
	inline type& operator=(U const& s) {
		this->x=T(s);
		this->y=T(s);
		this->z=T(s);
		this->w=T(s);
		return *this;
	}
	/**
		Assign to vector.
		@returns @c *this after assignment.
		@tparam U An arithmetic type.
		@param v Vector to copy.
	*/
	template<typename U>
	inline type& operator=(tvec4<U> const& v) {
		this->x=T(v.x);
		this->y=T(v.y);
		this->z=T(v.z);
		this->w=T(v.w);
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
	inline type& operator+=(U const& s) {
		this->x+=T(s);
		this->y+=T(s);
		this->z+=T(s);
		this->w+=T(s);
		return *this;
	}
	/**
		Add vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to add.
	*/
	template<typename U>
	inline type& operator+=(tvec4<U> const& v) {
		this->x+=T(v.x);
		this->y+=T(v.y);
		this->z+=T(v.z);
		this->w+=T(v.w);
		return *this;
	}
	/**
		Subtract value from all components.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to subtract.
	*/
	template<typename U>
	inline type& operator-=(U const& s) {
		this->x-=T(s);
		this->y-=T(s);
		this->z-=T(s);
		this->w-=T(s);
		return *this;
	}
	/**
		Subtract vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to subtract.
	*/
	template<typename U>
	inline type& operator-=(tvec4<U> const& v) {
		this->x-=T(v.x);
		this->y-=T(v.y);
		this->z-=T(v.z);
		this->w-=T(v.z);
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
		this->y*=T(s);
		this->z*=T(s);
		this->w*=T(s);
		return *this;
	}
	/**
		Multiply by vector (direct component product).
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to multiply by.
	*/
	template<typename U>
	inline type& operator*=(tvec4<U> const& v) {
		this->x*=T(v.x);
		this->y*=T(v.y);
		this->z*=T(v.z);
		this->w*=T(v.w);
		return *this;
	}
	/**
		Divide all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to divide by.
	*/
	template<typename U>
	inline type& operator/=(U const& s) {
		this->x/=T(s);
		this->y/=T(s);
		this->z/=T(s);
		this->w/=T(s);
		return *this;
	}
	/**
		Divide by vector (direct component quotient).
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to divide by.
	*/
	template<typename U>
	inline type& operator/=(tvec4<U> const& v) {
		this->x/=T(v.x);
		this->y/=T(v.y);
		this->z/=T(v.z);
		this->w/=T(v.w);
		return *this;
	}
	/**
		Modulo all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Divisor.
	*/
	template<typename U>
	inline type& operator%=(U const& s) {
		this->x%=T(s);
		this->y%=T(s);
		this->z%=T(s);
		this->w%=T(s);
		return *this;
	}
	/**
		Modulo by vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Divisor vector.
	*/
	template<typename U>
	inline type& operator%=(tvec4<U> const& v) {
		this->x%=T(v.x);
		this->y%=T(v.y);
		this->z%=T(v.z);
		this->w%=T(v.w);
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
	inline type& operator&=(U const& s) {
		this->x&=T(s);
		this->y&=T(s);
		this->z&=T(s);
		this->w&=T(s);
		return *this;
	}
	/**
		Bitwise-AND vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to AND with.
	*/
	template<typename U>
	inline type& operator&=(tvec4<U> const& v) {
		this->x&=T(v.x);
		this->y&=T(v.y);
		this->z&=T(v.z);
		this->w&=T(v.w);
		return *this;
	}
	/**
		Bitwise-OR all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to OR with.
	*/
	template<typename U>
	inline type& operator|=(U const& s) {
		this->x|=T(s);
		this->y|=T(s);
		this->z|=T(s);
		this->w|=T(s);
		return *this;
	}
	/**
		Bitwise-OR vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to OR with.
	*/
	template<typename U>
	inline type& operator|=(tvec4<U> const& v) {
		this->x|=T(v.x);
		this->y|=T(v.y);
		this->z|=T(v.z);
		this->w|=T(v.w);
		return *this;
	}
	/**
		Bitwise-XOR all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Value to XOR with.
	*/
	template<typename U>
	inline type& operator^=(U const& s) {
		this->x^=T(s);
		this->y^=T(s);
		this->z^=T(s);
		this->w^=T(s);
		return *this;
	}
	/**
		Bitwise-XOR vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Vector to XOR with.
	*/
	template<typename U>
	inline type& operator^=(tvec4<U> const& v) {
		this->x^=T(v.x);
		this->y^=T(v.y);
		this->z^=T(v.z);
		this->w^=T(v.w);
		return *this;
	}
	/**
		Bitwise left-shift all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Left-shift value amount.
	*/
	template<typename U>
	inline type& operator<<=(U const& s) {
		this->x<<=T(s);
		this->y<<=T(s);
		this->z<<=T(s);
		this->w<<=T(s);
		return *this;
	}
	/**
		Bitwise left-shift vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Left-shift vector amount.
	*/
	template<typename U>
	inline type& operator<<=(tvec4<U> const& v) {
		this->x<<=T(v.x);
		this->y<<=T(v.y);
		this->z<<=T(v.z);
		this->w<<=T(v.w);
		return *this;
	}
	/**
		Bitwise right-shift all components by value.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param s Right-shift value amount.
	*/
	template<typename U>
	inline type& operator>>=(U const& s) {
		this->x>>=T(s);
		this->y>>=T(s);
		this->z>>=T(s);
		this->w>>=T(s);
		return *this;
	}
	/**
		Bitwise right-shift vector.
		@returns @c *this after operation.
		@tparam U An arithmetic type.
		@param v Right-shift vector amount.
	*/
	template<typename U>
	inline type& operator>>=(tvec4<U> const& v) {
		this->x>>=T(v.x);
		this->y>>=T(v.y);
		this->z>>=T(v.z);
		this->w>>=T(v.w);
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
	inline tvec4<T> operator++(tvec4<T> const& x, int) {
		return tvec4<T>{x.x+T(1), x.y+T(1), x.z+T(1), x.w+T(1)};
	}
	/**
		Vector postfix decrement.
		@returns New vector with @c x-1.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec4<T> operator--(tvec4<T> const& x, int) {
		return tvec4<T>{x.x-T(1), x.y-T(1), x.z-T(1), x.w-T(1)};
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
	inline tvec4<T> operator+(tvec4<T> const& x) {
		return tvec4<T>{x.x, x.y, x.z, x.w};
	}
	/**
		Vector unary minus.
		@returns New vector with @c -x.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec4<T> operator-(tvec4<T> const& x) {
		return tvec4<T>{	-x.x,
							-x.y,
							-x.z,
							-x.w};
	}
	/**
		Vector unary bitwise-NOT.
		@returns New vector with @c ~x.
		@tparam T An arithmetic type.
		@param x Vector.
	*/
	template<typename T>
	inline tvec4<T> operator~(tvec4<T> const& x) {
		return tvec4<T>{	~x.x,
							~x.y,
							~x.z,
							~x.w};
	}
/// @}

/** @name Arithmetic operators */ /// @{
	/**
		Vector right-hand value addition (all components).
		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator+(tvec4<T> const& x, T const& y) {
		return tvec4<T>{x.x + y,
						x.y + y,
						x.z + y,
						x.w + y};
	}
	/**
		Vector left-hand value addition (all components).
		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator+(T const& x, tvec4<T> const& y) {
		return tvec4<T>{  x + y.x,
						  x + y.y,
						  x + y.z,
						  x + y.w};
	}
	/**
		Vector addition.
		@returns New vector with @a x plus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator+(tvec4<T> const& x, tvec4<T> const& y) {
		return tvec4<T>{x.x + y.x,
						x.y + y.y,
						x.z + y.z,
						x.w + y.w};
	}
	/**
		Vector right-hand value subtraction (all components).
		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator-(tvec4<T> const& x, T const& y) {
		return tvec4<T>{x.x - y,
						x.y - y,
						x.z - y,
						x.w - y};
	}
	/**
		Vector left-hand value subtraction (all components).
		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator-(T const& x, tvec4<T> const& y) {
		return tvec4<T>{  x - y.x,
						  x - y.y,
						  x - y.z,
						  x - y.w};
	}
	/**
		Vector subtraction.
		@returns New vector with @a x minus @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator-(tvec4<T> const& x, tvec4<T> const& y) {
		return tvec4<T>{x.x - y.x,
						x.y - y.y,
						x.z - y.z,
						x.w - y.w};
	}
	/**
		Vector right-hand scalar multiplication (all components).
		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator*(tvec4<T> const& x, T const& y) {
		return tvec4<T>{x.x * y,
						x.y * y,
						x.z * y,
						x.w * y};
	}
	/**
		Vector left-hand scalar multiplication (all components).
		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator*(T const& x, tvec4<T> const& y) {
		return tvec4<T>{  x * y.x,
						  x * y.y,
						  x * y.z,
						  x * y.w};
	}
	/**
		Vector multiplication (direct component product).
		@returns New vector with @a x times @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator*(tvec4<T> const& x, tvec4<T> const& y) {
		return tvec4<T>{x.x * y.x,
						x.y * y.y,
						x.z * y.z,
						x.w * y.w};
	}
	/**
		Vector right-hand value division (all components).
		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator/(tvec4<T> const& x, T const& y) {
		return tvec4<T>{x.x / y,
						x.y / y,
						x.z / y,
						x.w / y};
	}
	/**
		Vector left-hand value division (all components).
		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator/(T const& x, tvec4<T> const& y) {
		return tvec4<T>{  x / y.x,
						  x / y.y,
						  x / y.z,
						  x / y.w};
	}
	/**
		Vector division (direct component quotient).
		@returns New vector with @a x divided by @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator/(tvec4<T> const& x, tvec4<T> const& y) {
		return tvec4<T>{x.x / y.x,
						x.y / y.y,
						x.z / y.z,
						x.w / y.w};
	}
	/**
		Vector right-hand value modulo (all components).
		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator%(tvec4<T> const& x, T const& y) {
		return tvec4<T>{x.x % y,
						x.y % y,
						x.z % y,
						x.w % y};
	}
	/**
		Vector left-hand value modulo (all components).
		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator%(T const& x, tvec4<T> const& y) {
		return tvec4<T>{  x % y.x,
						  x % y.y,
						  x % y.z,
						  x % y.w};
	}
	/**
		Vector modulo.
		@returns New vector with @a x modulo @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator%(tvec4<T> const& x, tvec4<T> const& y) {
		return tvec4<T>{x.x % y.x,
						x.y % y.y,
						x.z % y.z,
						x.w % y.w};
	}
/// @}

/** @name Bitwise operators */ /// @{
	/**
		Vector right-hand value bitwise-AND (all components).
		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator&(tvec4<T> const& x, T const& y) {
		return tvec4<T>{x.x & y,
						x.y & y,
						x.z & y,
						x.w & y};
	}
	/**
		Vector left-hand value bitwise-AND (all components).
		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator&(T const& x, tvec4<T> const& y) {
		return tvec4<T>{  x & y.x,
						  x & y.y,
						  x & y.z,
						  x & y.w};
	}
	/**
		Vector bitwise-AND.
		@returns New vector with @a x AND @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator&(tvec4<T> const& x, tvec4<T> const& y) {
		return tvec4<T>{x.x & y.x,
						x.y & y.y,
						x.z & y.z,
						x.w & y.w};
	}
	/**
		Vector right-hand value bitwise-OR (all components).
		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator|(tvec4<T> const& x, T const& y) {
		return tvec4<T>{x.x | y,
						x.y | y,
						x.z | y,
						x.w | y};
	}
	/**
		Vector left-hand value bitwise-OR (all components).
		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator|(T const& x, tvec4<T> const& y) {
		return tvec4<T>{  x | y.x,
						  x | y.y,
						  x | y.z,
						  x | y.w};
	}
	/**
		Vector bitwise-OR.
		@returns New vector with @a x OR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator|(tvec4<T> const& x, tvec4<T> const& y) {
		return tvec4<T>{x.x | y.x,
						x.y | y.y,
						x.z | y.z,
						x.w | y.w};
	}
	/**
		Vector right-hand value bitwise-XOR (all components).
		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator^(tvec4<T> const& x, T const& y) {
		return tvec4<T>{x.x ^ y,
						x.y ^ y,
						x.z ^ y,
						x.w ^ y};
	}
	/**
		Vector left-hand value bitwise-XOR (all components).
		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator^(T const& x, tvec4<T> const& y) {
		return tvec4<T>{  x ^ y.x,
						  x ^ y.y,
						  x ^ y.z,
						  x ^ y.w};
	}
	/**
		Vector bitwise-XOR.
		@returns New vector with @a x XOR @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator^(tvec4<T> const& x, tvec4<T> const& y) {
		return tvec4<T>{x.x ^ y.x,
						x.y ^ y.y,
						x.z ^ y.z,
						x.w ^ y.w};
	}
	/**
		Vector right-hand value bitwise left-shift (all components).
		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator<<(tvec4<T> const& x, T const& y) {
		return tvec4<T>{x.x << y,
						x.y << y,
						x.z << y,
						x.w << y};
	}
	/**
		Vector left-hand value bitwise left-shift (all components).
		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator<<(T const& x, tvec4<T> const& y) {
		return tvec4<T>{  x << y.x,
						  x << y.y,
						  x << y.z,
						  x << y.w};
	}
	/**
		Vector bitwise left-shift.
		@returns New vector with @a x left-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator<<(tvec4<T> const& x, tvec4<T> const& y) {
		return tvec4<T>{x.x << y.x,
						x.y << y.y,
						x.z << y.z,
						x.w << y.w};
	}
	/**
		Vector right-hand value bitwise right-shift (all components).
		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Value (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator>>(tvec4<T> const& x, T const& y) {
		return tvec4<T>{x.x >> y,
						x.y >> y,
						x.z >> y,
						x.w >> y};
	}
	/**
		Vector left-hand value bitwise right-shift (all components).
		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Value (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator>>(T const& x, tvec4<T> const& y) {
		return tvec4<T>{  x >> y.x,
						  x >> y.y,
						  x >> y.z,
						  x >> y.w};
	}
	/**
		Vector bitwise right-shift.
		@returns New vector with @a x right-shift @a y.
		@tparam T An arithmetic type.
		@param x Vector (left-hand).
		@param y Vector (right-hand).
	*/
	template<typename T>
	inline tvec4<T> operator>>(tvec4<T> const& x, tvec4<T> const& y) {
		return tvec4<T>{x.x >> y.x,
						x.y >> y.y,
						x.z >> y.z,
						x.w >> y.w};
	}
/// @}

/** @} */ // end of doc-group vec4
/** @} */ // end of doc-group vector

} // namespace detail
} // namespace am

#endif // AM_DETAIL_TVEC4_HPP_
