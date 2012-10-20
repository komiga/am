
#ifndef AM_TESTS_COMMON_VECTOR_HPP_
#define AM_TESTS_COMMON_VECTOR_HPP_

#include <am/config.hpp>
#include <am/vec1.hpp>
#include <am/vec2.hpp>
#include <am/vec3.hpp>
#include <am/vec4.hpp>

#include <cassert>

// Comparison operators
#define AM_TEST_VEC_COP_ALL(pretype, value, op, operand)\
	AM_TEST_VEC_COP(pretype ## 1 {value}, op, operand);\
	AM_TEST_VEC_COP(pretype ## 2 {value}, op, operand);\
	AM_TEST_VEC_COP(pretype ## 3 {value}, op, operand);\
	AM_TEST_VEC_COP(pretype ## 4 {value}, op, operand)

#define AM_TEST_VEC_COP(vec, op, operand) {\
		auto const x=vec;\
		auto const y=decltype(x){operand};\
		assert(x op y);\
	}

// Assignment operators
#define AM_TEST_VEC_AOP_ALL(pretype, value, op, operand, result)\
	AM_TEST_VEC_AOP(pretype ## 1 {value}, op, operand, result);\
	AM_TEST_VEC_AOP(pretype ## 2 {value}, op, operand, result);\
	AM_TEST_VEC_AOP(pretype ## 3 {value}, op, operand, result);\
	AM_TEST_VEC_AOP(pretype ## 4 {value}, op, operand, result)

#define AM_TEST_VEC_AOP(vec, op, operand, result) {\
		auto x=vec;\
		x op##= operand;\
		assert(x.operator==(decltype(x){result}));\
	}

// Construct operators
#define AM_TEST_VEC_XOP_ALL(pretype, value, op, operand, rhs_result, lhs_result)\
	AM_TEST_VEC_XOP_RHS(pretype ## 1 {value}, op, operand, rhs_result);\
	AM_TEST_VEC_XOP_LHS(pretype ## 1 {value}, op, operand, lhs_result);\
	AM_TEST_VEC_XOP_RHS(pretype ## 2 {value}, op, operand, rhs_result);\
	AM_TEST_VEC_XOP_LHS(pretype ## 2 {value}, op, operand, lhs_result);\
	AM_TEST_VEC_XOP_RHS(pretype ## 3 {value}, op, operand, rhs_result);\
	AM_TEST_VEC_XOP_LHS(pretype ## 3 {value}, op, operand, lhs_result);\
	AM_TEST_VEC_XOP_RHS(pretype ## 4 {value}, op, operand, rhs_result);\
	AM_TEST_VEC_XOP_LHS(pretype ## 4 {value}, op, operand, lhs_result)

#define AM_TEST_VEC_XOP(vec, op, operand, rhs_result, lhs_result)\
	AM_TEST_VEC_XOP_RHS(vec, op, operand, rhs_result);\
	AM_TEST_VEC_XOP_LHS(vec, op, operand, lhs_result)

#define AM_TEST_VEC_XOP_RHS(vec, op, operand, result) {\
		auto const x=vec;\
		auto const y=(x op operand);\
		assert(y.operator==(decltype(x){result}));\
	}

#define AM_TEST_VEC_XOP_LHS(vec, op, operand, result) {\
		auto const x=vec;\
		auto const y=(operand op x);\
		assert(y.operator==(decltype(x){result}));\
	}

// Unary operators
#define AM_TEST_VEC_UOP_ALL(pretype, value, op, result)\
	AM_TEST_VEC_UOP(pretype ## 1 {value}, op, result);\
	AM_TEST_VEC_UOP(pretype ## 2 {value}, op, result);\
	AM_TEST_VEC_UOP(pretype ## 3 {value}, op, result);\
	AM_TEST_VEC_UOP(pretype ## 4 {value}, op, result)

#define AM_TEST_VEC_UOP(vec, op, result) {\
		auto const x=vec;\
		auto const y=op x;\
		assert(y.operator==(decltype(x){result}));\
	}

// Prefix operators
#define AM_TEST_VEC_POP_ALL(pretype, value, op, result)\
	AM_TEST_VEC_POP(pretype ## 1 {value}, op, result);\
	AM_TEST_VEC_POP(pretype ## 2 {value}, op, result);\
	AM_TEST_VEC_POP(pretype ## 3 {value}, op, result);\
	AM_TEST_VEC_POP(pretype ## 4 {value}, op, result)

#define AM_TEST_VEC_POP(vec, op, result) {\
		auto x=vec;\
		assert((op x).operator==(decltype(x){result}));\
	}

// Suffix/postfix operators
#define AM_TEST_VEC_SOP_ALL(pretype, value, op, result)\
	AM_TEST_VEC_SOP(pretype ## 1 {value}, op, result);\
	AM_TEST_VEC_SOP(pretype ## 2 {value}, op, result);\
	AM_TEST_VEC_SOP(pretype ## 3 {value}, op, result);\
	AM_TEST_VEC_SOP(pretype ## 4 {value}, op, result)

#define AM_TEST_VEC_SOP(vec, op, result) {\
		auto x=vec;\
		assert((x op).operator==(decltype(x){result}));\
	}

#endif // AM_TESTS_COMMON_VECTOR_HPP_
