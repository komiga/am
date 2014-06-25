
#pragma once

#include "../general/common.hpp"

// Comparison operators
#define TEST_MAT_COP(mat, op, operand) {\
	auto const x = mat;\
	auto const y = operand;\
	fassert(x op y);\
}

// Assignment operators
#define TEST_MAT_AOP(mat, op, operand, result) {\
	auto x = mat;\
	x op## = operand;\
	fassert(x == (result));\
}

// Construct operators
#define TEST_MAT_XOP(mat, op, operand, rhs_result, lhs_result)\
	TEST_MAT_XOP_RHS(mat, op, operand, rhs_result);\
	TEST_MAT_XOP_LHS(mat, op, operand, lhs_result)

#define TEST_MAT_XOP_RHS(mat, op, operand, result) {\
	auto const x = mat;\
	auto const y = (x op operand);\
	fassert(y == (result));\
}

#define TEST_MAT_XOP_LHS(mat, op, operand, result) {\
	auto const x = mat;\
	auto const y = (operand op x);\
	fassert(y == (result));\
}

// Unary operators
#define TEST_MAT_UOP(mat, op, result) {\
	auto const x = mat;\
	auto const y = op x;\
	fassert(y == (result));\
}

// Prefix operators
#define TEST_MAT_POP(mat, op, result) {\
	auto x = mat;\
	fassert((op x) == (result));\
}

// Suffix/postfix operators
#define TEST_MAT_SOP(mat, op, result) {\
	auto x = mat;\
	fassert((x op) == (result));\
}

// Full tests
#define TEST_MAT_OPS(\
	type_, I_, mat_,\
	u_pos_result, u_neg_result,\
	inc_result, dec_result,\
	s_add, s_add_result,\
	s_sub, s_sub_result_r, s_sub_result_l,\
	s_mul, s_mul_result,\
	s_div, s_div_result_r, s_div_result_l,\
	m_add, m_add_result,\
	m_sub, m_sub_result_r, m_sub_result_l\
) {\
	type_ const I = I_;\
	type_ const D{};\
	type_ const mat = mat_;\
	TEST_MAT_COP(I, ==, D);\
	TEST_MAT_COP(mat, !=, D);\
	TEST_MAT_UOP(mat,  +, u_pos_result);\
	TEST_MAT_UOP(mat,  -, u_neg_result);\
	TEST_MAT_POP(mat, ++, inc_result);\
	TEST_MAT_POP(mat, --, dec_result);\
	TEST_MAT_SOP(mat, ++, inc_result);\
	TEST_MAT_SOP(mat, --, dec_result);\
	/* Scalar operators */\
	TEST_MAT_AOP(mat,  +, s_add, s_add_result);\
	TEST_MAT_AOP(mat,  -, s_sub, s_sub_result_r);\
	TEST_MAT_AOP(mat,  *, s_mul, s_mul_result);\
	TEST_MAT_AOP(mat,  /, s_div, s_div_result_r);\
	TEST_MAT_XOP(mat,  +, s_add, s_add_result,   s_add_result);\
	TEST_MAT_XOP(mat,  -, s_sub, s_sub_result_r, s_sub_result_l);\
	TEST_MAT_XOP(mat,  *, s_mul, s_mul_result,   s_mul_result);\
	TEST_MAT_XOP(mat,  /, s_div, s_div_result_r, s_div_result_l);\
	/* Matrix operators */\
	TEST_MAT_AOP(mat,  +, m_add, m_add_result);\
	TEST_MAT_AOP(mat,  -, m_sub, m_sub_result_r);\
	TEST_MAT_XOP(mat,  +, m_add, m_add_result,   m_add_result);\
	TEST_MAT_XOP(mat,  -, m_sub, m_sub_result_r, m_sub_result_l);\
}

#define TEST_MAT_OPS_SQUARE(\
	type_, I_, mat_,\
	u_pos_result, u_neg_result,\
	inc_result, dec_result,\
	s_add, s_add_result,\
	s_sub, s_sub_result_r, s_sub_result_l,\
	s_mul, s_mul_result,\
	s_div, s_div_result_r, s_div_result_l,\
	m_add, m_add_result,\
	m_sub, m_sub_result_r, m_sub_result_l,\
	m_div_l, m_div_result_l\
)\
	TEST_MAT_OPS(type_, I_, mat_,\
		u_pos_result, u_neg_result,\
		inc_result, dec_result,\
		s_add, s_add_result,\
		s_sub, s_sub_result_r, s_sub_result_l,\
		s_mul, s_mul_result,\
		s_div, s_div_result_r, s_div_result_l,\
		m_add, m_add_result,\
		m_sub, m_sub_result_r, m_sub_result_l\
	); {\
		TEST_MAT_AOP(mat_, *, I_, mat_);\
		TEST_MAT_XOP(mat_, *, I_, mat_, mat_);\
		TEST_MAT_AOP(mat_, /, I_, mat_);\
		TEST_MAT_XOP_RHS(mat_, /, I_, mat_);\
		TEST_MAT_XOP_LHS(m_div_l, /, I_, m_div_result_l);\
	}

#define TEST_MAT_OPS_MULDIV(\
	mat,\
	m_mul, m_mul_result_r, m_mul_result_l,\
	m_div, m_div_result_r, m_div_result_l\
) {\
	TEST_MAT_AOP(mat, *, m_mul, m_mul_result);\
	TEST_MAT_XOP(mat, *, m_mul, m_mul_result_r, m_mul_result_l);\
	TEST_MAT_AOP(mat, /, m_div, m_div_result_r);\
	TEST_MAT_XOP(mat, /, m_div, m_div_result_r, m_div_result_l);\
}

// Properties
#define TEST_MAT_PROP(mat, func, result) {\
	auto const x = mat;\
	auto const y = am::linear::func(x);\
	fassert(y == (result));\
}

#define TEST_MAT_PROPERTIES(\
	mat,\
	tr_result\
) {\
	TEST_MAT_PROP(mat, transpose, tr_result);\
}

#define TEST_MAT_PROPERTIES_SQUARE(\
	mat,\
	tr_result,\
	det_result,\
	inv_mat, inv_mat_det, inv_result\
)\
	TEST_MAT_PROPERTIES(\
		mat,\
		tr_result\
	); {\
		TEST_MAT_PROP(mat, determinant, det_result);\
		TEST_MAT_PROP(inv_mat, determinant, inv_mat_det);\
		TEST_MAT_PROP(inv_mat, inverse, inv_result);\
	}

