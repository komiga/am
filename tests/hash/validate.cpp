
#include <am/hash/fnv.hpp>

#include "./common.hpp"
#include <string>

void test_fnv() {
	struct fnv_hash_data {
		hash_data<uint32_t> const data_32[5];
		hash_data<uint64_t> const data_64[5];
	};
	#define TEST_FNV_HASH_SET(data, func_pred)\
		TEST_HASH_SET(data.data_32, am::hash::func_pred<am::hash::HS32>, am::hash::func_pred ## _str<am::hash::HS32, std::string>);\
		TEST_HASH_SET(data.data_64, am::hash::func_pred<am::hash::HS64>, am::hash::func_pred ## _str<am::hash::HS64, std::string>);

	// FNV-0
	static fnv_hash_data const s_testdata_fnv0={{
		{0x00000000, ""},
		{0x00000041, "A"},
		{0xb74bb5ef, "foobar"},
		{0x32daf136, "nC63rvRg4lT_(&&bJr@95}Tu5KZ-j<oh"},
		{0, nullptr}},{
		{0x0000000000000000, ""},
		{0x0000000000000041, "A"},
		{0x0b91ae3f7ccdc5ef, "foobar"},
		{0xd449e0c999d3efd6, "nC63rvRg4lT_(&&bJr@95}Tu5KZ-j<oh"},
		{0, nullptr}
	}};
	TEST_FNV_HASH_SET(s_testdata_fnv0, fnv0);

	// FNV-1
	static fnv_hash_data const s_testdata_fnv1={{
		{0x811c9dc5, ""},
		{0x050c5d5e, "A"},
		{0x31f0b262, "foobar"},
		{0x96bc9a0b, "nC63rvRg4lT_(&&bJr@95}Tu5KZ-j<oh"},
		{0, nullptr}},{
		{0xcbf29ce484222325, ""},
		{0xaf63bd4c8601b79e, "A"},
		{0x340d8765a4dda9c2, "foobar"},
		{0xfffc4bc9a1cbc40b, "nC63rvRg4lT_(&&bJr@95}Tu5KZ-j<oh"},
		{0, nullptr}
	}};
	TEST_FNV_HASH_SET(s_testdata_fnv1, fnv1);

	// FNV-1a
	static fnv_hash_data const s_testdata_fnv1a={{
		{0x811c9dc5, ""},
		{0xc40bf6cc, "A"},
		{0xbf9cf968, "foobar"},
		{0x7f1dfc8f, "nC63rvRg4lT_(&&bJr@95}Tu5KZ-j<oh"},
		{0, nullptr}},{
		{0xcbf29ce484222325, ""},
		{0xaf63fc4c860222ec, "A"},
		{0x85944171f73967e8, "foobar"},
		{0x676c536a0ca191cf, "nC63rvRg4lT_(&&bJr@95}Tu5KZ-j<oh"},
		{0, nullptr}
	}};
	TEST_FNV_HASH_SET(s_testdata_fnv1a, fnv1a);
}

int main(int argc, char const* argv[]) {
	test_fnv();
	return 0;
}
