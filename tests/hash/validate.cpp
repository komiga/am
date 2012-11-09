
#include <am/hash/fnv.hpp>
#include <am/hash/murmur.hpp>

#include "./common.hpp"
#include <string>

#define HASH_STR_1 ""
#define HASH_STR_2 "A"
#define HASH_STR_3 "foobar"
#define HASH_STR_4 "nC63rvRg4lT_(&&bJr@95}Tu5KZ-j<oh"

void test_fnv() {
	struct fnv_hash_data {
		hash_data<uint32_t> const data_32[5];
		hash_data<uint64_t> const data_64[5];
	};
	#define TEST_FNV_HASH_SET(data_, func_pred)\
		TEST_HASH_SET(data_.data_32, am::hash::func_pred<am::hash::HL32>, am::hash::func_pred ## _str<am::hash::HL32, std::string>);\
		TEST_HASH_SET(data_.data_64, am::hash::func_pred<am::hash::HL64>, am::hash::func_pred ## _str<am::hash::HL64, std::string>);

	// FNV-0
	static fnv_hash_data const s_testdata_fnv0={{
		{0x00000000, HASH_STR_1},
		{0x00000041, HASH_STR_2},
		{0xb74bb5ef, HASH_STR_3},
		{0x32daf136, HASH_STR_4},
		{0, nullptr}},{
		{0x0000000000000000, HASH_STR_1},
		{0x0000000000000041, HASH_STR_2},
		{0x0b91ae3f7ccdc5ef, HASH_STR_3},
		{0xd449e0c999d3efd6, HASH_STR_4},
		{0, nullptr}
	}};
	TEST_FNV_HASH_SET(s_testdata_fnv0, fnv0);

	// FNV-1
	static fnv_hash_data const s_testdata_fnv1={{
		{0x811c9dc5, HASH_STR_1},
		{0x050c5d5e, HASH_STR_2},
		{0x31f0b262, HASH_STR_3},
		{0x96bc9a0b, HASH_STR_4},
		{0, nullptr}},{
		{0xcbf29ce484222325, HASH_STR_1},
		{0xaf63bd4c8601b79e, HASH_STR_2},
		{0x340d8765a4dda9c2, HASH_STR_3},
		{0xfffc4bc9a1cbc40b, HASH_STR_4},
		{0, nullptr}
	}};
	TEST_FNV_HASH_SET(s_testdata_fnv1, fnv1);

	// FNV-1a
	static fnv_hash_data const s_testdata_fnv1a={{
		{0x811c9dc5, HASH_STR_1},
		{0xc40bf6cc, HASH_STR_2},
		{0xbf9cf968, HASH_STR_3},
		{0x7f1dfc8f, HASH_STR_4},
		{0, nullptr}},{
		{0xcbf29ce484222325, HASH_STR_1},
		{0xaf63fc4c860222ec, HASH_STR_2},
		{0x85944171f73967e8, HASH_STR_3},
		{0x676c536a0ca191cf, HASH_STR_4},
		{0, nullptr}
	}};
	TEST_FNV_HASH_SET(s_testdata_fnv1a, fnv1a);
}

void test_murmur() {
	struct murmur2_hash_data {
		uint32_t const seed_32;
		hash_data<uint32_t> const data_32[5];
		uint64_t const seed_64;
		hash_data<uint64_t> const data_64[5];
	};
	#define TEST_MURMUR2_HASH_SET(data_)\
		TEST_HASH_SEEDED_SET(data_.data_32, data_.seed_32, am::hash::murmur2<am::hash::HL32>, am::hash::murmur2_str<am::hash::HL32, std::string>);\
		TEST_HASH_SEEDED_SET(data_.data_64, data_.seed_64, am::hash::murmur2<am::hash::HL64>, am::hash::murmur2_str<am::hash::HL64, std::string>);

	struct murmur64b_hash_data {
		uint64_t const seed;
		hash_data<uint64_t> const data[5];
	};
	#define TEST_MURMUR64B_HASH_SET(data_)\
		TEST_HASH_SEEDED_SET(data_.data, data_.seed, am::hash::murmur2_64b, am::hash::murmur2_64b_str<std::string>);

	struct murmur3_hash_data {
		uint32_t const seed;
		hash_data<uint32_t> const data_32[5];
	};
	#define TEST_MURMUR3_HASH_SET(data_)\
		TEST_HASH_SEEDED_SET(data_.data_32, data_.seed, am::hash::murmur3<am::hash::HL32>, am::hash::murmur3_str<am::hash::HL32, std::string>);

	// MurmurHash2 and MurmurHash64A
	static murmur2_hash_data const s_testdata_murmur2={
		0x00000000,{ // MurmurHash2
		{0x00000000, HASH_STR_1},
		{0x25f31569, HASH_STR_2},
		{0x6715a92e, HASH_STR_3},
		{0xb47f2335, HASH_STR_4},
		{0, nullptr}},
		0x0000000000000000,{ // MurmurHash64A
		{0x0000000000000000, HASH_STR_1},
		{0x37150ad24f8a8007, HASH_STR_2},
		{0xd49f461720d7a196, HASH_STR_3},
		{0x9d4e40fec6efa7f4, HASH_STR_4},
		{0, nullptr}
	}};
	TEST_MURMUR2_HASH_SET(s_testdata_murmur2);

	// MurmurHash64B
	static murmur64b_hash_data const s_testdata_murmur64b={
		0x0000000000000000,{
		{0x0000000000000000, HASH_STR_1},
		{0x1579d37158125e2a, HASH_STR_2},
		{0x3e2d2de4715d74db, HASH_STR_3},
		{0xd909cd8363949248, HASH_STR_4},
		{0, nullptr}
	}};
	TEST_MURMUR64B_HASH_SET(s_testdata_murmur64b);

	// MurmurHash3
	static murmur3_hash_data const s_testdata_murmur3={
		0x00000000,{
		{0x00000000, HASH_STR_1},
		{0x54dcf7ce, HASH_STR_2},
		{0xa4c4d4bd, HASH_STR_3},
		{0x8c94e46d, HASH_STR_4},
		{0, nullptr}
	}};
	TEST_MURMUR3_HASH_SET(s_testdata_murmur3);
}

#define TEST_HASH_COMMON_HASH_LENGTH(L){\
		am::hash::common_hash_type<am::hash::L> x;\
		assert(sizeof(x.data)==sizeof(x.chunks));\
	}

int main(int argc, char const* argv[]) {
	TEST_HASH_COMMON_HASH_LENGTH(HL128);
	TEST_HASH_COMMON_HASH_LENGTH(HL256);
	TEST_HASH_COMMON_HASH_LENGTH(HL512);
	TEST_HASH_COMMON_HASH_LENGTH(HL1024);
	test_fnv();
	test_murmur();
	return 0;
}
