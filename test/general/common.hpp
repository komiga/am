
#ifndef AM_TEST_GENERAL_COMMON_HPP_
#define AM_TEST_GENERAL_COMMON_HPP_

#include <cstdlib>
#include <cstdio>

#define fassert(expr) (							\
	(expr) ? static_cast<void>(0) : (			\
		std::fprintf(							\
			stderr, "assertion failure "		\
			"in %s:%d: %s: `" #expr "`\n",		\
			__FILE__, __LINE__, __func__		\
		),										\
		std::abort()							\
	)											\
)

#endif // AM_TEST_GENERAL_COMMON_HPP_
