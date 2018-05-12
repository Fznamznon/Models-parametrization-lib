#pragma once

/*!
\file
\brief Header file with vec3 and vec4 classes.
*/

namespace param {
namespace Math {
/*!
  \brief Class describing 3-dimensional vector.
  \author Fznamznon
*/
struct vec3 {
  double x;
  double y;
  double z;
  vec3() = default;
  vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
  ~vec3() = default;
};

/*!
  \brief Class describing 4-dimensional vector.
  \author Fznamznon
*/
struct vec4 {
  double x;
  double y;
  double z;
  double a;
  vec4() = default;
  vec4(double _x, double _y, double _z, double _a)
      : x(_x), y(_y), z(_z), a(_a) {}
  ~vec4() = default;
};
} // namespace Math
} // namespace param
