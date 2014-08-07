/**
@file linear/vector_operations.hpp
@brief Vector operations.

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../config.hpp"
#include "../detail/linear/type_traits.hpp"
#include "./vector_interface.hpp"
#include "./interpolation.hpp"

namespace am {
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
	@defgroup vector_ops Vector operations
	@{
*/

/** @cond INTERNAL */
#define AM_VEC_OP_REQUIRE_FLOATING_POINT(Cons)							\
	AM_STATIC_ASSERT(													\
		detail::linear::is_vector<Cons>::value,							\
		"Cons must be a vector"											\
	);																	\
	AM_STATIC_ASSERT(													\
		detail::linear::is_construct_floating_point<Cons>::value,		\
		"Cons must be floating-point"									\
	);
/** @endcond */

/**
	Calculate the length of a vector.

	@remarks Defined for all floating-point vector types.

	@tparam Cons Any floating-point vector type.
	@returns The length of @a v.
	@param v Vector.
*/
template<
	class Cons
>
inline detail::linear::value_type<Cons>
length(
	Cons const& v
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(Cons);
	return Cons::operations::length(v);
}

/**
	Calculate the distance between two vectors.

	@remarks Defined for all floating-point vector types.

	@tparam Cons A floating-point vector type.
	@returns The distance between @a v and @a r.
	@param v First vector.
	@param r Second vector.
*/
template<
	class Cons
>
inline detail::linear::value_type<Cons>
distance(
	Cons const& v,
	Cons const& r
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(Cons);
	return Cons::operations::distance(v, r);
}

/**
	Calculate the dot product of two vectors.

	@remarks Defined for all floating-point vector types.

	@tparam Cons A floating-point vector type.
	@returns The dot product of @a v and @a r.
	@param v First vector.
	@param r Second vector.
*/
template<
	class Cons
>
inline detail::linear::value_type<Cons>
dot(
	Cons const& v,
	Cons const& r
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(Cons);
	return Cons::operations::dot(v, r);
}

/**
	Calculate the cross product of two 3-dimensional vectors.

	@remarks Defined for all 3-dimensional floating-point vector
	specializations (of any precision).

	@tparam T A floating-point arithmetic type.
	@returns The cross product of @a v and @a r.
	@param v First vector.
	@param r Second vector.
*/
template<class T>
inline detail::linear::tvec3<T>
cross(
	detail::linear::tvec3<T> const& v,
	detail::linear::tvec3<T> const& r
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(detail::linear::tvec3<T>);
	return detail::linear::tvec3<T>::operations::cross(v, r);
}

/**
	Normalize a vector.

	@remarks Defined for all floating-point vector types.

	@tparam Cons A floating-point vector type.
	@returns @a v normalized.
	@param v Vector to normalize.
*/
template<
	class Cons
>
inline Cons
normalize(
	Cons const& v
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(Cons);
	return Cons::operations::normalize(v);
}

/**
	Orient a normal vector to point away from a surface.

	@remarks Defined for all floating-point vector types.

	@tparam Cons A floating-point vector type.
	@returns Either @c n or @c -n.
	@param n Normal vector to orient.
	@param i Incident vector.
	@param ng Geometric normal vector.
*/
template<
	class Cons
>
inline Cons
faceforward(
	Cons const& n,
	Cons const& i,
	Cons const& ng
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(Cons);
	return Cons::operations::faceforward(n, i, ng);
}

/**
	Calculate the reflection direction vector for an incident vector.

	@note @a n should be a normalized vector.

	@remarks Defined for all floating-point vector types.

	@tparam Cons A floating-point vector type.
	@returns The reflection direction vector.
	@param i Incident vector.
	@param n Surface normal vector.
*/
template<
	class Cons
>
inline Cons
reflect(
	Cons const& i,
	Cons const& n
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(Cons);
	return Cons::operations::reflect(i, n);
}

/**
	Calculate the refraction direction vector for an incident vector.

	@note @a i and @a n should be normalized vectors.

	@remarks Defined for all floating-point vector types.

	@tparam Cons A floating-point vector type.
	@returns The refraction direction vector.
	@param i Incident vector.
	@param n Surface normal vector.
	@param eta Ratio of indices of refraction.
*/
template<
	class Cons
>
inline Cons
refract(
	Cons const& i,
	Cons const& n,
	detail::linear::value_type<Cons> const& eta
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(Cons);
	return Cons::operations::refract(i, n, eta);
}

/**
	Linearly interpolate between two vectors.

	@tparam Cons A floating-point vector type.
	@returns Interpolant.
	@param x,y Values.
	@param a Interpolation weight.
*/
template<
	class Cons
>
inline Cons
mix(
	Cons const& x,
	Cons const& y,
	detail::linear::value_type<Cons> const& a
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(Cons);
	return linear::lerp(x, y, a);
}

/** @cond INTERNAL */
#undef AM_VEC_OP_REQUIRE_FLOATING_POINT
/** @endcond */

/** @} */ // end of doc-group vector_ops
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace am
