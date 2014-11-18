
#include <am/hash/fnv.hpp>

#include "../general/common.hpp"

#include <initializer_list>
#include <string>
#include <iostream>
#include <iomanip>

template<class Impl>
inline void output(
	typename Impl::hash_type const value_combined,
	typename Impl::hash_type const value_linear
) {
	static constexpr auto const
	width = static_cast<unsigned>(Impl::hash_length) << 1;
	std::cout
		<< std::setw(width) << value_combined
		<< " | "
		<< std::setw(width) << value_linear
		<< '\n'
	;
}

template<class Impl>
inline bool test_combiner(
	std::initializer_list<std::string const> const& strings
) {
	am::hash::generic_combiner<Impl> combiner{};
	std::string joined;
	for (auto const& str : strings) {
		combiner.add_string(str);
		joined.append(str);
	}
	auto const value_combined = combiner.value();
	auto const value_linear = am::hash::calc_string<Impl>(joined);
	output<Impl>(value_combined, value_linear);
	return value_combined == value_linear;
}

/*template<class Impl>
inline bool test_combiner_seeded(
	std::initializer_list<std::string const> const& strings,
	typename Impl::seed_type const seed
) {
	am::hash::generic_combiner<Impl> combiner{seed};
	std::string joined;
	for (auto const& str : strings) {
		combiner.add_string(str);
		joined.append(str);
	}
	auto const value_combined = combiner.value();
	auto const value_linear = am::hash::calc_string<Impl>(joined, seed);
	output<Impl>(value_combined, value_linear);
	return value_combined == value_linear;
}*/

template<template<am::hash::HashLength> class ImplT>
inline bool test_combiner_t(
	std::initializer_list<std::string const> const& strings
) {
	return
		test_combiner<ImplT<am::hash::HL32>>(strings) &&
		test_combiner<ImplT<am::hash::HL64>>(strings)
	;
}

signed main() {
	std::cout
		<< "combined | linear/expected\n"
		<< std::left
		<< std::hex
		<< std::setfill('0')
	;

	std::initializer_list<std::initializer_list<std::string const>> const
	test_data{
		{},
		{""},
		{"", ""},
		{"a", ""},
		{"", "b", ""},
		{"", "", "c"},
		{"aba", "c", "aba"},
		{"aba", "c", "aba"},
	};
	for (auto const& strings : test_data) {
		std::cout
			<< "## testing: {"
		;
		for (unsigned i = 0; i < strings.size(); ++i) {
			std::cout << "\"" << *(strings.begin() + i) << "\"";
			if (i + 1 < strings.size()) {
				std::cout << ", ";
			}
		}
		std::cout << "}\n";

		fassert(test_combiner_t<am::hash::fnv0>(strings));
		fassert(test_combiner_t<am::hash::fnv1>(strings));
		fassert(test_combiner_t<am::hash::fnv1a>(strings));
		std::cout << '\n';
	}
	std::cout.flush();

	return 0;
}
