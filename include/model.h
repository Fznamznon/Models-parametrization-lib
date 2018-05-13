#pragma once

#include <cstddef>
#include <vector>

/*!
\file
\brief Header file with Model class.
*/

namespace param {
/*!
  \brief Class describing 3-dimensional model.
  \author Fznamznon
  \warning Defines only cloud of vertices.
*/
class Model {

private:
/// Actual verices
  std::vector<float> act_vertices;
/// Original verices
  std::vector<float> orig_vertices;

public:
  // Constructors
  Model() = default;
  Model(std::vector<float> vertices)
      : act_vertices(vertices), orig_vertices(vertices) {}

  // Vertex getter
  std::vector<float>& getVertices() { return this->act_vertices; }

  // Vertex setter
  void setVertices(std::vector<float> &vertices) {
    this->act_vertices = vertices;
  }

  ~Model() = default;
};
} // namespace param
