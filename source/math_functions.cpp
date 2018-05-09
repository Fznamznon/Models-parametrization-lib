#include "math_functions.h"

namespace param {
namespace Math {

// TODO: Rewrite this ugly function
vec4 computeBCCoords(vec3 target, std::vector<vec3> bs) {
  vec4 bc_coords;
  vec3 b1 = bs[0];
  vec3 b2 = bs[1];
  vec3 b3 = bs[2];
  vec3 b4 = bs[3];
  // TODO: Write function to compute determinant
  double maindet = (b2.x - b1.x) * (b3.y - b1.y) * (b4.z - b1.z) +
                   (b2.y - b1.y) * (b3.z - b1.z) * (b4.x - b1.x) +
                   (b3.x - b1.x) * (b4.y - b1.y) * (b2.z - b1.z) -
                   (b4.x - b1.x) * (b3.y - b1.y) * (b2.z - b1.z) -
                   (b3.z - b1.z) * (b4.y - b1.y) * (b2.x - b1.x) -
                   (b3.x - b1.x) * (b2.y - b1.y) * (b4.z - b1.z);
  double det = (target.x - b1.x) * (b3.y - b1.y) * (b4.z - b1.z) +
               (target.y - b1.y) * (b3.z - b1.z) * (b4.x - b1.x) +
               (b3.x - b1.x) * (b4.y - b1.y) * (target.z - b1.z) -
               (b4.x - b1.x) * (b3.y - b1.y) * (target.z - b1.z) -
               (b3.z - b1.z) * (b4.y - b1.y) * (target.x - b1.x) -
               (b3.x - b1.x) * (target.y - b1.y) * (b4.z - b1.z);
  bc_coords.y = det / maindet;
  det = (b2.x - b1.x) * (target.y - b1.y) * (b4.z - b1.z) +
        (b2.y - b1.y) * (target.z - b1.z) * (b4.x - b1.x) +
        (target.x - b1.x) * (b4.y - b1.y) * (b2.z - b1.z) -
        (b4.x - b1.x) * (target.y - b1.y) * (b2.z - b1.z) -
        (target.z - b1.z) * (b4.y - b1.y) * (b2.x - b1.x) -
        (target.x - b1.x) * (b2.y - b1.y) * (b4.z - b1.z);

  bc_coords.z = det / maindet;
  det = (b2.x - b1.x) * (b3.y - b1.y) * (target.z - b1.z) +
        (b2.y - b1.y) * (b3.z - b1.z) * (target.x - b1.x) +
        (b3.x - b1.x) * (target.y - b1.y) * (b2.z - b1.z) -
        (target.x - b1.x) * (b3.y - b1.y) * (b2.z - b1.z) -
        (b3.z - b1.z) * (target.y - b1.y) * (b2.x - b1.x) -
        (b3.x - b1.x) * (b2.y - b1.y) * (target.z - b1.z);

  bc_coords.a = det / maindet;
  bc_coords.x = 1 - bc_coords.y - bc_coords.z - bc_coords.a;
  return bc_coords;
}

// TODO: refactor this ugly function
vec3 computeDecCoords(vec4 bc_coords, std::vector<vec3> bs) {
  vec3 coords;
  vec3 b1 = bs[0];
  vec3 b2 = bs[1];
  vec3 b3 = bs[2];
  vec3 b4 = bs[3];
  coords.x = ((bc_coords.x * b1.x + bc_coords.y * b2.x + bc_coords.z * b3.x +
               bc_coords.a * b4.x) /
              (bc_coords.x + bc_coords.y + bc_coords.z + bc_coords.a));
  coords.y = ((bc_coords.x * b1.y + bc_coords.y * b2.y + bc_coords.z * b3.y +
               bc_coords.a * b4.y) /
              (bc_coords.x + bc_coords.y + bc_coords.z + bc_coords.a));
  coords.z = ((bc_coords.x * b1.z + bc_coords.y * b2.z + bc_coords.z * b3.z +
               bc_coords.a * b4.z) /
              (bc_coords.x + bc_coords.y + bc_coords.z + bc_coords.a));
  return coords;
}
} // namespace Math
} // namespace param
