
#include <am/hash/fnv.hpp>
#include <am/hash/murmur.hpp>

#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>

// FIXME: seeds are currently narrowed to HL32

using func_vector_type
= std::vector<
	void
	(*)(
		std::string const&,
		am::hash::common_hash_type<am::hash::HL64> const
	)
>;

template<
	am::hash::HashLength L
>
void
output(
	am::hash::common_hash_type<L> const value
) {
	std::cout
		<< std::setw(static_cast<unsigned>(L) << 1)
		<< value
	;
}

template<
	am::hash::HashLength L
>
using hash_func_type =
am::hash::common_hash_type<L>
(&)(
	std::string const&
);

template<class Impl>
void
outputter(
	std::string const& str,
	am::hash::common_hash_type<am::hash::HL64> const
) {
	output<Impl::hash_length>(am::hash::calc_string<Impl>(str));
}

template<class Impl>
void
outputter_seeded(
	std::string const& str,
	am::hash::common_hash_type<am::hash::HL64> const seed
) {
	output<Impl::hash_length>(am::hash::calc_string<Impl>(
		str, static_cast<typename Impl::hash_type>(seed)
	));
}

using algorithm_map_type
= std::map<
	std::string,
	func_vector_type
>;

struct AlgorithmConfig final {
	std::string const& name;
	func_vector_type const& funcs;
	am::hash::common_hash_type<am::hash::HL64> const seed;

	AlgorithmConfig(
		algorithm_map_type::value_type const& pair,
		am::hash::common_hash_type<am::hash::HL64> const seed
	) 
		: name(pair.first)
		, funcs(pair.second)
		, seed(seed)
	{}
};

static algorithm_map_type const
s_algorithms{{
	{"fnv0", {
		&outputter<am::hash::fnv0<am::hash::HL32>>,
		&outputter<am::hash::fnv0<am::hash::HL64>>
	}},
	{"fnv1", {
		&outputter<am::hash::fnv1<am::hash::HL32>>,
		&outputter<am::hash::fnv1<am::hash::HL64>>
	}},
	{"fnv1a", {
		&outputter<am::hash::fnv1a<am::hash::HL32>>,
		&outputter<am::hash::fnv1a<am::hash::HL64>>
	}},

	{"murmur2", {
		&outputter_seeded<am::hash::murmur2<am::hash::HL32>>,
		&outputter_seeded<am::hash::murmur2<am::hash::HL64>>
	}},
	{"murmur64b", {
		&outputter_seeded<am::hash::murmur2_64b>
	}},
	{"murmur3", {
		&outputter_seeded<am::hash::murmur3>
	}}
}};

static std::vector<AlgorithmConfig>
s_selected{};

bool
select_algorithm(
	char const* const name,
	am::hash::common_hash_type<am::hash::HL64> const seed
) {
	auto const it = s_algorithms.find(name);
	if (s_algorithms.end() == it) {
		return false;
	} else {
		s_selected.emplace_back(*it, seed);
		return true;
	}
}

void
print_help() {
	std::cout
		<< "usage: util [seed] algo [[seed] algo [...]] - string [...]\n"
		<< "valid algorithms are:\n"
	;
	for (auto const& algo : s_algorithms) {
		std::cout << "  " << algo.first << '\n';
	}
}

signed
main(
	signed argc,
	char* argv[]
) {
	if (4 > argc) {
		std::cout << "invalid arguments\n";
		print_help();
		std::cout.flush();
		return -1;
	}

	am::hash::common_hash_type<am::hash::HL64> last_seed{0u};
	std::size_t dash_pos = 0u;

	for (
		std::size_t index = 1;
		index < static_cast<std::size_t>(argc);
		++index
	) {
		char const* const arg = argv[index];
		// strncmp stops at \0, and we want to know if the entire
		// string is equal, not just its first character, so 2 is the
		// maximum number of characters to compare
		if (0 == std::strncmp("-", arg, 2u)) {
			dash_pos = index;
			break;
		} else if (std::isdigit(arg[0])) {
			char* end = argv[index] + std::strlen(arg);
			last_seed = std::strtoll(arg, &end, 0);
		} else if (!select_algorithm(arg, last_seed)) {
			std::cout
				<< "invalid algorithm: "
				<< arg
				<< "\n\n"
			;
			print_help();
			std::cout.flush();
			return -2;
		}
	}

	if (0 == dash_pos || s_selected.empty()) {
		std::cout << "invalid arguments\n";
		print_help();
		std::cout.flush();
		return -1;
	}

	std::vector<std::string> strings{
		argv + dash_pos + 1,
		argv + argc
	};

	std::cout
		<< std::hex
		<< std::left
	;
	for (auto const& string : strings) {
		std::cout
			<< '\"' << string << "\"\n"
		;
		for (auto const& config : s_selected) {
			std::cout
				<< std::setfill(' ')
				<< "    ["
				<< std::setw(9u)
				<< config.name
				<< "] => "
				<< std::setfill('0')
			;
			for (
				auto func_it = config.funcs.cbegin();
				config.funcs.cend() != func_it;
				++func_it
			) {
				(*func_it)(string, config.seed);
				if (config.funcs.cend() != (func_it + 1)) {
					std::cout << ", ";
				}
			}
			std::cout << '\n';
		}
	}
	std::cout.flush();
	return 0;
}
