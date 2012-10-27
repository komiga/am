
#define AM_CONFIG_VECTOR_TYPES AM_FLAG_TYPE_ALL

#include <am/config.hpp>
#include <am/arithmetic_types.hpp>
#include <am/vector.hpp>
#include <am/matrix.hpp>

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

	am::mat2x2 const m22{};
	am::mat2x3 const m23{};
	am::mat2x4 const m24{};

	am::mat3x2 const m32{};
	am::mat3x3 const m33{};
	am::mat3x4 const m34{};

	am::mat4x2 const m42{};
	am::mat4x3 const m43{};
	am::mat4x4 const m44{};
	return 0;
}
