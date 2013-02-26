/**
@file linear/vector_operations.hpp
@brief Vector operations.

@author Tim Howard
@copyright 2012-2013 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_LINEAR_VECTOR_OPERATIONS_HPP_
#define AM_LINEAR_VECTOR_OPERATIONS_HPP_

#include "../config.hpp"
#include "../detail/linear/type_traits.hpp"

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
#define AM_VEC_OP_REQUIRE_FLOATING_POINT(conType)\
	AM_STATIC_ASSERT(\
		detail::linear::is_vector<conType>::value,\
		"conType must be a vector");\
	AM_STATIC_ASSERT(\
		detail::linear::is_construct_floating_point<conType>::value,\
		"conType must be floating-point");
/** @endcond */

/**
	Calculate the length of a vector.

	@remark Defined for all floating-point vector types.
	@returns The length of @a v.
	@tparam conType Any floating-point vector type.
	@param v Vector.
*/
template<class conType>
inline typename conType::value_type length(conType const& v) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(conType);
	return conType::operations::length(v);
}

/**
	Calculate the distance between two vectors.

	@remark Defined for all floating-point vector types.
	@returns The distance between @a v and @a r.
	@tparam conType A floating-point vector type.
	@param v First vector.
	@param r Second vector.
*/
template<class conType>
inline typename conType::value_type distance(
	conType const& v,
	conType const& r
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(conType);
	return conType::operations::distance(v, r);
}

/**
	Calculate the dot product of two vectors.

	@remark Defined for all floating-point vector types.
	@returns The dot product of @a v and @a r.
	@tparam conType A floating-point vector type.
	@param v First vector.
	@param r Second vector.
*/
template<class conType>
inline typename conType::value_type dot(
	conType const& v,
	conType const& r
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(conType);
	return conType::operations::dot(v, r);
}

/**
	Calculate the cross product of two 3-dimensional vectors.

	@remark Defined for all 3-dimensional floating-point vector
	specializations (of any precision).
	@returns The cross product of @a v and @a r.
	@tparam T A floating-point arithmetic type.
	@param v First vector.
	@param r Second vector.
*/
template<typename T>
inline detail::linear::tvec3<T> cross(
	detail::linear::tvec3<T> const& v,
	detail::linear::tvec3<T> const& r
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(detail::linear::tvec3<T>);
	return detail::linear::tvec3<T>::operations::cross(v, r);
}

/**
	Normalize a vector.

	@remark Defined for all floating-point vector types.
	@returns @a v normalized.
	@tparam conType A floating-point vector type.
	@param v Vector to normalize.
*/
template<class conType>
inline conType normalize(conType const& v) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(conType);
	return conType::operations::normalize(v);
}

/**
	Orient a normal vector to point away from a surface.

	@remark Defined for all floating-point vector types.
	@returns Either @c n or @c -n.
	@tparam conType A floating-point vector type.
	@param n Normal vector to orient.
	@param i Incident vector.
	@param ng Geometric normal vector.
*/
template<class conType>
inline conType faceforward(
	conType const& n,
	conType const& i,
	conType const& ng
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(conType);
	return conType::operations::faceforward(n, i, ng);
}

/**
	Calculate the reflection direction vector for an incident vector.

	@note @a n should be a normalized vector.
	@remark Defined for all floating-point vector types.
	@returns The reflection direction vector.
	@tparam conType A floating-point vector type.
	@param i Incident vector.
	@param n Surface normal vector.
*/
template<class conType>
inline conType reflect(conType const& i, conType const& n) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(conType);
	return conType::operations::reflect(i, n);
}

/**
	Calculate the refraction direction vector for an incident vector.

	@note @a i and @a n should be normalized vectors.
	@remark Defined for all floating-point vector types.
	@returns The refraction direction vector.
	@tparam conType A floating-point vector type.
	@param i Incident vector.
	@param n Surface normal vector.
	@param eta Ratio of indices of refraction.
*/
template<class conType>
inline conType refract(
	conType const& i,
	conType const& n,
	typename conType::value_type const& eta
) {
	AM_VEC_OP_REQUIRE_FLOATING_POINT(conType);
	return conType::operations::refract(i, n, eta);
}

/** @cond INTERNAL */
#undef AM_VEC_OP_REQUIRE_FLOATING_POINT
/** @endcond */

/** @} */ // end of doc-group vector_ops
/** @} */ // end of doc-group vector
/** @} */ // end of doc-group linear

} // namespace linear
} // namespace am

#endif // AM_LINEAR_VECTOR_OPERATIONS_HPP_
