#pragma once

#include <vector>
#include <cstddef>

class Model {

private:
  std::vector<double> act_vertices;
  std::vector<double> orig_vertices;

public:
  // Constructors
  Model() = default;
  Model(std::vector<double> vertices);

  // Vertex getters
  std::vector<double> get_vertices_vec();
  double *get_vertices();

  // Vertex setters
  void set_vertices_vec(std::vector<double> vertices);
  void set_vertices(double *vertices, size_t size);

  ~Model() = default;
};
