
#include <am/config.hpp>
#include <am/linear/vector.hpp>

#include "./common.hpp"
#include <cstdio>

int main(int argc, char const* argv[]) {
	// Comparison operators
	TEST_VEC_COP_ALL(vec ,  1.0f, ==,  1.0f);
	TEST_VEC_COP_ALL(vec ,  1.0f, !=,  0.0f);
	TEST_VEC_COP_ALL(ivec,  0x01, ==,  0x01);
	TEST_VEC_COP_ALL(ivec,  0x01, !=,  0x00);

	// Assignment operators
	TEST_VEC_AOP_ALL(vec ,  0.0f,  +,  1.0f, ( 1.0f));
	TEST_VEC_AOP_ALL(vec ,  0.0f,  -, -1.0f, ( 1.0f));
	TEST_VEC_AOP_ALL(vec ,  1.0f,  *,  2.0f, ( 2.0f));
	TEST_VEC_AOP_ALL(vec ,  4.0f,  /,  2.0f, ( 2.0f));
	TEST_VEC_AOP_ALL(ivec,  0x04,  %,  0x02, ( 0x00));
	TEST_VEC_AOP_ALL(ivec,  0x03,  &,  0x02, ( 0x02));
	TEST_VEC_AOP_ALL(ivec,  0x01,  |,  0x02, ( 0x03));
	TEST_VEC_AOP_ALL(ivec,  0xFF,  ^,  0x0F, ( 0xF0));
	TEST_VEC_AOP_ALL(ivec,  0x02, <<,  0x01, ( 0x04));
	TEST_VEC_AOP_ALL(ivec,  0x02, >>,  0x02, ( 0x00));

	// Construct operators
	TEST_VEC_XOP_ALL(vec ,  0.0f,  +,  1.0f, ( 1.0f), ( 1.0f));
	TEST_VEC_XOP_ALL(vec ,  0.0f,  -, -1.0f, ( 1.0f), (-1.0f));
	TEST_VEC_XOP_ALL(vec ,  1.0f,  *,  2.0f, ( 2.0f), ( 2.0f));
	TEST_VEC_XOP_ALL(vec ,  4.0f,  /,  2.0f, ( 2.0f), ( 0.5f));
	TEST_VEC_XOP_ALL(ivec,  0x04,  %,  0x02, ( 0x00), ( 0x02));
	TEST_VEC_XOP_ALL(ivec,  0x03,  &,  0x02, ( 0x02), ( 0x02));
	TEST_VEC_XOP_ALL(ivec,  0x01,  |,  0x02, ( 0x03), ( 0x03));
	TEST_VEC_XOP_ALL(ivec,  0xFF,  ^,  0x0F, ( 0xF0), ( 0xF0));
	TEST_VEC_XOP_ALL(ivec,  0x02, <<,  0x01, ( 0x04), ( 0x04));
	TEST_VEC_XOP_ALL(ivec,  0x02, >>,  0x02, ( 0x00), ( 0x00));

	// Unary operators
	TEST_VEC_UOP_ALL(vec ,  1.0f,  +,  1.0f);
	TEST_VEC_UOP_ALL(vec ,  1.0f,  -, -1.0f);
	TEST_VEC_UOP_ALL(ivec,  0x01,  +,  0x01);
	TEST_VEC_UOP_ALL(ivec,  0x01,  -, -0x01);
	TEST_VEC_UOP_ALL(ivec,  0x00,  ~,  0xFFFFFFFF);

	// Prefix and postfix increment and decrement
	TEST_VEC_POP_ALL(vec ,  1.0f, ++,  2.0f);
	TEST_VEC_POP_ALL(vec ,  1.0f, --,  0.0f);
	TEST_VEC_POP_ALL(ivec,  0x01, ++,  0x02);
	TEST_VEC_POP_ALL(ivec,  0x01, --,  0x00);
	TEST_VEC_SOP_ALL(vec ,  1.0f, ++,  2.0f);
	TEST_VEC_SOP_ALL(vec ,  1.0f, --,  0.0f);
	TEST_VEC_SOP_ALL(ivec,  0x01, ++,  0x02);
	TEST_VEC_SOP_ALL(ivec,  0x01, --,  0x00);

	// TODO: More rigour
	#define PRINT_VEC3(v, name) printf(name ": {%f, %f, %f}\n", v.x, v.y, v.z);
	#define PRINT_FLOAT(f, name) printf(name ": %f\n", f);

	am::linear::vec3 const
		a{1.0, 2.0, 3.0},
		b{3.0, 2.0, 1.0};
	am::linear::vec3 r;
	am::linear::vec3::value_type fr;
	fr=am::linear::length(a); PRINT_FLOAT(fr, "length");
	fr=am::linear::distance(a, b); PRINT_FLOAT(fr, "distance");
	fr=am::linear::dot(a, b); PRINT_FLOAT(fr, "dot");
	r=am::linear::cross(a, b); PRINT_VEC3(r, "cross");
	r=am::linear::normalize(a); PRINT_VEC3(r, "normalized");
	return 0;
}
