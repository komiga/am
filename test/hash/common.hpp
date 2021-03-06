
#pragma once

#include "../general/common.hpp"

#include <cstring>
#include <string>

#define TEST_HASH_FUNC_CSTR(func, impl, input, result) {\
	auto const x = am::hash::func<impl>(input, std::strlen(input));\
	fassert(x == result);\
}

#define TEST_HASH_FUNC_STDSTR(func, impl, input, result) {\
	auto const x = am::hash::func<impl>(input);\
	fassert(x == result);\
}

template<typename T>
struct hash_data {
	using value_type = T;

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
