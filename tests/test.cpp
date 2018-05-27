#include <iostream>
#include <param.hpp>

int main() {

  param::Basis basis;
  param::Basis new_basis;
  std::vector<param::math::vec3> bp(4);
  std::vector<double> model_vertices(9);

  for (int i = 0; i < 4; ++i) {
    bp[i].x = i;
    bp[i].y = i;
    bp[i].z = i;
  }
  basis.setPoints(bp);
  for (int i = 0; i < 9; i += 3) {
    model_vertices[i] = i;
    model_vertices[i + 1] = i;
    model_vertices[i + 2] = i;
  }
  for (int i = 0; i < 4; ++i) {
    bp[i].x++;
    bp[i].y++;
    bp[i].z++;
  }
  new_basis.setPoints(bp);
  param::Model model(model_vertices);
//! [example]
  param::Worker w(model, basis);
  w.initialize();
  w.setBasis(new_basis);
  w.transformModel();
//! [example]
  return 0;
}

