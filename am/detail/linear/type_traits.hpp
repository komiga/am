/**
@file
@brief Type traits.

@author Timothy Howard
@copyright 2012-2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include "../../config.hpp"

#include <type_traits>

namespace am {
namespace detail {
namespace linear {

/**
	Whether the given type is a @ref vector "vector".

	@tparam T Any type.
*/
template<
	class T
>
struct is_vector
	: public std::false_type
{};

/**
	Whether the given type is a @ref matrix "matrix".

	@tparam T Any type.
*/
template<
	class T
>
struct is_matrix
	: public std::false_type
{};

/**
	Whether the given type is a square @ref matrix "matrix".

	@tparam T Any type.
*/
template<
	class T
>
struct is_square_matrix
	: public std::false_type
{};

/**
	Whether the components in a linear construct are floating-point
	arithmetic types.

	@warning This assumes Cons is a linear construct such as a
	@ref matrix "matrix" or a @ref vector "vector" (i.e., a type that
	has a @c value_type member type alias).

	@tparam Cons A specialized linear construct.
*/
template<
	class Cons
>
struct is_construct_floating_point {
	/** Whether the linear construct is floating-point. */
	static constexpr bool
	value = std::is_floating_point<
		typename Cons::value_type
	>::value;
};

namespace {

template<
	class Cons,
	class = void
>
struct value_type_impl;

template<class Cons>
struct value_type_impl<
	Cons,
	typename std::enable_if<
		linear::is_vector<Cons>::value ||
		linear::is_matrix<Cons>::value
	>::type
> {
	using type = typename Cons::value_type;
};

template<class Cons>
struct value_type_impl<
	Cons,
	typename std::enable_if<std::is_arithmetic<Cons>::value>::type
> {
	using type = Cons;
};

} // anonymous namespace

/**
	Value type of a linear construct or scalar.

	@tparam Cons An arithmetic type or specialized linear construct.
*/
template<
	class Cons
>
using value_type = typename value_type_impl<Cons>::type;

/** @cond INTERNAL */
#define AM_DETAIL_TYPE_IS_VECTOR(TYPE)								\
	template<class T>												\
	struct is_vector<TYPE<T> > : public std::true_type				\
	{} /**/

#define AM_DETAIL_TYPE_IS_MATRIX(TYPE)								\
	template<class T>												\
	struct is_matrix<TYPE<T> > : public std::true_type				\
	{} /**/

#define AM_DETAIL_TYPE_IS_SQUARE_MATRIX(TYPE)						\
	template<class T>												\
	struct is_square_matrix<TYPE<T> > : public std::true_type		\
	{} /**/
/** @endcond */

} // namespace linear
} // namespace detail
} // namespace am
