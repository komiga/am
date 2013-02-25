/**
@file detail/linear/type_traits.hpp
@brief Type traits.

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef AM_DETAIL_LINEAR_TYPE_TRAITS_HPP_
#define AM_DETAIL_LINEAR_TYPE_TRAITS_HPP_

#include "../../config.hpp"

#include <type_traits>

namespace am {
namespace detail {
namespace linear {

/**
	Whether the given type is a @ref vector "vector".
	@tparam T Any type.
*/
template<typename T>
struct is_vector : public std::false_type {};

/**
	Whether the given type is a @ref matrix "matrix".
	@tparam T Any type.
*/
template<typename T>
struct is_matrix : public std::false_type {};

/**
	Whether the given type is a square @ref matrix "matrix".
	@tparam T Any type.
*/
template<typename T>
struct is_square_matrix : public std::false_type {};

/**
	Whether the components in a linear construct are floating-point
	arithmetic types.
	@warning This assumes conType is a linear construct such as a
	@ref matrix "matrix" or a @ref vector "vector" (i.e., a type that has
	a @c value_type member typedef).
	@tparam conType A specialized linear construct.
*/
template<class conType>
struct is_construct_floating_point {
	/** Whether the linear construct is floating-point. */
	constexpr static bool value
		=std::is_floating_point<typename conType::value_type>::value;
};

/** @cond INTERNAL */
#define AM_DETAIL_TYPE_IS_VECTOR(TYPE)\
	template<typename T>\
	struct is_vector<TYPE<T> > : public std::true_type {};

#define AM_DETAIL_TYPE_IS_MATRIX(TYPE)\
	template<typename T>\
	struct is_matrix<TYPE<T> > : public std::true_type {};

#define AM_DETAIL_TYPE_IS_SQUARE_MATRIX(TYPE)\
	template<typename T>\
	struct is_square_matrix<TYPE<T> > : public std::true_type {};
/** @endcond */

} // namespace linear
} // namespace detail
} // namespace am

#endif // AM_DETAIL_LINEAR_TYPE_TRAITS_HPP_
