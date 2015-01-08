/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief Common hashy things.
*/

#pragma once

#include "../config.hpp"

#include <type_traits>

namespace am {
namespace hash {

/**
	@addtogroup hash
	@{
*/

/**
	Hash lengths.
*/
enum HashLength : unsigned {
	/** 8-bit hash length. */
	HL8 = 1u,
	/** 32-bit hash length. */
	HL32 = 4u,
	/** 64-bit hash length. */
	HL64 = 8u,
	/** 128-bit hash length. */
	HL128 = 16u,
	/** 256-bit hash length. */
	HL256 = 32u,
	/** 512-bit hash length. */
	HL512 = 64u,
	/** 1024-bit hash length. */
	HL1024 = 128u
};

/** @cond INTERNAL */
template<
	HashLength L
>
struct common_hash_type_impl {
	struct type {
		union {
			uint8_t data[static_cast<unsigned>(L)];
			uint32_t chunks[static_cast<unsigned>(L) >> 2];
		};
	};
};

template<>
struct common_hash_type_impl<HashLength::HL8> {
	using type = uint8_t;
};
template<>
struct common_hash_type_impl<HashLength::HL32> {
	using type = uint32_t;
};
template<>
struct common_hash_type_impl<HashLength::HL64> {
	using type = uint64_t;
};

template<
	HashLength L
>
using common_hash_type = typename common_hash_type_impl<L>::type;
/** @endcond */ // INTERNAL

/**
	Whether a hash implementation is stateful.
*/
template<class /*Impl*/>
struct impl_is_stateful {
	static constexpr bool const value = false;
};

/**
	Whether a hash implementation is seeded.
*/
template<class /*Impl*/>
struct impl_is_seeded {
	static constexpr bool const value = false;
};

/**
	Calculate the hash of a sequence of bytes.

	@returns The hash of the given data.
	@tparam Impl Implementation interface.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
*/
template<
	class Impl,
	class = typename std::enable_if<!impl_is_seeded<Impl>::value>::type
>
inline typename Impl::hash_type
calc(
	char const* const data,
	unsigned const size
) {
	return Impl::calc(reinterpret_cast<uint8_t const*>(data), size);
}

/**
	Calculate the hash of a standard string.

	@returns The hash of @a str.
	@tparam Impl Implementation interface.
	@tparam StringT A standard string type (e.g., @c std::string);
	inferred from @a str.
	@param str A string.
*/
template<
	class Impl,
	class StringT,
	class = typename std::enable_if<!impl_is_seeded<Impl>::value>::type
>
inline typename Impl::hash_type
calc_string(
	StringT const& str
) {
	return Impl::calc(
		reinterpret_cast<uint8_t const*>(str.c_str()),
		str.size() << (sizeof(typename StringT::value_type) >> 1)
	);
}

/**
	Calculate the hash of a sequence of bytes (constexpr).

	@returns The hash of the given data.
	@tparam Impl Implementation interface.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
*/
template<
	class Impl,
	class = typename std::enable_if<!impl_is_seeded<Impl>::value>::type
>
inline constexpr typename Impl::hash_type
calc_ce(
	char const* const data,
	unsigned const size
) {
	return Impl::calc_ce_seq(data, size);
}

/**
	Calculate the hash of a sequence of bytes (seeded).

	@returns The hash of the given data.
	@tparam Impl Implementation interface.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
	@param seed Seed value.
*/
template<
	class Impl,
	class = typename std::enable_if<impl_is_seeded<Impl>::value>::type
>
inline typename Impl::hash_type
calc(
	char const* const data,
	unsigned const size,
	typename Impl::seed_type const seed
) {
	return Impl::calc(reinterpret_cast<uint8_t const*>(data), size, seed);
}

/**
	Calculate the hash of a standard string (seeded).

	@returns The hash of @a str.
	@tparam Impl Implementation interface.
	@tparam StringT A standard string type (e.g., @c std::string);
	inferred from @a str.
	@param str A string.
	@param seed Seed value.
*/
template<
	class Impl,
	class StringT,
	class = typename std::enable_if<impl_is_seeded<Impl>::value>::type
>
inline typename Impl::hash_type
calc_string(
	StringT const& str,
	typename Impl::seed_type const seed
) {
	return Impl::calc(
		reinterpret_cast<uint8_t const*>(str.c_str()),
		str.size() << (sizeof(typename StringT::value_type) >> 1),
		seed
	);
}

/**
	Calculate the hash of a sequence of bytes (seeded, constexpr).

	@returns The hash of the given data.
	@tparam Impl Implementation interface.
	@param data A sequence of bytes.
	@param size Size in bytes of @a data.
	@param seed Seed value.
*/
template<
	class Impl,
	class = typename std::enable_if<impl_is_seeded<Impl>::value>::type
>
inline constexpr typename Impl::hash_type
calc_ce(
	char const* const data,
	unsigned const size,
	typename Impl::seed_type const seed
) {
	return Impl::calc_ce_seq(data, size, seed);
}

/**
	Generic hash combiner.

	@tparam Impl Hash implementation.
*/
template<class Impl>
struct base_combiner {
	AM_STATIC_ASSERT(
		hash::impl_is_stateful<Impl>::value,
		"hash implementation must be stateful to use a combiner"
	);

	/** Hash implementation type. */
	using impl_type = Impl;
	/** Hash state type. */
	using state_type = typename impl_type::state_type;
	/** Hash value type. */
	using hash_type = typename impl_type::hash_type;

	/** Hash state. */
	state_type state;

	~base_combiner() = default;
	base_combiner() = default;
	base_combiner(base_combiner const&) = default;
	base_combiner(base_combiner&&) = default;

	base_combiner& operator=(base_combiner const&) = default;
	base_combiner& operator=(base_combiner&&) = default;

	/**
		Add a sequence of bytes.

		@param data A sequence of bytes.
		@param size Size in bytes of @a data.
	*/
	void
	add(
		char const* data,
		unsigned const size
	) noexcept {
		impl_type::state_add(
			state,
			reinterpret_cast<uint8_t const*>(data),
			size
		);
	}

	/**
		Add a standard string.

		@tparam StringT A standard string type (e.g., @c std::string);
		inferred from @a str.
		@param str A string.
	*/
	template<class StringT>
	void
	add_string(
		StringT const& str
	) noexcept {
		impl_type::state_add(
			state,
			reinterpret_cast<uint8_t const*>(str.c_str()),
			str.size() << (sizeof(typename StringT::value_type) >> 1)
		);
	}

	/**
		Get the current value.

		@note This does not mutate the combiner. Data can be added
		after fetching the value without reinitialization of the
		combiner.

		@returns The current value of the combiner.
	*/
	hash_type
	value() const noexcept {
		return impl_type::state_value(state);
	}

	/**
		Get the accumulated data size.

		@returns The accumulated data size.
	*/
	unsigned
	size() const noexcept {
		return impl_type::state_size(state);
	}
};

/**
	Generic hash combiner.

	@tparam Impl Hash implementation.
*/
template<
	class Impl,
	bool = impl_is_seeded<Impl>::value
>
struct generic_combiner;

/**
	Generic hash combiner (unseeded).

	@tparam Impl Hash implementation.
*/
template<class Impl>
struct generic_combiner<Impl, false>
	: base_combiner<Impl>
{
	using impl_type = Impl;

	/** Destructor. */
	~generic_combiner() = default;
	/** Copy constructor. */
	generic_combiner(generic_combiner const&) = default;
	/** Move assignment operator. */
	generic_combiner(generic_combiner&&) = default;

	/** Copy assignment operator. */
	generic_combiner& operator=(generic_combiner const&) = default;
	/** Move constructor. */
	generic_combiner& operator=(generic_combiner&&) = default;

	/**
		Default constructor.

		@note This initializes the combiner state.
	*/
	generic_combiner() {
		init();
	}

	/**
		Initialize the combiner state.

		@note If the combiner is already initialized, this will reset
		the state.
	*/
	void
	init() noexcept {
		impl_type::state_init(this->state);
	}
};

/**
	Generic hash combiner (seeded).

	@tparam Impl Hash implementation.
*/
template<class Impl>
struct generic_combiner<Impl, true>
	: base_combiner<Impl>
{
	using impl_type = Impl;

	/** Seed value type. */
	using seed_type = typename Impl::seed_type;

	generic_combiner() = delete;

	/** Destructor. */
	~generic_combiner() = default;
	/** Copy constructor. */
	generic_combiner(generic_combiner const&) = default;
	/** Move assignment operator. */
	generic_combiner(generic_combiner&&) = default;

	/** Copy assignment operator. */
	generic_combiner& operator=(generic_combiner const&) = default;
	/** Move constructor. */
	generic_combiner& operator=(generic_combiner&&) = default;

	/**
		Constructor.

		@note This initializes the combiner state.

		@param seed Seed value.
	*/
	generic_combiner(
		seed_type const seed
	) {
		init(seed);
	}

	/**
		Initialize the combiner state.

		@note If the combiner is already initialized, this will reset
		the state.

		@param seed Seed value.
	*/
	void
	init(
		seed_type const seed
	) noexcept {
		impl_type::state_init(this->state, seed);
	}
};

/** @} */ // end of doc-group hash

} // namespace hash
} // namespace am
