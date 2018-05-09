#include "worker.h"

namespace param {

void Worker::initialize() {

  std::vector<float> vtx = this->m.getVertices();
  this->indices = std::vector<std::vector<size_t>>(b.size());
  this->b_coords = std::vector<double>(vtx.size() / 3 * 4);
  for (size_t i = 0; i < vtx.size(); i += 3) {
    vec3 p = {vtx[i], vtx[i + 1], vtx[i + 2]};
    for (size_t j = 0; j < b.size(); ++j) {
      if (this->b[j].worksForDot(p)) {
        size_t ind = i / 3;
        vec4 coords = Math::computeBCCoords(p, this->b[j].getPoints());
        this->b_coords[ind * 4] = coords.x;
        this->b_coords[ind * 4 + 1] = coords.y;
        this->b_coords[ind * 4 + 2] = coords.z;
        this->b_coords[ind * 4 + 3] = coords.a;
        this->indices[j].push_back(ind);
      }
    }
  }
  this->initialized = true;
}

void Worker::transformModel() {
  if (!this->initialized)
    initialize();

  std::vector<float> vertices = this->m.getVertices();
  for (size_t i = 0; i < this->indices.size(); ++i) {
    for (size_t j = 0; j < this->indices[i].size(); ++j) {
      size_t ind = this->indices[i][j];

      vec4 c = {this->b_coords[ind * 4], this->b_coords[ind * 4 + 1],
                this->b_coords[ind * 4 + 2], this->b_coords[ind * 4 + 3]};

      vec3 result_coords = Math::computeDecCoords(c, this->b[i].getPoints());

      vertices[ind * 3] = result_coords.x;
      vertices[ind * 3 + 1] = result_coords.y;
      vertices[ind * 3 + 2] = result_coords.z;
    }
  }
  this->m.setVertices(vertices);
}

} // namespace param
