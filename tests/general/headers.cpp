
#define AM_CONFIG_VECTOR_TYPES AM_FLAG_TYPE_ALL

#include <am/config.hpp>
#include <am/arithmetic_types.hpp>
#include <am/vec1.hpp>
#include <am/vec2.hpp>
#include <am/vec3.hpp>
#include <am/vec4.hpp>
#include <am/mat2x2.hpp>

int main(int argc, char const* argv[]) {
	am::vec1 const  a1{1.0};
	am::ivec1 const b1{};
	am::uvec1 const c1{};
	am::vec2 const  a2{2.0};
	am::ivec2 const b2{};
	am::uvec2 const c2{};
	am::vec3 const  a3{a2, 3.0};
	am::ivec3 const b3{};
	am::uvec3 const c3{};
	am::vec4 const  a4{a3, 4.0};
	am::ivec4 const b4{};
	am::uvec4 const c4{};

	am::mat2x2 const m2x2{};
	return 0;
}
