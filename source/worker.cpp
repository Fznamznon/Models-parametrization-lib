#include "worker.h"

void Worker::initialize() {

  std::vector<double> vtx = this->m.get_vertices_vec();

  for (size_t i = 0; i < vtx.size(); i += 3) {
    vec3 p = {vtx[i], vtx[i + 1], vtx[i + 2]};
    if (this->b.worksForDot(p)) {
      vec4 coords = Math::computeBCCoords(p, this->b.getPoints());
      this->b_coords.push_back(coords.x);
      this->b_coords.push_back(coords.y);
      this->b_coords.push_back(coords.z);
      this->b_coords.push_back(coords.a);
    }
  }
  this->initialized = true;
}

void Worker::transformModel() {
  if (!this->initialized)
    return;

  size_t bc_len = this->b_coords.size();
  std::vector<double> new_vertices;
  for (size_t i = 0; i < bc_len; i += 4) {
    vec4 c = {this->b_coords[i], this->b_coords[i + 1], this->b_coords[i + 2],
              this->b_coords[i + 3]};
    vec3 result_coords = Math::computeDecCoords(c, this->b.getPoints());
    new_vertices.push_back(result_coords.x);
    new_vertices.push_back(result_coords.y);
    new_vertices.push_back(result_coords.z);
  }
}
