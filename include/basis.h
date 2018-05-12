#pragma once

#include "math_functions.h"
#include <iostream>
#include <vector>

/*!
\file
\brief Header file with Scope-related classes and Basis class.
*/

namespace param {

using namespace Math;

/*!
  \brief Abstract class describing 3-dimensional scope.
  \author Fznamznon

  Derive this class to define custom scope.
  Scopes are needed to determine where the basis is acting.
*/
class Scope {
public:
  /*!
  Returns true if dot inside the current scope
  \param[in] dot - vector describing point in 3-dimensional space.
  */
  virtual bool isDotInside(vec3 dot) const = 0;
  /*! Virtual copy construtor
  */
  virtual Scope *clone() const = 0;
  virtual ~Scope() = default;
};

/*!
  \brief Class describing 3-dimensional scope which is all 3-d space.
  \author Fznamznon
*/
class AllSpaceScope : public Scope {
public:
  AllSpaceScope() = default;
  AllSpaceScope(const AllSpaceScope &) = default;
  bool isDotInside(vec3 dot) const override { return true; }
  Scope *clone() const override { return new AllSpaceScope(*this); }
  ~AllSpaceScope() = default;
};

/*!
  \brief Class describing 3-dimensional scope inside the tetrahedron.
  \author Fznamznon

  Uses barycentric coordinates to understand that point inside the
  tetrahedron
*/
class TetrahedronScope : public Scope {
private:
  std::vector<vec3> vertices; /// Vertices of Tetrahedron

public:
  TetrahedronScope() = delete;
  TetrahedronScope(const TetrahedronScope &) = default;
  TetrahedronScope(std::vector<vec3> _vertices) {
    // TODO: check vector size
    this->vertices = _vertices;
  }
  bool isDotInside(vec3 dot) const override {
    vec4 coords = Math::computeBCCoords(dot, this->vertices);
    // TODO: make this check more pretty
    if (coords.x >= 0 && coords.y >= 0 && coords.z >= 0 && coords.a >= 0) {
      return true;
    }
    return false;
  }
  Scope *clone() const override { return new TetrahedronScope(*this); }
  ~TetrahedronScope() = default;
};

/*!
  \brief Class describing affine basis in 3-dimensional space.
  \author Fznamznon
*/
class Basis {
private:
  /// Points of basis
  std::vector<vec3> points;
  /// Acting scope
  Scope *scope;

public:
  /*!
    Default constructor for Basis.
    All points are (0,0,0) and Scope is AllSpaceScope
  */
  Basis() { this->scope = new AllSpaceScope(); }
  Basis(const Basis &other) {
    this->scope = other.scope->clone();
    this->points = other.points;
  }
  /*!
  Constructor with vector parameter.
  Points will be copied from vector, Scope is AllSpaceScope
  \param[in] ps - vector describing basis points in 3-dimensional space.
  */
  Basis(std::vector<vec3> ps) : points(ps) {
    this->scope = new AllSpaceScope();
  }
  /*!
  Constructor with vector and Scope parameters.
  Points will be copied from vector, Scope will be managed by basis.
  \warning don't delete Scope memory!
  \param[in] ps - vector describing basis points in 3-dimensional space.
  \param[in] s - scope for new basis.
  */
  Basis(std::vector<vec3> ps, Scope *s) : points(ps), scope(s) {}
  Basis &operator=(const Basis &other) {
    if (this != &other) {
      delete this->scope;
      this->scope = other.scope->clone();
      this->points = other.points;
    }
    return *this;
  }
  /*!
  Returns true if this basis works for this dot.
  \param[in] dot - vector describing point in 3-dimensional space.
  */
  bool worksForDot(vec3 dot) { return this->scope->isDotInside(dot); }
  std::vector<vec3> getPoints() { return this->points; }

  /*!
  Points setter. Use this method to change basis points to manipulate target
  geometry.
  \param[in] ps - vector describing new basis points in 3-dimensional space.
  */
  void setPoints(std::vector<vec3> ps) { this->points = ps; }
  ~Basis() { delete this->scope; }
};
} // namespace param
