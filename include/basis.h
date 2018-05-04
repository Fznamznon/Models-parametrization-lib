#pragma once

#include "math_functions.h"
#include <iostream>
#include <vector>

class Scope {
public:
  virtual bool isDotInside(vec3 dot) const = 0;
  virtual Scope *clone() const = 0;
};

class AllSpaceScope : public Scope {
public:
  AllSpaceScope() = default;
  AllSpaceScope(const AllSpaceScope &) = default;
  bool isDotInside(vec3 dot) const override { return true; }
  Scope *clone() const override { return new AllSpaceScope(*this); }
  ~AllSpaceScope() = default;
};

class TetrahedronScope : public Scope {
private:
  std::vector<vec3> vertices;

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

class Basis {
private:
  // 4 3-dimensional vectors and Scope
  std::vector<vec3> points;
  Scope *scope;

public:
  Basis() { this->scope = new AllSpaceScope(); }
  Basis(const Basis &other) {
    this->scope = other.scope->clone();
    this->points = other.points;
  }
  Basis(std::vector<vec3> ps) : points(ps) {}
  Basis(std::vector<vec3> ps, Scope *s) : points(ps), scope(s) {}
  bool worksForDot(vec3 dot) { return this->scope->isDotInside(dot); }
  std::vector<vec3> getPoints() { return this->points; }
  void setPoints(std::vector<vec3> ps) { this->points = ps; }
  ~Basis() { delete this->scope; }
};