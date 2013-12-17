
#ifndef AM_TEST_HASH_COMMON_HPP_
#define AM_TEST_HASH_COMMON_HPP_

#include "../general/common.hpp"

#include <cstring>

#define TEST_HASH_FUNC_CSTR(func, L, input, result) {\
	auto const x = am::hash::func<am::hash::HashLength::L>(input, std::strlen(input));\
	fassert(x == result);\
}

#define TEST_HASH_FUNC_STDSTR(func, L, input, result) {\
	auto const x = am::hash::func<am::hash::HashLength::L>(input);\
	fassert(x == result);\
}

template<typename T>
struct hash_data {
	typedef T value_type;

	value_type const value;
	char const* const input;
};

template<
	class H,
	typename DF,
	typename SF,
	typename CF
>
void TEST_HASH_SET(
	H const* const set,
	DF hash_func,
	SF str_hash_func,
	CF constexpr_hash_func
) {
	for (H const* it = set; nullptr != it->input; ++it) {
		std::size_t const size = std::strlen(it->input);
		fassert(it->value == hash_func(it->input, size));
		fassert(it->value == str_hash_func(std::string{it->input}));
		fassert(it->value == constexpr_hash_func(it->input, size));
	}
}

template<
	class H,
	typename S,
	typename DF,
	typename SF
>
void TEST_HASH_SEEDED_SET(
	H const* const set,
	S const seed,
	DF hash_func,
	SF str_hash_func
) {
	for (H const* it = set; nullptr != it->input; ++it) {
		std::size_t const size = std::strlen(it->input);
		fassert(it->value == hash_func(it->input, size, seed));
		fassert(it->value == str_hash_func(std::string{it->input}, seed));
	}
}

template<
	class H,
	typename S,
	typename DF,
	typename SF,
	typename CF
>
void TEST_HASH_SEEDED_SET_CE(
	H const* const set,
	S const seed,
	DF hash_func,
	SF str_hash_func,
	CF constexpr_hash_func
) {
	for (H const* it = set; nullptr != it->input; ++it) {
		std::size_t const size = std::strlen(it->input);
		fassert(it->value == hash_func(it->input, size, seed));
		fassert(it->value == str_hash_func(std::string{it->input}, seed));
		fassert(it->value == constexpr_hash_func(it->input, size, seed));
	}
}

#endif // AM_TEST_HASH_COMMON_HPP_
