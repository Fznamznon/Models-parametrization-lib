#pragma once

#include "vectors.h"
#include <vector>

/*!
\file
\brief Header file with math functions prototypes.
*/

namespace param {
namespace math {

/*!
Computes barycentric coordinates for point from Cartesian coordinates relatively
affine basis.
\param[in] target - point in 3-dimensional space.
\param[in] bs - vector describing affine basis points.
\return vector of barycentric coordinates.
*/
vec4 computeBCCoords(vec3 target, std::vector<vec3> bs);

/*!
Computes Cartesian coordinates for point from barycentric coordinates relatively
affine basis.
\param[in] bc_coords - point in 3-dimensional space.
\param[in] bs - vector describing affine basis points.
\return vector of Cartesian coordinates.
*/
vec3 computeDecCoords(vec4 bc_coords, std::vector<vec3> bs);

} // namespace Math
} // namespace param
