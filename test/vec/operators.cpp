
#include <am/config.hpp>
#include <am/linear/vector.hpp>
#include <am/linear/interpolation.hpp>

#include "./common.hpp"

#include <cstdio>

signed main() {
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
	#define PRINT_VEC3(v, name)\
		std::printf(name ": {%f, %f, %f}\n", v.x, v.y, v.z);
	#define PRINT_FLOAT(f, name)\
		std::printf(name ": %f\n", f);

	am::linear::vec3 const
		a{1.0f, 2.0f, 3.0f},
		b{3.0f, 2.0f, 1.0f},
		c{1.0f, 2.0f, 4.0f},
		zero{0.0f, 0.0f, 0.0f}
	;
	am::linear::vec3 r;
	am::linear::vec3::value_type fr;
	fr = am::linear::length(a); PRINT_FLOAT(fr, "length");
	fr = am::linear::distance(a, b); PRINT_FLOAT(fr, "distance");
	fr = am::linear::dot(a, b); PRINT_FLOAT(fr, "dot");
	r = am::linear::cross(a, b); PRINT_VEC3(r, "cross");
	r = am::linear::normalize(a); PRINT_VEC3(r, "normalized");
	r = am::linear::lerp(zero, c, 0.00f); PRINT_VEC3(r, "lerp 0.00f");
	r = am::linear::lerp(zero, c, 0.25f); PRINT_VEC3(r, "lerp 0.25f");
	r = am::linear::lerp(zero, c, 0.50f); PRINT_VEC3(r, "lerp 0.50f");
	r = am::linear::lerp(zero, c, 0.75f); PRINT_VEC3(r, "lerp 0.75f");
	r = am::linear::lerp(zero, c, 1.00f); PRINT_VEC3(r, "lerp 1.00f");

	r = am::linear::bezier_cubic(zero, zero, c, c, 0.00f); PRINT_VEC3(r, "bezier 0.00f");
	r = am::linear::bezier_cubic(zero, zero, c, c, 0.25f); PRINT_VEC3(r, "bezier 0.25f");
	r = am::linear::bezier_cubic(zero, zero, c, c, 0.50f); PRINT_VEC3(r, "bezier 0.50f");
	r = am::linear::bezier_cubic(zero, zero, c, c, 0.75f); PRINT_VEC3(r, "bezier 0.75f");
	r = am::linear::bezier_cubic(zero, zero, c, c, 1.00f); PRINT_VEC3(r, "bezier 1.00f");
	return 0;
}
