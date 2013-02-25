
#define AM_CONFIG_VECTOR_TYPES AM_FLAG_TYPE_ALL

#include <am/config.hpp>
#include <am/arithmetic_types.hpp>
#include <am/linear/vector.hpp>
#include <am/linear/matrix.hpp>
#include <am/hash/fnv.hpp>

signed main() {
	am::linear:: vec1 const a1{1.0};
	am::linear::ivec1 const b1{};
	am::linear::uvec1 const c1{};
	am::linear:: vec2 const a2{2.0};
	am::linear::ivec2 const b2{};
	am::linear::uvec2 const c2{};
	am::linear:: vec3 const a3{a2, 3.0};
	am::linear::ivec3 const b3{};
	am::linear::uvec3 const c3{};
	am::linear:: vec4 const a4{a3, 4.0};
	am::linear::ivec4 const b4{};
	am::linear::uvec4 const c4{};

	am::linear::mat2x2 const m22{};
	am::linear::mat2x3 const m23{};
	am::linear::mat2x4 const m24{};

	am::linear::mat3x2 const m32{};
	am::linear::mat3x3 const m33{};
	am::linear::mat3x4 const m34{};

	am::linear::mat4x2 const m42{};
	am::linear::mat4x3 const m43{};
	am::linear::mat4x4 const m44{};
	return 0;
}
