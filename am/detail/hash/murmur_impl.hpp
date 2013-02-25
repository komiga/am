/**
@file detail/hash/murmur_impl.hpp
@brief Murmur (implementation).

@author Tim Howard
@copyright 2012 Tim Howard under the MIT license; see @ref index or the accompanying LICENSE file for full text.
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

template<::am::hash::HashLength L>
using murmur_hash_type=::am::hash::common_hash_type<L>;

// NOTE: Specific-case unsafe ROTL; lacks mask guard on amt
#define AM_ROTL32__(x, amt)\
	((x<<amt) | (x>>(32-amt)))

template<::am::hash::HashLength L>
struct murmur2_impl;

// MurmurHash2
template<>
struct murmur2_impl<::am::hash::HashLength::HL32> {
	static constexpr uint32_t M=0x5bd1e995;
	static constexpr unsigned R=24;

	static uint32_t calc(
		uint8_t const* const data,
		std::size_t const size,
		uint32_t const seed
	) {
		// Rounded data size; essentially (size>>2)<<2
		std::size_t const aligned_size=size&~0x03;
		uint8_t const* const end=data+aligned_size;
		uint32_t const* block=reinterpret_cast<uint32_t const*>(data);
		uint32_t h=seed^size;
		uint32_t k;

		// Core
		for (; end!=reinterpret_cast<uint8_t const*>(block); ++block) {
			k=*block;
			k*=M;
			k^=k>>R;
			k*=M;

			h*=M;
			h^=k;
		}

		// Tail
		k=0;
		switch (size&3) {
			// Reverse core mixin
			case 3: h^=static_cast<uint32_t>(end[2])<<16;
			case 2: h^=static_cast<uint32_t>(end[1])<<8;
			case 1: h^=static_cast<uint32_t>(end[0]);
			h*=M;
		}

		// Finalization
		h^=h>>13;
		h*=M;
		h^=h>>15;
		return h;
	}
};

// MurmurHash64A
template<>
struct murmur2_impl<::am::hash::HashLength::HL64> {
	static constexpr uint64_t M=0xc6a4a7935bd1e995;
	static constexpr unsigned R=47;

	static uint64_t calc(
		uint8_t const* const data,
		std::size_t const size,
		uint64_t const seed
	) {
		// Rounded data size; essentially (size>>3)<<3
		std::size_t const aligned_size=size&~0x07;
		uint8_t const* const end=data+aligned_size;
		uint64_t const* block=reinterpret_cast<uint64_t const*>(data);
		uint64_t h=seed^(size*M);
		uint64_t k;

		// Core
		for (; end!=reinterpret_cast<uint8_t const*>(block); ++block) {
			k=*block;
			k*=M;
			k^=k>>R;
			k*=M;

			h^=k;
			h*=M;
		}

		// Tail
		k=0;
		switch (size&7) {
			// Reverse core mixin
			case 7: h^=static_cast<uint64_t>(end[6])<<48;
			case 6: h^=static_cast<uint64_t>(end[5])<<40;
			case 5: h^=static_cast<uint64_t>(end[4])<<32;
			case 4: h^=static_cast<uint64_t>(end[3])<<24;
			case 3: h^=static_cast<uint64_t>(end[2])<<16;
			case 2: h^=static_cast<uint64_t>(end[1])<<8;
			case 1: h^=static_cast<uint64_t>(end[0]);
			h*=M;
		}

		// Finalization
		h^=h>>R;
		h*=M;
		h^=h>>R;
		return h;
	}
};

// MurmurHash64B
#define AM_MURMUR2_64B_CMIX__(hx)\
	k*=M; k^=k>>R; k*=M;\
	hx*=M; hx^=k

struct murmur2_64b_impl {
	static constexpr uint32_t M=0x5bd1e995;
	static constexpr unsigned R=24;

	static uint64_t calc(
		uint8_t const* const data,
		std::size_t size,
		uint64_t const seed
	) {
		uint32_t const* block=reinterpret_cast<uint32_t const*>(data);
		// NOTE: Using specific variation for h2 from SMHasher;
		// originally h2=0 and seed was unsigned signed
		uint32_t h1=static_cast<uint32_t>(seed^size);
		uint32_t h2=static_cast<uint32_t>(seed>>32);
		uint32_t k;

		//std::printf("size=%-2lu h1=%08x h2=%08x  ", size, h1, h2);

		// Core
		while (8<=size) {
			k=*block++;
			AM_MURMUR2_64B_CMIX__(h1);
			k=*block++;
			AM_MURMUR2_64B_CMIX__(h2);
			size-=8;
		}

		//std::printf("C size=%-2lu h1=%08x h2=%08x  ", size, h1, h2);

		// Partial block (h1)
		if (4<=size) {
			k=*block++;
			AM_MURMUR2_64B_CMIX__(h1);
			size-=4;
		}

		//std::printf("P size=%-2lu h1=%08x h2=%08x\n", size, h1, h2);

		// Tail
		uint8_t const* tail=reinterpret_cast<uint8_t const*>(block);
		switch (size) {
			// Reverse core mixin
			case 3: h2^=tail[2]<<16;
			case 2: h2^=tail[1]<<8;
			case 1: h2^=tail[0];
			h2*=M;
		}

		// Finalization
		h1^=h2>>18; h1*=M;
		h2^=h1>>22; h2*=M;
		h1^=h2>>17; h1*=M;
		h2^=h1>>19; h2*=M;

		uint64_t h=h1;
		h=(h<<32)|h2;
		return h;
	}
};
#undef AM_MURMUR2_64B_CMIX__

template<::am::hash::HashLength L> struct murmur3_impl;

template<>
struct murmur3_impl<::am::hash::HashLength::HL32> {
	static constexpr uint32_t C1=0xcc9e2d51;
	static constexpr uint32_t C2=0x1b873593;
	static constexpr uint32_t C3=0xe6546b64;
	static constexpr uint32_t F1=0x85ebca6b;
	static constexpr uint32_t F2=0xc2b2ae35;

	static uint32_t calc(
		uint8_t const* const data,
		std::size_t const size,
		uint32_t const seed
	) {
		// Number of 32-bit blocks
		std::size_t const nblocks=size>>2;
		// Rounded data size; essentially (size>>2)<<2
		std::size_t const aligned_size=size&~0x03;
		uint32_t const* const blocks=
			reinterpret_cast<uint32_t const*>(data+aligned_size);
		uint32_t h=seed;
		uint32_t k;

		// Core
		for (signed i=-nblocks; i; ++i) {
			k=blocks[i];
			k*=C1;
			k=AM_ROTL32__(k, 15);
			k*=C2;

			h^=k;
			h=AM_ROTL32__(h, 13);
			h=h*5+C3;
		}

		// Tail
		uint8_t const* const tail=data+aligned_size;
		k=0;
		switch (size&3) {
			// Reverse tail & partial core mixin
			case 3: k^=tail[2]<<16;
			case 2: k^=tail[1]<<8;
			case 1: k^=tail[0];
			k*=C1;
			k=AM_ROTL32__(k, 15);
			k*=C2;
			h^=k;
		}

		// Finalization; avalanche
		h^=size;
		h^=h>>16;
		h*=F1;
		h^=h>>13;
		h*=F2;
		h^=h>>16;

		return h;
	}
};

#undef AM_ROTL32__

/** @endcond */ // INTERNAL

} // namespace hash
} // namespace detail
} // namespace am

#endif // AM_DETAIL_HASH_MURMUR_IMPL_HPP_
