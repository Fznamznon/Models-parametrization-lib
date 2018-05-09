#pragma once

#include <cstddef>
#include <vector>

class Model {

private:
  std::vector<float> act_vertices;
  std::vector<float> orig_vertices;

public:
  // Constructors
  Model() = default;
  Model(std::vector<float> vertices)
      : act_vertices(vertices), orig_vertices(vertices) {}

  // Vertex getters
  std::vector<float> getVertices() { return this->act_vertices; }

  // Vertex setters
  void setVertices(std::vector<float> vertices) {
    this->act_vertices = vertices;
  }

  ~Model() = default;
};
