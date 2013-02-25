
#ifndef AM_TEST_HASH_COMMON_HPP_
#define AM_TEST_HASH_COMMON_HPP_

#include <cassert>
#include <cstring>

#define TEST_HASH_FUNC_CSTR(func, L, input, result) {\
		auto const x=am::hash::func<am::hash::HashLength::L>(input, std::strlen(input));\
		assert(x==result);\
	}

#define TEST_HASH_FUNC_STDSTR(func, L, input, result) {\
		auto const x=am::hash::func<am::hash::HashLength::L>(input);\
		assert(x==result);\
	}

template<typename T>
struct hash_data {
	typedef T value_type;

	value_type const value;
	char const* const input;
};

template<class H, typename DF, typename SF>
void TEST_HASH_SET(H const* const set, DF hash_func, SF str_hash_func) {
	for (H const* it=set; nullptr!=it->input; ++it) {
		assert(it->value==hash_func(it->input, std::strlen(it->input)));
		assert(it->value==str_hash_func(std::string{it->input}));
	}
}

template<class H, typename S, typename DF, typename SF>
void TEST_HASH_SEEDED_SET(H const* const set, S const seed, DF hash_func, SF str_hash_func) {
	for (H const* it=set; nullptr!=it->input; ++it) {
		assert(it->value==hash_func(it->input, std::strlen(it->input), seed));
		assert(it->value==str_hash_func(std::string{it->input}, seed));
	}
}

#endif // AM_TEST_HASH_COMMON_HPP_
