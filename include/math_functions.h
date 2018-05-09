#pragma once

#include "vectors.h"
#include <vector>

namespace param {
namespace Math {

vec4 computeBCCoords(vec3 target, std::vector<vec3> bs);

vec3 computeDecCoords(vec4 bc_coords, std::vector<vec3> bs);

} // namespace Math
} // namespace param
