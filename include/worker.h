#pragma once

#include "basis.h"
#include "model.h"
namespace param {
class Worker {
private:
  Model m;
  std::vector<Basis> b;
  std::vector<double> b_coords;
  std::vector<std::vector<size_t>> indices;
  bool initialized;

public:
  Worker() = delete;
  Worker(Model model, Basis basis) : m(model), initialized(false) {
    b.push_back(basis);
  }
  Worker(Model model, std::vector<Basis> basis)
      : m(model), b(basis), initialized(false) {}

  void initialize();
  void transformModel();
  void setBasis(std::vector<Basis> basis) { this->b = basis; }

  Model getModel() { return this->m; }

  ~Worker() = default;
};
} // namespace param
