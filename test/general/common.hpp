
#pragma once

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

