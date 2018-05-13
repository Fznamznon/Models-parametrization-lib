#include <iostream>
#include <param.hpp>

int main() {

  param::Basis b;
  std::vector<param::Math::vec3> bp(4);
  std::vector<float> model_vertices(9);

  for (int i = 0; i < 4; ++i) {
    bp[i].x = i;
    bp[i].y = i;
    bp[i].z = i;
  }
  b.setPoints(bp);
  for (int i = 0; i < 9; i += 3) {
    model_vertices[i] = i;
    model_vertices[i + 1] = i;
    model_vertices[i + 2] = i;
  }
  param::Model m(model_vertices);
//! [example]
  param::Worker w(m, b);
  w.transformModel();
//! [example]
  return 0;
}

