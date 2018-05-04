#include "model.h"

Model::Model(std::vector <double> vertices) {
  this->orig_vertices = vertices;
  this->act_vertices = vertices;
}

std::vector<double> Model::get_vertices_vec() { return this->act_vertices; }

double *Model::get_vertices() { return this->act_vertices.data(); }

void Model::set_vertices_vec(std::vector<double> vertices) {
  // TODO: check size
  this->act_vertices = vertices;
}

void Model::set_vertices(double *vertices, size_t size) {
  // TODO: check size
  this->act_vertices.clear();
  auto it = this->act_vertices.begin();
  this->act_vertices.insert(it, vertices, vertices + size);
}
