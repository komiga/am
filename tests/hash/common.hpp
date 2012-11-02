
#ifndef AM_TESTS_HASH_COMMON_HPP_
#define AM_TESTS_HASH_COMMON_HPP_

#include <cassert>
#include <cstring>

#define TEST_HASH_FUNC_CSTR(func, S, input, result) {\
		auto const x=am::hash::func<am::hash::HashSize::S>(input, std::strlen(input));\
		assert(x==result);\
	}

#define TEST_HASH_FUNC_STDSTR(func, S, input, result) {\
		auto const x=am::hash::func<am::hash::HashSize::S>(input);\
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

#endif // AM_TESTS_HASH_COMMON_HPP_
