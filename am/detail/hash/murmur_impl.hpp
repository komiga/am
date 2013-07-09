/**
@file detail/hash/murmur_impl.hpp
@brief Murmur (implementation).

@author Tim Howard
@copyright 2012-2013 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
Although the AM implementations are under the MIT license,
the Murmur algorithms themselves are in the public domain
and no copyright is claimed on them.
*/

#ifndef AM_DETAIL_HASH_MURMUR_IMPL_HPP_
#define AM_DETAIL_HASH_MURMUR_IMPL_HPP_

#include "../../config.hpp"

namespace am {
namespace detail {
namespace hash {

/** @cond INTERNAL */

template<
	::am::hash::HashLength L
>
using murmur_hash_type = ::am::hash::common_hash_type<L>;

template<
	::am::hash::HashLength L
>
struct murmur2_impl;

// MurmurHash2
template<>
struct murmur2_impl<::am::hash::HashLength::HL32> {
	static AM_CONSTEXPR uint32_t const M = 0x5bd1e995;
	static AM_CONSTEXPR unsigned const R = 24;

	static uint32_t
	calc(
		uint8_t const* const data,
		std::size_t const size,
		uint32_t const seed
	) {
		// Rounded data size; essentially (size>>2)<<2
		std::size_t const aligned_size = size & ~0x03;
		uint8_t const* const end = data+aligned_size;
		uint32_t const* block = reinterpret_cast<uint32_t const*>(data);
		uint32_t h = seed ^ size;
		uint32_t k;

		// Core
		for (; end != reinterpret_cast<uint8_t const*>(block); ++block) {
			k =* block;
			k *= M;
			k ^= k >> R;
			k *= M;

			h *= M;
			h ^= k;
		}

		// Tail
		k = 0;
		switch (size & 3) {
			// Reverse core mixin
			case 3: h ^= static_cast<uint32_t>(end[2]) << 16;
			case 2: h ^= static_cast<uint32_t>(end[1]) << 8;
			case 1: h ^= static_cast<uint32_t>(end[0]);
			h *= M;
		}

		// Finalization
		h ^= h >> 13;
		h *= M;
		h ^= h >> 15;
		return h;
	}
};

// MurmurHash64A
template<>
struct murmur2_impl<::am::hash::HashLength::HL64> {
	static AM_CONSTEXPR uint64_t const M = 0xc6a4a7935bd1e995;
	static AM_CONSTEXPR unsigned const R = 47;

	static uint64_t
	calc(
		uint8_t const* const data,
		std::size_t const size,
		uint64_t const seed
	) {
		// Rounded data size; essentially (size>>3)<<3
		std::size_t const aligned_size = size & ~0x07;
		uint8_t const* const end = data + aligned_size;
		uint64_t const* block = reinterpret_cast<uint64_t const*>(data);
		uint64_t h = seed ^ (size * M);
		uint64_t k;

		// Core
		for (; end!=reinterpret_cast<uint8_t const*>(block); ++block) {
			k = *block;
			k *= M;
			k ^= k >> R;
			k *= M;

			h ^= k;
			h *= M;
		}

		// Tail
		k = 0;
		switch (size & 7) {
			// Reverse core mixin
			case 7: h ^= static_cast<uint64_t>(end[6]) << 48;
			case 6: h ^= static_cast<uint64_t>(end[5]) << 40;
			case 5: h ^= static_cast<uint64_t>(end[4]) << 32;
			case 4: h ^= static_cast<uint64_t>(end[3]) << 24;
			case 3: h ^= static_cast<uint64_t>(end[2]) << 16;
			case 2: h ^= static_cast<uint64_t>(end[1]) << 8;
			case 1: h ^= static_cast<uint64_t>(end[0]);
			h *= M;
		}

		// Finalization
		h ^= h >> R;
		h *= M;
		h ^= h >> R;
		return h;
	}
};

// MurmurHash64B
#define AM_MURMUR2_64B_CMIX__(hx)\
	k *= M; k ^= k >> R; k *= M;\
	hx *= M; hx ^= k

struct murmur2_64b_impl {
	static AM_CONSTEXPR uint32_t const M = 0x5bd1e995;
	static AM_CONSTEXPR unsigned const R = 24u;

	static uint64_t
	calc(
		uint8_t const* const data,
		std::size_t size,
		uint64_t const seed
	) {
		uint32_t const* block = reinterpret_cast<uint32_t const*>(data);
		// NOTE: Using specific variation for h2 from SMHasher;
		// originally h2=0 and seed was unsigned signed
		uint32_t h1 = static_cast<uint32_t>(seed ^ size);
		uint32_t h2 = static_cast<uint32_t>(seed >> 32);
		uint32_t k;

		//std::printf("size = %-2lu h1 = %08x h2 = %08x  ", size, h1, h2);

		// Core
		while (8 <= size) {
			k = *block++;
			AM_MURMUR2_64B_CMIX__(h1);
			k = *block++;
			AM_MURMUR2_64B_CMIX__(h2);
			size -= 8;
		}

		//std::printf("C size = %-2lu h1 = %08x h2 = %08x  ", size, h1, h2);

		// Partial block (h1)
		if (4<=size) {
			k=*block++;
			AM_MURMUR2_64B_CMIX__(h1);
			size-=4;
		}

		//std::printf("P size = %-2lu h1 = %08x h2 = %08x\n", size, h1, h2);

		// Tail
		uint8_t const* tail = reinterpret_cast<uint8_t const*>(block);
		switch (size) {
			// Reverse core mixin
			case 3: h2 ^= tail[2]<<16;
			case 2: h2 ^= tail[1]<<8;
			case 1: h2 ^= tail[0];
			h2 *= M;
		}

		// Finalization
		h1 ^= h2 >> 18; h1 *= M;
		h2 ^= h1 >> 22; h2 *= M;
		h1 ^= h2 >> 17; h1 *= M;
		h2 ^= h1 >> 19; h2 *= M;

		uint64_t h = h1;
		h=(h << 32) | h2;
		return h;
	}
};
#undef AM_MURMUR2_64B_CMIX__

template<
	::am::hash::HashLength L
>
struct murmur3_impl;

template<>
struct murmur3_impl<::am::hash::HashLength::HL32> {
	static AM_CONSTEXPR uint32_t const C1 = 0xcc9e2d51u;
	static AM_CONSTEXPR uint32_t const C2 = 0x1b873593u;
	static AM_CONSTEXPR uint32_t const C3 = 0xe6546b64u;
	static AM_CONSTEXPR uint32_t const F1 = 0x85ebca6bu;
	static AM_CONSTEXPR uint32_t const F2 = 0xc2b2ae35u;

	// NOTE: Specific-case unsafe ROTL; lacks mask guard on amt
	inline static AM_CONSTEXPR uint32_t
	rotl32(
		uint32_t const x,
		uint32_t const amt
	) noexcept {
		return (x << amt) | (x >> (32 - amt));
	}

	static uint32_t
	calc(
		uint8_t const* const data,
		std::size_t const size,
		uint32_t const seed
	) noexcept {
		// Number of 32-bit blocks
		std::size_t const nblocks = size >> 2;
		// Rounded data size; essentially (size >> 2) << 2
		std::size_t const aligned_size = size & ~0x03;
		uint32_t const* const
			blocks = reinterpret_cast<uint32_t const*>(data + aligned_size);
		uint32_t h = seed;
		uint32_t k;

		// Core
		for (signed i = -nblocks; i; ++i) {
			k = blocks[i];
			k *= C1;
			k = rotl32(k, 15);
			k *= C2;

			h ^= k;
			h = rotl32(h, 13);
			h = h * 5 + C3;
		}

		// Tail
		uint8_t const* const tail = data + aligned_size;
		k = 0;
		switch (size & 0x03) {
			// Reverse tail & partial core mixin
			case 3: k ^= tail[2] << 16;
			case 2: k ^= tail[1] << 8;
			case 1: k ^= tail[0];
			k *= C1;
			k = rotl32(k, 15);
			k *= C2;
			h ^= k;
		}

		// Finalization; avalanche
		h ^= size;
		h ^= h >> 16;
		h *= F1;
		h ^= h >> 13;
		h *= F2;
		h ^= h >> 16;

		return h;
	}

// constexpr
struct ce_impl final {
	// Only handles every whole 4-byte block
	inline static AM_CONSTEXPR uint32_t
	body(
		char const* const iter,
		char const* const end,
		uint32_t const h
	) noexcept {
		return (end>iter)
			? body(
				iter + 4u, end,
				do_block(
					h,
					iter[0] | iter[1] << 8 | iter[2] << 16 | iter[3] << 24
				)
			)
			: h
		;
	}

	inline static AM_CONSTEXPR uint32_t
	do_block(
		uint32_t const h,
		uint32_t const k
	) noexcept {
		return rotl32(h ^ (rotl32(k * C1, 15) * C2), 13) * 5 + C3;
	}

	// Handle the last non-whole block (if there is one) and mix it in
	inline static AM_CONSTEXPR uint32_t
	tail(
		char const* const tail,
		uint32_t const size,
		uint32_t const h
	) noexcept {
		return (0 == (size & 0x03))
			? h
			: h ^ (rotl32(tail_cascade(tail, size & 0x03, 0) * C1, 15) * C2)
		;
	}

	inline static AM_CONSTEXPR uint32_t
	tail_cascade(
		char const* const tail,
		uint32_t const slots,
		uint32_t const k
	) noexcept {
		return (0 == slots)
			? k
			: tail_cascade(
				tail,
				slots - 1,
				k ^ tail[slots - 1] << ((slots - 1) << 3)
			)
		;
	}

	inline static AM_CONSTEXPR uint32_t
	avalanche(
		uint32_t h,
		uint32_t const size
	) noexcept {
		return a1(h ^ size);
	}

	inline static AM_CONSTEXPR uint32_t
	a1(uint32_t const h) noexcept { return a2(F1 * (h ^ h >> 16)); }
	inline static AM_CONSTEXPR uint32_t
	a2(uint32_t const h) noexcept { return a3(F2 * (h ^ h >> 13)); }
	inline static AM_CONSTEXPR uint32_t
	a3(uint32_t const h) noexcept { return h ^ h >> 16; }
}; // struct ce_impl

	inline static AM_CONSTEXPR uint32_t
	calc_c_seq(
		char const* const data,
		uint32_t const size,
		uint32_t const seed
	) noexcept {
		return
		ce_impl::avalanche(
			ce_impl::tail(
				data + (size & ~0x03), // aligned to 4-byte block
				size,
				ce_impl::body(
					data,
					data + (size & ~0x03),
					seed
				)
			),
			size
		);
	}
};

/** @endcond */ // INTERNAL

} // namespace hash
} // namespace detail
} // namespace am

#endif // AM_DETAIL_HASH_MURMUR_IMPL_HPP_
