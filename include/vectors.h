#pragma once

namespace param {
namespace Math {
struct vec3 {
  double x;
  double y;
  double z;
  vec3() = default;
  vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
  ~vec3() = default;
};

struct vec4 {
  double x;
  double y;
  double z;
  double a;
};
} // namespace Math
} // namespace param
