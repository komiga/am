
#include <am/config.hpp>

#include "./common.hpp"
#include <cstdio>

int main(int argc, char const* argv[]) {
	// Comparison operators
	TEST_VEC_COP_ALL(am::vec ,  1.0f, ==,  1.0f);
	TEST_VEC_COP_ALL(am::vec ,  1.0f, !=,  0.0f);
	TEST_VEC_COP_ALL(am::ivec,  0x01, ==,  0x01);
	TEST_VEC_COP_ALL(am::ivec,  0x01, !=,  0x00);

	// Assignment operators
	TEST_VEC_AOP_ALL(am::vec ,  0.0f,  +,  1.0f, ( 1.0f));
	TEST_VEC_AOP_ALL(am::vec ,  0.0f,  -, -1.0f, ( 1.0f));
	TEST_VEC_AOP_ALL(am::vec ,  1.0f,  *,  2.0f, ( 2.0f));
	TEST_VEC_AOP_ALL(am::vec ,  4.0f,  /,  2.0f, ( 2.0f));
	TEST_VEC_AOP_ALL(am::ivec,  0x04,  %,  0x02, ( 0x00));
	TEST_VEC_AOP_ALL(am::ivec,  0x03,  &,  0x02, ( 0x02));
	TEST_VEC_AOP_ALL(am::ivec,  0x01,  |,  0x02, ( 0x03));
	TEST_VEC_AOP_ALL(am::ivec,  0xFF,  ^,  0x0F, ( 0xF0));
	TEST_VEC_AOP_ALL(am::ivec,  0x02, <<,  0x01, ( 0x04));
	TEST_VEC_AOP_ALL(am::ivec,  0x02, >>,  0x02, ( 0x00));

	// Construct operators
	TEST_VEC_XOP_ALL(am::vec ,  0.0f,  +,  1.0f, ( 1.0f), ( 1.0f));
	TEST_VEC_XOP_ALL(am::vec ,  0.0f,  -, -1.0f, ( 1.0f), (-1.0f));
	TEST_VEC_XOP_ALL(am::vec ,  1.0f,  *,  2.0f, ( 2.0f), ( 2.0f));
	TEST_VEC_XOP_ALL(am::vec ,  4.0f,  /,  2.0f, ( 2.0f), ( 0.5f));
	TEST_VEC_XOP_ALL(am::ivec,  0x04,  %,  0x02, ( 0x00), ( 0x02));
	TEST_VEC_XOP_ALL(am::ivec,  0x03,  &,  0x02, ( 0x02), ( 0x02));
	TEST_VEC_XOP_ALL(am::ivec,  0x01,  |,  0x02, ( 0x03), ( 0x03));
	TEST_VEC_XOP_ALL(am::ivec,  0xFF,  ^,  0x0F, ( 0xF0), ( 0xF0));
	TEST_VEC_XOP_ALL(am::ivec,  0x02, <<,  0x01, ( 0x04), ( 0x04));
	TEST_VEC_XOP_ALL(am::ivec,  0x02, >>,  0x02, ( 0x00), ( 0x00));

	// Unary operators
	TEST_VEC_UOP_ALL(am::vec ,  1.0f,  +,  1.0f);
	TEST_VEC_UOP_ALL(am::vec ,  1.0f,  -, -1.0f);
	TEST_VEC_UOP_ALL(am::ivec,  0x01,  +,  0x01);
	TEST_VEC_UOP_ALL(am::ivec,  0x01,  -, -0x01);
	TEST_VEC_UOP_ALL(am::ivec,  0x00,  ~,  0xFFFFFFFF);

	// Prefix and postfix increment and decrement
	TEST_VEC_POP_ALL(am::vec ,  1.0f, ++,  2.0f);
	TEST_VEC_POP_ALL(am::vec ,  1.0f, --,  0.0f);
	TEST_VEC_POP_ALL(am::ivec,  0x01, ++,  0x02);
	TEST_VEC_POP_ALL(am::ivec,  0x01, --,  0x00);
	TEST_VEC_SOP_ALL(am::vec ,  1.0f, ++,  2.0f);
	TEST_VEC_SOP_ALL(am::vec ,  1.0f, --,  0.0f);
	TEST_VEC_SOP_ALL(am::ivec,  0x01, ++,  0x02);
	TEST_VEC_SOP_ALL(am::ivec,  0x01, --,  0x00);

	// TODO: More rigour
	#define PRINT_VEC3(v, name) printf(name ": {%f, %f, %f}\n", v.x, v.y, v.z);
	#define PRINT_FLOAT(f, name) printf(name ": %f\n", f);

	am::vec3 const
		a{1.0, 2.0, 3.0},
		b{3.0, 2.0, 1.0};
	am::vec3 r;
	am::vec3::value_type fr;
	fr=am::length(a); PRINT_FLOAT(fr, "length");
	fr=am::distance(a, b); PRINT_FLOAT(fr, "distance");
	fr=am::dot(a, b); PRINT_FLOAT(fr, "dot");
	r=am::cross(a, b); PRINT_VEC3(r, "cross");
	r=am::normalize(a); PRINT_VEC3(r, "normalized");
	return 0;
}
