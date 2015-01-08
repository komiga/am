/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief Interpolation functions.
*/

#pragma once

#include "../config.hpp"
#include "../detail/linear/type_traits.hpp"

namespace am {
namespace linear {

/**
	@addtogroup linear
	@{
*/
/**
	@defgroup interpolation Interpolation
	@{
*/

/**
	Linearly interpolate between two values with individual weights.

	@note @a w0 and @a w1 must be unit length and must add up to @c 1.
	If they do not follow this constraint, the result may be beyond
	@a v0 or @a v1.

	@tparam Cons Floating-point vector or scalar.
	@returns Interpolant.
	@param v0,w0 First value and weight.
	@param v1,w1 Second value and weight.
*/
template<
	class Cons
>
inline Cons
lerp_independent(
	Cons const& v0,
	detail::linear::value_type<Cons> const w0,
	Cons const& v1,
	detail::linear::value_type<Cons> const w1
) {
	return (v0 * w0) + (v1 * w1);
}

/**
	Linearly interpolate between two values.

	@note @a t must be unit length. If @a t is outside the range
	<code>[0, 1]</code>, the result will be beyond @a v0 or @a v1.

	@tparam Cons Floating-point vector or scalar.
	@returns Interpolant.
	@param v0,v1 Values.
	@param t Interpolation value.
*/
template<
	class Cons
>
inline Cons
lerp(
	Cons const& v0,
	Cons const& v1,
	detail::linear::value_type<Cons> const t
) {
	using V = detail::linear::value_type<Cons>;
	return linear::lerp_independent(
		v0, V{1} - t,
		v1, t
	);
}

/**
	Evaluate point in a cubic Bézier curve.

	@note @a t must be in the range <code>[0, 1]</code>.

	@tparam Cons Floating-point vector or scalar.
	@returns Interpolant.
	@param v0,v1,v2,v3 Values.
	@param t .
*/
template<
	class Cons
>
inline Cons
bezier_cubic(
	Cons const& v0,
	Cons const& v1,
	Cons const& v2,
	Cons const& v3,
	detail::linear::value_type<Cons> t
) {
	using V = detail::linear::value_type<Cons>;
	// Brute force:
	//return lerp(
	//	lerp(lerp(v0, v1, t), lerp(v1, v2, t), t),
	//	lerp(lerp(v1, v2, t), lerp(v2, v3, t), t),
	//	t
	//);

	// Reduction:
	// v0 * (1-t)³ +
	// v1 * (1-t)² * 3*t +
	// v2 * 3*(1-t) * t² +
	// v3 * t³
	V r = V{1} - t;
	Cons const i2 = v2 * V{3}*r * t*t;
	r *= r;
	return
		(v0 * r*r) +
		(v1 * r * V{3}*t) +
		i2 +
		(v3 * t*t*t)
	;
}

/** @} */ // end of doc-group interpolation
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace am
