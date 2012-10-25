
#include <am/config.hpp>
#include <am/mat2x2.hpp>

#include "./common.hpp"
#include <cstdio>

int main(int argc, char const* argv[]) {
	am::mat2 const
		m22_i{
			 1.0f, 0.0f,
			 0.0f, 1.0f},
		m22_0{
			 0.0f, 0.0f,
			 0.0f, 0.0f},
		m22_x{
			 1.0f, 3.0f,
			 2.0f, 4.0f},
		m22_nx{
			-1.0f,-3.0f,
			-2.0f,-4.0f},
		m22_xa1{
			 2.0f, 4.0f,
			 3.0f, 5.0f},
		m22_xs1{
			 0.0f, 2.0f,
			 1.0f, 3.0f},
		m22_nxs1{
			 0.0f,-2.0f,
			-1.0f,-3.0f},
		m22_2x{
			 2.0f, 6.0f,
			 4.0f, 8.0f},
		m22_xd2{
			 0.5f, 1.5f,
			 1.0f, 2.0f},
		m22_2dx{
			 2.0f, 2.0f/3.0f,
			 1.0f, 0.5f},
		m22_xi{m22_x},
		m22_ix{m22_x},
		m22_xdi{m22_x},
		m22_idx{
			-2.0f, 1.5f,
			 1.0f,-0.5f}
	;
	TEST_MAT_OPS(
		am::mat2,
		m22_i,
		m22_x,
		// unary plus and minus
		 m22_x,
		 m22_nx,
		// Prefix and postfix increment and decrement
		 m22_xa1,
		 m22_xs1,
		// scalar add
		 1.0f,
		 m22_xa1,
		// scalar subtract
		 1.0f,
		 m22_xs1,  // rhs result
		 m22_nxs1, // lhs result
		// scalar multiply
		 2.0f,
		 m22_2x,
		// scalar divide
		 2.0f,
		 m22_xd2, // rhs result
		 m22_2dx, // lhs result

		// matrix add
		 m22_x,
		 m22_2x,
		// matrix subtract
		 m22_x,
		 m22_0, // rhs result
		 m22_0, // lhs result
		// matrix product
		 m22_i,
		 m22_xi, // rhs result
		 m22_ix, // lhs result
		// matrix quotient
		 m22_i,
		 m22_xdi, // rhs result
		 m22_idx  // lhs result
	); // mat2

	// TODO: More rigour
	#define PRINT_MAT2X2(m, name)\
		printf(name "\n\t: {%f, %f}\n", m[0][0], m[0][1]);\
		printf("\t  {%f, %f}\n", m[1][0], m[1][1]);

	auto t=am::transpose(m22_x);
	PRINT_MAT2X2(t, "transposed");
	printf("determinant: %f\n", am::determinant(m22_x));
	auto inverse=am::inverse(m22_x);
	PRINT_MAT2X2(inverse, "inverted");
	return 0;
}
