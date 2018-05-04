#include <iostream>
#include <worker.h>

int main() {

  Basis b;
  std::vector<vec3> bp(4);
  std::vector<double> model_vertices(9);

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
  Model m(model_vertices);

  Worker w(m, b);
  w.initialize();
  w.transformModel();
  return 0;
}

