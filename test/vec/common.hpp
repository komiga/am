
#pragma once

#include "../general/common.hpp"

// Comparison operators
#define TEST_VEC_COP_ALL(pretype, value, op, operand)\
	TEST_VEC_COP(am::linear::pretype ## 1 {value}, op, operand);\
	TEST_VEC_COP(am::linear::pretype ## 2 {value}, op, operand);\
	TEST_VEC_COP(am::linear::pretype ## 3 {value}, op, operand);\
	TEST_VEC_COP(am::linear::pretype ## 4 {value}, op, operand)

#define TEST_VEC_COP(vec, op, operand) {\
	auto const x = vec;\
	auto const y = decltype(x){operand};\
	fassert(x op y);\
}

// Assignment operators
#define TEST_VEC_AOP_ALL(pretype, value, op, operand, result)\
	TEST_VEC_AOP(am::linear::pretype ## 1 {value}, op, operand, result);\
	TEST_VEC_AOP(am::linear::pretype ## 2 {value}, op, operand, result);\
	TEST_VEC_AOP(am::linear::pretype ## 3 {value}, op, operand, result);\
	TEST_VEC_AOP(am::linear::pretype ## 4 {value}, op, operand, result)

#define TEST_VEC_AOP(vec, op, operand, result) {\
	auto x = vec;\
	x op## = operand;\
	fassert(x == (decltype(x){result}));\
}

// Construct operators
#define TEST_VEC_XOP_ALL(pretype, value, op, operand, rhs_result, lhs_result)\
	TEST_VEC_XOP_RHS(am::linear::pretype ## 1 {value}, op, operand, rhs_result);\
	TEST_VEC_XOP_LHS(am::linear::pretype ## 1 {value}, op, operand, lhs_result);\
	TEST_VEC_XOP_RHS(am::linear::pretype ## 2 {value}, op, operand, rhs_result);\
	TEST_VEC_XOP_LHS(am::linear::pretype ## 2 {value}, op, operand, lhs_result);\
	TEST_VEC_XOP_RHS(am::linear::pretype ## 3 {value}, op, operand, rhs_result);\
	TEST_VEC_XOP_LHS(am::linear::pretype ## 3 {value}, op, operand, lhs_result);\
	TEST_VEC_XOP_RHS(am::linear::pretype ## 4 {value}, op, operand, rhs_result);\
	TEST_VEC_XOP_LHS(am::linear::pretype ## 4 {value}, op, operand, lhs_result)

#define TEST_VEC_XOP(vec, op, operand, rhs_result, lhs_result)\
	TEST_VEC_XOP_RHS(vec, op, operand, rhs_result);\
	TEST_VEC_XOP_LHS(vec, op, operand, lhs_result)

#define TEST_VEC_XOP_RHS(vec, op, operand, result) {\
	auto const x = vec;\
	auto const y = (x op operand);\
	fassert(y == (decltype(x){result}));\
}

#define TEST_VEC_XOP_LHS(vec, op, operand, result) {\
	auto const x = vec;\
	auto const y = (operand op x);\
	fassert(y == (decltype(x){result}));\
}

// Unary operators
#define TEST_VEC_UOP_ALL(pretype, value, op, result)\
	TEST_VEC_UOP(am::linear::pretype ## 1 {value}, op, result);\
	TEST_VEC_UOP(am::linear::pretype ## 2 {value}, op, result);\
	TEST_VEC_UOP(am::linear::pretype ## 3 {value}, op, result);\
	TEST_VEC_UOP(am::linear::pretype ## 4 {value}, op, result)

#define TEST_VEC_UOP(vec, op, result) {\
	auto const x = vec;\
	auto const y = op x;\
	fassert(y == (decltype(x){result}));\
}

// Prefix operators
#define TEST_VEC_POP_ALL(pretype, value, op, result)\
	TEST_VEC_POP(am::linear::pretype ## 1 {value}, op, result);\
	TEST_VEC_POP(am::linear::pretype ## 2 {value}, op, result);\
	TEST_VEC_POP(am::linear::pretype ## 3 {value}, op, result);\
	TEST_VEC_POP(am::linear::pretype ## 4 {value}, op, result)

#define TEST_VEC_POP(vec, op, result) {\
	auto x = vec;\
	fassert((op x) == (decltype(x){result}));\
}

// Suffix/postfix operators
#define TEST_VEC_SOP_ALL(pretype, value, op, result)\
	TEST_VEC_SOP(am::linear::pretype ## 1 {value}, op, result);\
	TEST_VEC_SOP(am::linear::pretype ## 2 {value}, op, result);\
	TEST_VEC_SOP(am::linear::pretype ## 3 {value}, op, result);\
	TEST_VEC_SOP(am::linear::pretype ## 4 {value}, op, result)

#define TEST_VEC_SOP(vec, op, result) {\
	auto x = vec;\
	fassert((x op) == (vec));\
	fassert((x op) == (decltype(x){result}));\
}
