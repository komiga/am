
#include <am/config.hpp>

#include "../common/vector.hpp"

int main(int argc, char const* argv[]) {
	// Comparison operators
	AM_TEST_VEC_COP_ALL(am::vec ,  1.0f, ==,  1.0f);
	AM_TEST_VEC_COP_ALL(am::vec ,  1.0f, !=,  0.0f);
	AM_TEST_VEC_COP_ALL(am::ivec,  0x01, ==,  0x01);
	AM_TEST_VEC_COP_ALL(am::ivec,  0x01, !=,  0x00);

	// Assignment operators
	AM_TEST_VEC_AOP_ALL(am::vec ,  0.0f,  +,  1.0f, ( 1.0f));
	AM_TEST_VEC_AOP_ALL(am::vec ,  0.0f,  -, -1.0f, ( 1.0f));
	AM_TEST_VEC_AOP_ALL(am::vec ,  1.0f,  *,  2.0f, ( 2.0f));
	AM_TEST_VEC_AOP_ALL(am::vec ,  4.0f,  /,  2.0f, ( 2.0f));
	AM_TEST_VEC_AOP_ALL(am::ivec,  0x04,  %,  0x02, ( 0x00));
	AM_TEST_VEC_AOP_ALL(am::ivec,  0x03,  &,  0x02, ( 0x02));
	AM_TEST_VEC_AOP_ALL(am::ivec,  0x01,  |,  0x02, ( 0x03));
	AM_TEST_VEC_AOP_ALL(am::ivec,  0xFF,  ^,  0x0F, ( 0xF0));
	AM_TEST_VEC_AOP_ALL(am::ivec,  0x02, <<,  0x01, ( 0x04));
	AM_TEST_VEC_AOP_ALL(am::ivec,  0x02, >>,  0x02, ( 0x00));

	// Construct operators
	AM_TEST_VEC_XOP_ALL(am::vec ,  0.0f,  +,  1.0f, ( 1.0f), ( 1.0f));
	AM_TEST_VEC_XOP_ALL(am::vec ,  0.0f,  -, -1.0f, ( 1.0f), (-1.0f));
	AM_TEST_VEC_XOP_ALL(am::vec ,  1.0f,  *,  2.0f, ( 2.0f), ( 2.0f));
	AM_TEST_VEC_XOP_ALL(am::vec ,  4.0f,  /,  2.0f, ( 2.0f), ( 0.5f));
	AM_TEST_VEC_XOP_ALL(am::ivec,  0x04,  %,  0x02, ( 0x00), ( 0x02));
	AM_TEST_VEC_XOP_ALL(am::ivec,  0x03,  &,  0x02, ( 0x02), ( 0x02));
	AM_TEST_VEC_XOP_ALL(am::ivec,  0x01,  |,  0x02, ( 0x03), ( 0x03));
	AM_TEST_VEC_XOP_ALL(am::ivec,  0xFF,  ^,  0x0F, ( 0xF0), ( 0xF0));
	AM_TEST_VEC_XOP_ALL(am::ivec,  0x02, <<,  0x01, ( 0x04), ( 0x04));
	AM_TEST_VEC_XOP_ALL(am::ivec,  0x02, >>,  0x02, ( 0x00), ( 0x00));

	// Unary operators
	AM_TEST_VEC_UOP_ALL(am::vec ,  1.0f,  -, -1.0f);
	AM_TEST_VEC_UOP_ALL(am::vec ,  1.0f,  +,  1.0f);
	AM_TEST_VEC_UOP_ALL(am::ivec,  0x01,  -, -0x01);
	AM_TEST_VEC_UOP_ALL(am::ivec,  0x01,  +,  0x01);
	AM_TEST_VEC_UOP_ALL(am::ivec,  0x00,  ~,  0xFFFFFFFF);

	// Prefix and postfix increment and decrement
	AM_TEST_VEC_POP_ALL(am::vec ,  1.0f, --,  0.0f);
	AM_TEST_VEC_POP_ALL(am::vec ,  1.0f, ++,  2.0f);
	AM_TEST_VEC_POP_ALL(am::ivec,  0x01, --,  0x00);
	AM_TEST_VEC_POP_ALL(am::ivec,  0x01, ++,  0x02);
	AM_TEST_VEC_SOP_ALL(am::vec ,  1.0f, --,  0.0f);
	AM_TEST_VEC_SOP_ALL(am::vec ,  1.0f, ++,  2.0f);
	AM_TEST_VEC_SOP_ALL(am::ivec,  0x01, --,  0x00);
	AM_TEST_VEC_SOP_ALL(am::ivec,  0x01, ++,  0x02);
	return 0;
}
