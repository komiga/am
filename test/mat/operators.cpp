
#include <am/config.hpp>
#include <am/linear/matrix.hpp>

#include "./common.hpp"

void test_mat2x2() {
	// Operators
	am::linear::mat2x2 const
		mat_i{
			 1.0f, 0.0f,
			 0.0f, 1.0f},
		mat_0{
			 0.0f, 0.0f,
			 0.0f, 0.0f},
		mat_x{
			 1.0f, 3.0f,
			 2.0f, 4.0f},
		mat_nx{
			-1.0f,-3.0f,
			-2.0f,-4.0f},
		mat_xa1{
			 2.0f, 4.0f,
			 3.0f, 5.0f},
		mat_xs1{
			 0.0f, 2.0f,
			 1.0f, 3.0f},
		mat_1sx{
			 0.0f,-2.0f,
			-1.0f,-3.0f},
		mat_2x{
			 2.0f, 6.0f,
			 4.0f, 8.0f},
		mat_xd2{
			 0.5f, 1.5f,
			 1.0f, 2.0f},
		mat_2dx{
			 2.0f/1.0f, 2.0f/3.0f,
			 2.0f/2.0f, 2.0f/4.0f},
		mat_idx{
			-2.0f, 1.5f,
			 1.0f,-0.5f}
	;
	TEST_MAT_OPS_SQUARE(
		am::linear::mat2x2,
		mat_i,
		mat_x,
		// unary plus and minus
		 mat_x,
		 mat_nx,
		// Prefix and postfix increment and decrement
		 mat_xa1,
		 mat_xs1,
		// scalar add
		 1.0f,
		 mat_xa1,
		// scalar subtract
		 1.0f,
		 mat_xs1, // rhs result
		 mat_1sx, // lhs result
		// scalar multiply
		 2.0f,
		 mat_2x,
		// scalar divide
		 2.0f,
		 mat_xd2, // rhs result
		 mat_2dx, // lhs result

		// matrix add
		 mat_x,
		 mat_2x,
		// matrix subtract
		 mat_x,
		 mat_0, // rhs result
		 mat_0, // lhs result
		// identity-matrix divide
		 mat_x,  // lhs operand
		 mat_idx // lhs result
	);

	// Multiplications
	// 2x2 * 2x2 -> 2x2
	am::linear::mat2x2 const
		mat_y22{mat_i}
	;
	am::linear::mat2x2 const
		mat_xy22{mat_x}
	;
	// 2x2 * 3x2 -> 3x2
	am::linear::mat3x2 const
		mat_y32{
			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f}
	;
	am::linear::mat3x2 const
		mat_xy32{
			1.0f, 3.0f,
			2.0f, 4.0f,
			0.0f, 0.0f}
	;
	// 2x2 * 4x2 -> 4x2
	am::linear::mat4x2 const
		mat_y42{
			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			0.0f, 0.0f}
	;
	am::linear::mat4x2 const
		mat_xy42{
			1.0f, 3.0f,
			2.0f, 4.0f,
			0.0f, 0.0f,
			0.0f, 0.0f}
	;
	TEST_MAT_XOP_RHS(mat_x, *, mat_y22, mat_xy22);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y32, mat_xy32);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y42, mat_xy42);

	// Properties
	am::linear::mat2x2 const
		mat_x_tr{
			1.0f, 2.0f,
			3.0f, 4.0f}
	;
	TEST_MAT_PROPERTIES_SQUARE(
		mat_x,
		mat_x_tr,
		-2.0f,
		mat_x, -2.0f, mat_idx
	);
}

void test_mat2x3() {
	// Operators
	am::linear::mat2x3 const
		mat_i{
			  1.0f,  0.0f,  0.0f,
			  0.0f,  1.0f,  0.0f},
		mat_0{
			  0.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  0.0f},
		mat_x{
			  1.0f,  3.0f,  5.0f,
			  2.0f,  4.0f,  6.0f},
		mat_nx{
			 -1.0f, -3.0f, -5.0f,
			 -2.0f, -4.0f, -6.0f},
		mat_xa1{
			  2.0f,  4.0f,  6.0f,
			  3.0f,  5.0f,  7.0f},
		mat_xs1{
			  0.0f,  2.0f,  4.0f,
			  1.0f,  3.0f,  5.0f},
		mat_1sx{
			  0.0f, -2.0f, -4.0f,
			 -1.0f, -3.0f, -5.0f},
		mat_2x{
			  2.0f,  6.0f, 10.0f,
			  4.0f,  8.0f, 12.0f},
		mat_xd2{
			  0.5f,  1.5f,  2.5f,
			  1.0f,  2.0f,  3.0f},
		mat_2dx{
			  2.0f/1.0f, 2.0f/3.0f, 2.0f/5.0f,
			  2.0f/2.0f, 2.0f/4.0f, 2.0f/6.0f}
	;
	TEST_MAT_OPS(
		am::linear::mat2x3,
		mat_i,
		mat_x,
		// unary plus and minus
		 mat_x,
		 mat_nx,
		// Prefix and postfix increment and decrement
		 mat_xa1,
		 mat_xs1,
		// scalar add
		 1.0f,
		 mat_xa1,
		// scalar subtract
		 1.0f,
		 mat_xs1, // rhs result
		 mat_1sx, // lhs result
		// scalar multiply
		 2.0f,
		 mat_2x,
		// scalar divide
		 2.0f,
		 mat_xd2, // rhs result
		 mat_2dx, // lhs result
		// matrix add
		 mat_x,
		 mat_2x,
		// matrix subtract
		 mat_x,
		 mat_0, // rhs result
		 mat_0  // lhs result
	);

	// Multiplications
	// 2x3 * 2x2 -> 2x3
	am::linear::mat2x2 const
		mat_y22{
			1.0f, 0.0f,
			0.0f, 1.0f}
	;
	am::linear::mat2x3 const
		mat_xy22{mat_x}
	;
	// 2x3 * 3x2 -> 3x3
	am::linear::mat3x2 const
		mat_y32{
			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f}
	;
	am::linear::mat3x3 const
		mat_xy32{
			1.0f, 3.0f, 5.0f,
			2.0f, 4.0f, 6.0f,
			0.0f, 0.0f, 0.0f}
	;
	// 2x3 * 4x2 -> 4x3
	am::linear::mat4x2 const
		mat_y42{
			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			0.0f, 0.0f}
	;
	am::linear::mat4x3 const
		mat_xy42{
			1.0f, 3.0f, 5.0f,
			2.0f, 4.0f, 6.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f}
	;
	TEST_MAT_XOP_RHS(mat_x, *, mat_y22, mat_xy22);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y32, mat_xy32);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y42, mat_xy42);

	// Properties
	am::linear::mat3x2 const
		mat_x_tr{
			1.0f, 2.0f,
			3.0f, 4.0f,
			5.0f, 6.0f}
	;
	TEST_MAT_PROPERTIES(
		mat_x,
		mat_x_tr
	);
}

void test_mat2x4() {
	// Operators
	am::linear::mat2x4 const
		mat_i{
			  1.0f,  0.0f,  0.0f,  0.0f,
			  0.0f,  1.0f,  0.0f,  0.0f},
		mat_0{
			  0.0f,  0.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  0.0f,  0.0f},
		mat_x{
			  1.0f,  3.0f,  5.0f,  7.0f,
			  2.0f,  4.0f,  6.0f,  8.0f},
		mat_nx{
			 -1.0f, -3.0f, -5.0f, -7.0f,
			 -2.0f, -4.0f, -6.0f, -8.0f},
		mat_xa1{
			  2.0f,  4.0f,  6.0f,  8.0f,
			  3.0f,  5.0f,  7.0f,  9.0f},
		mat_xs1{
			  0.0f,  2.0f,  4.0f,  6.0f,
			  1.0f,  3.0f,  5.0f,  7.0f},
		mat_1sx{
			  0.0f, -2.0f, -4.0f, -6.0f,
			 -1.0f, -3.0f, -5.0f, -7.0f},
		mat_2x{
			  2.0f,  6.0f, 10.0f, 14.0f,
			  4.0f,  8.0f, 12.0f, 16.0f},
		mat_xd2{
			  0.5f,  1.5f,  2.5f,  3.5f,
			  1.0f,  2.0f,  3.0f,  4.0f},
		mat_2dx{
			  2.0f/1.0f, 2.0f/3.0f, 2.0f/5.0f, 2.0f/7.0f,
			  2.0f/2.0f, 2.0f/4.0f, 2.0f/6.0f, 2.0f/8.0f}
	;
	TEST_MAT_OPS(
		am::linear::mat2x4,
		mat_i,
		mat_x,
		// unary plus and minus
		 mat_x,
		 mat_nx,
		// Prefix and postfix increment and decrement
		 mat_xa1,
		 mat_xs1,
		// scalar add
		 1.0f,
		 mat_xa1,
		// scalar subtract
		 1.0f,
		 mat_xs1, // rhs result
		 mat_1sx, // lhs result
		// scalar multiply
		 2.0f,
		 mat_2x,
		// scalar divide
		 2.0f,
		 mat_xd2, // rhs result
		 mat_2dx, // lhs result
		// matrix add
		 mat_x,
		 mat_2x,
		// matrix subtract
		 mat_x,
		 mat_0, // rhs result
		 mat_0  // lhs result
	);

	// Multiplications
	// 2x4 * 2x2 -> 2x4
	am::linear::mat2x2 const
		mat_y22{
			1.0f, 0.0f,
			0.0f, 1.0f}
	;
	am::linear::mat2x4 const
		mat_xy22{mat_x}
	;
	// 2x4 * 3x2 -> 3x4
	am::linear::mat3x2 const
		mat_y32{
			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f}
	;
	am::linear::mat3x4 const
		mat_xy32{
			1.0f, 3.0f, 5.0f, 7.0f,
			2.0f, 4.0f, 6.0f, 8.0f,
			0.0f, 0.0f, 0.0f, 0.0f}
	;
	// 2x4 * 4x2 -> 4x4
	am::linear::mat4x2 const
		mat_y42{
			1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			0.0f, 0.0f}
	;
	am::linear::mat4x4 const
		mat_xy42{
			1.0f, 3.0f, 5.0f, 7.0f,
			2.0f, 4.0f, 6.0f, 8.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f}
	;
	TEST_MAT_XOP_RHS(mat_x, *, mat_y22, mat_xy22);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y32, mat_xy32);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y42, mat_xy42);

	// Properties
	am::linear::mat4x2 const
		mat_x_tr{
			1.0f, 2.0f,
			3.0f, 4.0f,
			5.0f, 6.0f,
			7.0f, 8.0f}
	;
	TEST_MAT_PROPERTIES(
		mat_x,
		mat_x_tr
	);
}

void test_mat3x2() {
	// Operators
	am::linear::mat3x2 const
		mat_i{
			  1.0f,  0.0f,
			  0.0f,  1.0f,
			  0.0f,  0.0f},
		mat_0{
			  0.0f,  0.0f,
			  0.0f,  0.0f,
			  0.0f,  0.0f},
		mat_x{
			  1.0f,  4.0f,
			  2.0f,  5.0f,
			  3.0f,  6.0f},
		mat_nx{
			 -1.0f, -4.0f,
			 -2.0f, -5.0f,
			 -3.0f, -6.0f},
		mat_xa1{
			  2.0f,  5.0f,
			  3.0f,  6.0f,
			  4.0f,  7.0f},
		mat_xs1{
			  0.0f,  3.0f,
			  1.0f,  4.0f,
			  2.0f,  5.0f},
		mat_1sx{
			  0.0f, -3.0f,
			 -1.0f, -4.0f,
			 -2.0f, -5.0f},
		mat_2x{
			  2.0f,  8.0f,
			  4.0f, 10.0f,
			  6.0f, 12.0f},
		mat_xd2{
			  0.5f,  2.0f,
			  1.0f,  2.5f,
			  1.5f,  3.0f},
		mat_2dx{
			  2.0f/1.0f, 2.0f/4.0f,
			  2.0f/2.0f, 2.0f/5.0f,
			  2.0f/3.0f, 2.0f/6.0f}
	;
	TEST_MAT_OPS(
		am::linear::mat3x2,
		mat_i,
		mat_x,
		// unary plus and minus
		 mat_x,
		 mat_nx,
		// Prefix and postfix increment and decrement
		 mat_xa1,
		 mat_xs1,
		// scalar add
		 1.0f,
		 mat_xa1,
		// scalar subtract
		 1.0f,
		 mat_xs1, // rhs result
		 mat_1sx, // lhs result
		// scalar multiply
		 2.0f,
		 mat_2x,
		// scalar divide
		 2.0f,
		 mat_xd2, // rhs result
		 mat_2dx, // lhs result
		// matrix add
		 mat_x,
		 mat_2x,
		// matrix subtract
		 mat_x,
		 mat_0, // rhs result
		 mat_0  // lhs result
	);

	// Multiplications
	// 3x2 * 2x3 -> 2x2
	am::linear::mat2x3 const
		mat_y23{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f}
	;
	am::linear::mat2x2 const
		mat_xy23{
			1.0f, 4.0f,
			2.0f, 5.0f}
	;
	// 3x2 * 3x3 -> 3x2
	am::linear::mat3x3 const
		mat_y33{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f}
	;
	am::linear::mat3x2 const
		mat_xy33{mat_x}
	;
	// 3x2 * 4x3 -> 4x2
	am::linear::mat4x3 const
		mat_y43{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.0f}
	;
	am::linear::mat4x2 const
		mat_xy43{
			1.0f, 4.0f,
			2.0f, 5.0f,
			3.0f, 6.0f,
			0.0f, 0.0f}
	;
	TEST_MAT_XOP_RHS(mat_x, *, mat_y23, mat_xy23);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y33, mat_xy33);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y43, mat_xy43);

	// Properties
	am::linear::mat2x3 const
		mat_x_tr{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f}
	;
	TEST_MAT_PROPERTIES(
		mat_x,
		mat_x_tr
	);
}

void test_mat3x3() {
	// Operators
	am::linear::mat3x3 const
		mat_i{
			  1.0f,  0.0f,  0.0f,
			  0.0f,  1.0f,  0.0f,
			  0.0f,  0.0f,  1.0f},
		mat_0{
			  0.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  0.0f},
		mat_x{
			  1.0f,  4.0f,  7.0f,
			  2.0f,  5.0f,  8.0f,
			  3.0f,  6.0f,  9.0f},
		mat_nx{
			 -1.0f, -4.0f, -7.0f,
			 -2.0f, -5.0f, -8.0f,
			 -3.0f, -6.0f, -9.0f},
		mat_xa1{
			  2.0f,  5.0f,  8.0f,
			  3.0f,  6.0f,  9.0f,
			  4.0f,  7.0f, 10.0f},
		mat_xs1{
			  0.0f,  3.0f,  6.0f,
			  1.0f,  4.0f,  7.0f,
			  2.0f,  5.0f,  8.0f},
		mat_1sx{
			  0.0f, -3.0f, -6.0f,
			 -1.0f, -4.0f, -7.0f,
			 -2.0f, -5.0f, -8.0f},
		mat_2x{
			  2.0f,  8.0f, 14.0f,
			  4.0f, 10.0f, 16.0f,
			  6.0f, 12.0f, 18.0f},
		mat_xd2{
			  0.5f,  2.0f,  3.5f,
			  1.0f,  2.5f,  4.0f,
			  1.5f,  3.0f,  4.5f},
		mat_2dx{
			  2.0f/1.0f, 2.0f/4.0f, 2.0f/7.0f,
			  2.0f/2.0f, 2.0f/5.0f, 2.0f/8.0f,
			  2.0f/3.0f, 2.0f/6.0f, 2.0f/9.0f},
		mat_u{
			  1.0f,  2.0f,  3.0f,
			  2.0f,  3.0f,  2.0f,
			  3.0f,  2.0f,  1.0f},
		mat_idu{
			0.125f, -0.5f,0.625f,
			 -0.5f,  1.0f, -0.5f,
			0.625f, -0.5f,0.125f}
	;
	TEST_MAT_OPS_SQUARE(
		am::linear::mat3x3,
		mat_i,
		mat_x,
		// unary plus and minus
		 mat_x,
		 mat_nx,
		// Prefix and postfix increment and decrement
		 mat_xa1,
		 mat_xs1,
		// scalar add
		 1.0f,
		 mat_xa1,
		// scalar subtract
		 1.0f,
		 mat_xs1, // rhs result
		 mat_1sx, // lhs result
		// scalar multiply
		 2.0f,
		 mat_2x,
		// scalar divide
		 2.0f,
		 mat_xd2, // rhs result
		 mat_2dx, // lhs result

		// matrix add
		 mat_x,
		 mat_2x,
		// matrix subtract
		 mat_x,
		 mat_0, // rhs result
		 mat_0, // lhs result
		// identity-matrix divide
		 mat_u,  // lhs operand
		 mat_idu // lhs result
	);

	// Multiplications
	// 3x3 * 2x3 -> 2x3
	am::linear::mat2x3 const
		mat_y23{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f}
	;
	am::linear::mat2x3 const
		mat_xy23{
			1.0f, 4.0f, 7.0f,
			2.0f, 5.0f, 8.0f}
	;
	// 3x3 * 3x3 -> 3x3
	am::linear::mat3x3 const
		mat_y33{mat_i}
	;
	am::linear::mat3x3 const
		mat_xy33{mat_x}
	;
	// 3x3 * 4x3 -> 4x3
	am::linear::mat4x3 const
		mat_y43{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.0f}
	;
	am::linear::mat4x3 const
		mat_xy43{
			1.0f, 4.0f, 7.0f,
			2.0f, 5.0f, 8.0f,
			3.0f, 6.0f, 9.0f,
			0.0f, 0.0f, 0.0f}
	;
	TEST_MAT_XOP_RHS(mat_x, *, mat_y23, mat_xy23);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y33, mat_xy33);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y43, mat_xy43);

	// Properties
	am::linear::mat3x3 const
		mat_x_tr{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f}
	;
	TEST_MAT_PROPERTIES_SQUARE(
		mat_x,
		mat_x_tr,
		0.0f,
		mat_u, -8.0f, mat_idu
	);
}

void test_mat3x4() {
	// Operators
	am::linear::mat3x4 const
		mat_i{
			  1.0f,  0.0f,  0.0f,  0.0f,
			  0.0f,  1.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  1.0f,  0.0f},
		mat_0{
			  0.0f,  0.0f,  0.0f, 0.0f,
			  0.0f,  0.0f,  0.0f, 0.0f,
			  0.0f,  0.0f,  0.0f, 0.0f},
		mat_x{
			  1.0f,  4.0f,  7.0f, 10.0f,
			  2.0f,  5.0f,  8.0f, 11.0f,
			  3.0f,  6.0f,  9.0f, 12.0f},
		mat_nx{
			 -1.0f, -4.0f, -7.0f,-10.0f,
			 -2.0f, -5.0f, -8.0f,-11.0f,
			 -3.0f, -6.0f, -9.0f,-12.0f},
		mat_xa1{
			  2.0f,  5.0f,  8.0f, 11.0f,
			  3.0f,  6.0f,  9.0f, 12.0f,
			  4.0f,  7.0f, 10.0f, 13.0f},
		mat_xs1{
			  0.0f,  3.0f,  6.0f,  9.0f,
			  1.0f,  4.0f,  7.0f, 10.0f,
			  2.0f,  5.0f,  8.0f, 11.0f},
		mat_1sx{
			  0.0f, -3.0f, -6.0f, -9.0f,
			 -1.0f, -4.0f, -7.0f,-10.0f,
			 -2.0f, -5.0f, -8.0f,-11.0f},
		mat_2x{
			  2.0f,  8.0f, 14.0f, 20.0f,
			  4.0f, 10.0f, 16.0f, 22.0f,
			  6.0f, 12.0f, 18.0f, 24.0f},
		mat_xd2{
			  0.5f,  2.0f,  3.5f,  5.0f,
			  1.0f,  2.5f,  4.0f,  5.5f,
			  1.5f,  3.0f,  4.5f,  6.0f},
		mat_2dx{
			  2.0f/1.0f, 2.0f/4.0f, 2.0f/7.0f, 2.0f/10.0f,
			  2.0f/2.0f, 2.0f/5.0f, 2.0f/8.0f, 2.0f/11.0f,
			  2.0f/3.0f, 2.0f/6.0f, 2.0f/9.0f, 2.0f/12.0f}
	;
	TEST_MAT_OPS(
		am::linear::mat3x4,
		mat_i,
		mat_x,
		// unary plus and minus
		 mat_x,
		 mat_nx,
		// Prefix and postfix increment and decrement
		 mat_xa1,
		 mat_xs1,
		// scalar add
		 1.0f,
		 mat_xa1,
		// scalar subtract
		 1.0f,
		 mat_xs1, // rhs result
		 mat_1sx, // lhs result
		// scalar multiply
		 2.0f,
		 mat_2x,
		// scalar divide
		 2.0f,
		 mat_xd2, // rhs result
		 mat_2dx, // lhs result
		// matrix add
		 mat_x,
		 mat_2x,
		// matrix subtract
		 mat_x,
		 mat_0, // rhs result
		 mat_0  // lhs result
	);

	// Multiplications
	// 3x4 * 2x3 -> 2x4
	am::linear::mat2x3 const
		mat_y23{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f}
	;
	am::linear::mat2x4 const
		mat_xy23{
			1.0f, 4.0f, 7.0f, 10.0f,
			2.0f, 5.0f, 8.0f, 11.0f}
	;
	// 3x4 * 3x3 -> 3x4
	am::linear::mat3x3 const
		mat_y33{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f}
	;
	am::linear::mat3x4 const
		mat_xy33{mat_x}
	;
	// 3x4 * 4x3 -> 4x4
	am::linear::mat4x3 const
		mat_y43{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.0f}
	;
	am::linear::mat4x4 const
		mat_xy43{
			1.0f, 4.0f, 7.0f, 10.0f,
			2.0f, 5.0f, 8.0f, 11.0f,
			3.0f, 6.0f, 9.0f, 12.0f,
			0.0f, 0.0f, 0.0f, 0.0f}
	;
	TEST_MAT_XOP_RHS(mat_x, *, mat_y23, mat_xy23);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y33, mat_xy33);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y43, mat_xy43);

	// Properties
	am::linear::mat4x3 const
		mat_x_tr{
			 1.0f,  2.0f,  3.0f,
			 4.0f,  5.0f,  6.0f,
			 7.0f,  8.0f,  9.0f,
			10.0f, 11.0f, 12.0f}
	;
	TEST_MAT_PROPERTIES(
		mat_x,
		mat_x_tr
	);
}

void test_mat4x2() {
	// Operators
	am::linear::mat4x2 const
		mat_i{
			  1.0f,  0.0f,
			  0.0f,  1.0f,
			  0.0f,  0.0f,
			  0.0f,  0.0f},
		mat_0{
			  0.0f,  0.0f,
			  0.0f,  0.0f,
			  0.0f,  0.0f,
			  0.0f,  0.0f},
		mat_x{
			  1.0f,  5.0f,
			  2.0f,  6.0f,
			  3.0f,  7.0f,
			  4.0f,  8.0f},
		mat_nx{
			 -1.0f, -5.0f,
			 -2.0f, -6.0f,
			 -3.0f, -7.0f,
			 -4.0f, -8.0f},
		mat_xa1{
			  2.0f,  6.0f,
			  3.0f,  7.0f,
			  4.0f,  8.0f,
			  5.0f,  9.0f},
		mat_xs1{
			  0.0f,  4.0f,
			  1.0f,  5.0f,
			  2.0f,  6.0f,
			  3.0f,  7.0f},
		mat_1sx{
			 -0.0f, -4.0f,
			 -1.0f, -5.0f,
			 -2.0f, -6.0f,
			 -3.0f, -7.0f},
		mat_2x{
			  2.0f, 10.0f,
			  4.0f, 12.0f,
			  6.0f, 14.0f,
			  8.0f, 16.0f},
		mat_xd2{
			  0.5f,  2.5f,
			  1.0f,  3.0f,
			  1.5f,  3.5f,
			  2.0f,  4.0f},
		mat_2dx{
			 2.0f/1.0f, 2.0f/5.0f,
			 2.0f/2.0f, 2.0f/6.0f,
			 2.0f/3.0f, 2.0f/7.0f,
			 2.0f/4.0f, 2.0f/8.0f}
	;
	TEST_MAT_OPS(
		am::linear::mat4x2,
		mat_i,
		mat_x,
		// unary plus and minus
		 mat_x,
		 mat_nx,
		// Prefix and postfix increment and decrement
		 mat_xa1,
		 mat_xs1,
		// scalar add
		 1.0f,
		 mat_xa1,
		// scalar subtract
		 1.0f,
		 mat_xs1, // rhs result
		 mat_1sx, // lhs result
		// scalar multiply
		 2.0f,
		 mat_2x,
		// scalar divide
		 2.0f,
		 mat_xd2, // rhs result
		 mat_2dx, // lhs result
		// matrix add
		 mat_x,
		 mat_2x,
		// matrix subtract
		 mat_x,
		 mat_0, // rhs result
		 mat_0  // lhs result
	);

	// Multiplications
	// 4x2 * 2x4 -> 2x2
	am::linear::mat2x4 const
		mat_y24{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f}
	;
	am::linear::mat2x2 const
		mat_xy24{
			1.0f, 5.0f,
			2.0f, 6.0f}
	;
	// 4x2 * 3x4 -> 3x2
	am::linear::mat3x4 const
		mat_y34{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f}
	;
	am::linear::mat3x2 const
		mat_xy34{
			1.0f, 5.0f,
			2.0f, 6.0f,
			3.0f, 7.0f}
	;
	// 4x2 * 4x4 -> 4x2
	am::linear::mat4x4 const
		mat_y44{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f}
	;
	am::linear::mat4x2 const
		mat_xy44{mat_x}
	;
	TEST_MAT_XOP_RHS(mat_x, *, mat_y24, mat_xy24);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y34, mat_xy34);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y44, mat_xy44);

	// Properties
	am::linear::mat2x4 const
		mat_x_tr{
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f}
	;
	TEST_MAT_PROPERTIES(
		mat_x,
		mat_x_tr
	);
}

void test_mat4x3() {
	// Operators
	am::linear::mat4x3 const
		mat_i{
			  1.0f,  0.0f,  0.0f,
			  0.0f,  1.0f,  0.0f,
			  0.0f,  0.0f,  1.0f,
			  0.0f,  0.0f,  0.0f},
		mat_0{
			  0.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  0.0f},
		mat_x{
			  1.0f,  5.0f,  9.0f,
			  2.0f,  6.0f, 10.0f,
			  3.0f,  7.0f, 11.0f,
			  4.0f,  8.0f, 12.0f},
		mat_nx{
			 -1.0f, -5.0f, -9.0f,
			 -2.0f, -6.0f,-10.0f,
			 -3.0f, -7.0f,-11.0f,
			 -4.0f, -8.0f,-12.0f},
		mat_xa1{
			  2.0f,  6.0f, 10.0f,
			  3.0f,  7.0f, 11.0f,
			  4.0f,  8.0f, 12.0f,
			  5.0f,  9.0f, 13.0f},
		mat_xs1{
			  0.0f,  4.0f,  8.0f,
			  1.0f,  5.0f,  9.0f,
			  2.0f,  6.0f, 10.0f,
			  3.0f,  7.0f, 11.0f},
		mat_1sx{
			 -0.0f, -4.0f, -8.0f,
			 -1.0f, -5.0f, -9.0f,
			 -2.0f, -6.0f,-10.0f,
			 -3.0f, -7.0f,-11.0f},
		mat_2x{
			  2.0f, 10.0f, 18.0f,
			  4.0f, 12.0f, 20.0f,
			  6.0f, 14.0f, 22.0f,
			  8.0f, 16.0f, 24.0f},
		mat_xd2{
			  0.5f,  2.5f, 4.5f,
			  1.0f,  3.0f, 5.0f,
			  1.5f,  3.5f, 5.5f,
			  2.0f,  4.0f, 6.0f},
		mat_2dx{
			 2.0f/1.0f, 2.0f/5.0f, 2.0f/ 9.0f,
			 2.0f/2.0f, 2.0f/6.0f, 2.0f/10.0f,
			 2.0f/3.0f, 2.0f/7.0f, 2.0f/11.0f,
			 2.0f/4.0f, 2.0f/8.0f, 2.0f/12.0f}
	;
	TEST_MAT_OPS(
		am::linear::mat4x3,
		mat_i,
		mat_x,
		// unary plus and minus
		 mat_x,
		 mat_nx,
		// Prefix and postfix increment and decrement
		 mat_xa1,
		 mat_xs1,
		// scalar add
		 1.0f,
		 mat_xa1,
		// scalar subtract
		 1.0f,
		 mat_xs1, // rhs result
		 mat_1sx, // lhs result
		// scalar multiply
		 2.0f,
		 mat_2x,
		// scalar divide
		 2.0f,
		 mat_xd2, // rhs result
		 mat_2dx, // lhs result
		// matrix add
		 mat_x,
		 mat_2x,
		// matrix subtract
		 mat_x,
		 mat_0, // rhs result
		 mat_0  // lhs result
	);

	// Multiplications
	// 4x3 * 2x4 -> 2x3
	am::linear::mat2x4 const
		mat_y24{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f}
	;
	am::linear::mat2x3 const
		mat_xy24{
			1.0f, 5.0f, 9.0f,
			2.0f, 6.0f,10.0f}
	;
	// 4x3 * 3x4 -> 3x3
	am::linear::mat3x4 const
		mat_y34{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f}
	;
	am::linear::mat3x3 const
		mat_xy34{
			1.0f, 5.0f, 9.0f,
			2.0f, 6.0f,10.0f,
			3.0f, 7.0f,11.0f}
	;
	// 4x3 * 4x4 -> 4x3
	am::linear::mat4x4 const
		mat_y44{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f}
	;
	am::linear::mat4x3 const
		mat_xy44{mat_x}
	;
	TEST_MAT_XOP_RHS(mat_x, *, mat_y24, mat_xy24);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y34, mat_xy34);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y44, mat_xy44);

	// Properties
	am::linear::mat3x4 const
		mat_x_tr{
			1.0f,  2.0f,  3.0f,  4.0f,
			5.0f,  6.0f,  7.0f,  8.0f,
			9.0f, 10.0f, 11.0f, 12.0f}
	;
	TEST_MAT_PROPERTIES(
		mat_x,
		mat_x_tr
	);
}

void test_mat4x4() {
	// Operators
	am::linear::mat4x4 const
		mat_i{
			  1.0f,  0.0f,  0.0f,  0.0f,
			  0.0f,  1.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  1.0f,  0.0f,
			  0.0f,  0.0f,  0.0f,  1.0f},
		mat_0{
			  0.0f,  0.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  0.0f,  0.0f,
			  0.0f,  0.0f,  0.0f,  0.0f},
		mat_x{
			  1.0f,  5.0f,  9.0f, 13.0f,
			  2.0f,  6.0f, 10.0f, 14.0f,
			  3.0f,  7.0f, 11.0f, 15.0f,
			  4.0f,  8.0f, 12.0f, 16.0f},
		mat_nx{
			 -1.0f, -5.0f, -9.0f,-13.0f,
			 -2.0f, -6.0f,-10.0f,-14.0f,
			 -3.0f, -7.0f,-11.0f,-15.0f,
			 -4.0f, -8.0f,-12.0f,-16.0f},
		mat_xa1{
			  2.0f,  6.0f, 10.0f, 14.0f,
			  3.0f,  7.0f, 11.0f, 15.0f,
			  4.0f,  8.0f, 12.0f, 16.0f,
			  5.0f,  9.0f, 13.0f, 17.0f},
		mat_xs1{
			  0.0f,  4.0f,  8.0f, 12.0f,
			  1.0f,  5.0f,  9.0f, 13.0f,
			  2.0f,  6.0f, 10.0f, 14.0f,
			  3.0f,  7.0f, 11.0f, 15.0f},
		mat_1sx{
			  0.0f, -4.0f, -8.0f,-12.0f,
			 -1.0f, -5.0f, -9.0f,-13.0f,
			 -2.0f, -6.0f,-10.0f,-14.0f,
			 -3.0f, -7.0f,-11.0f,-15.0f},
		mat_2x{
			  2.0f, 10.0f, 18.0f, 26.0f,
			  4.0f, 12.0f, 20.0f, 28.0f,
			  6.0f, 14.0f, 22.0f, 30.0f,
			  8.0f, 16.0f, 24.0f, 32.0f},
		mat_xd2{
			  0.5f,  2.5f,  4.5f,  6.5f,
			  1.0f,  3.0f,  5.0f,  7.0f,
			  1.5f,  3.5f,  5.5f,  7.5f,
			  2.0f,  4.0f,  6.0f,  8.0f},
		mat_2dx{
			  2.0f/1.0f, 2.0f/5.0f, 2.0f/ 9.0f, 2.0f/13.0f,
			  2.0f/2.0f, 2.0f/6.0f, 2.0f/10.0f, 2.0f/14.0f,
			  2.0f/3.0f, 2.0f/7.0f, 2.0f/11.0f, 2.0f/15.0f,
			  2.0f/4.0f, 2.0f/8.0f, 2.0f/12.0f, 2.0f/16.0f},
		mat_u{
			  1.0f,  2.0f,  3.0f,  4.0f,
			  2.0f,  5.0f,  2.0f,  3.0f,
			  3.0f,  2.0f,  5.0f,  2.0f,
			  4.0f,  3.0f,  2.0f,  1.0f},
		mat_idu{
			  0.2f, -0.3f, -0.2f,  0.5f,
			 -0.3f,  0.4f,  0.1f, -0.2f,
			 -0.2f,  0.1f,  0.4f, -0.3f,
			  0.5f, -0.2f, -0.3f,  0.2f}
	;
	TEST_MAT_OPS_SQUARE(
		am::linear::mat4x4,
		mat_i,
		mat_x,
		// unary plus and minus
		 mat_x,
		 mat_nx,
		// Prefix and postfix increment and decrement
		 mat_xa1,
		 mat_xs1,
		// scalar add
		 1.0f,
		 mat_xa1,
		// scalar subtract
		 1.0f,
		 mat_xs1, // rhs result
		 mat_1sx, // lhs result
		// scalar multiply
		 2.0f,
		 mat_2x,
		// scalar divide
		 2.0f,
		 mat_xd2, // rhs result
		 mat_2dx, // lhs result

		// matrix add
		 mat_x,
		 mat_2x,
		// matrix subtract
		 mat_x,
		 mat_0, // rhs result
		 mat_0, // lhs result
		// identity-matrix divide
		 mat_u,  // lhs operand
		 mat_idu // lhs result
	);

	// Multiplications
	// 4x4 * 2x4 -> 2x4
	am::linear::mat2x4 const
		mat_y24{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f}
	;
	am::linear::mat2x4 const
		mat_xy24{
			1.0f, 5.0f, 9.0f,13.0f,
			2.0f, 6.0f,10.0f,14.0f}
	;
	// 4x4 * 3x4 -> 3x4
	am::linear::mat3x4 const
		mat_y34{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f}
	;
	am::linear::mat3x4 const
		mat_xy34{
			1.0f, 5.0f, 9.0f,13.0f,
			2.0f, 6.0f,10.0f,14.0f,
			3.0f, 7.0f,11.0f,15.0f}
	;
	// 4x4 * 4x4 -> 4x4
	am::linear::mat4x4 const
		mat_y44{mat_i}
	;
	am::linear::mat4x4 const
		mat_xy44{mat_x}
	;
	TEST_MAT_XOP_RHS(mat_x, *, mat_y24, mat_xy24);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y34, mat_xy34);
	TEST_MAT_XOP_RHS(mat_x, *, mat_y44, mat_xy44);

	// Properties
	am::linear::mat4x4 const
		mat_x_tr{
			 1.0f, 2.0f, 3.0f, 4.0f,
			 5.0f, 6.0f, 7.0f, 8.0f,
			 9.0f,10.0f,11.0f,12.0f,
			13.0f,14.0f,15.0f,16.0f}
	;
	TEST_MAT_PROPERTIES_SQUARE(
		mat_x,
		mat_x_tr,
		0.0f,
		mat_u, -100.0f, mat_idu
	);
}

int main(int argc, char const* argv[]) {
	test_mat2x2();
	test_mat2x3();
	test_mat2x4();

	test_mat3x2();
	test_mat3x3();
	test_mat3x4();

	test_mat4x2();
	test_mat4x3();
	test_mat4x4();
	return 0;
}
