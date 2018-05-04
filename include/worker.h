#pragma once

#include "basis.h"
#include "model.h"

class Worker {
private:
  Model m;
  // TODO: array
  Basis b;
  std::vector<double> b_coords;
  bool initialized;

public:
  Worker() = delete;
  Worker(Model model, Basis basis) : m(model), b(basis), initialized(false) {}

  void initialize();
  void transformModel();

  ~Worker() = default;
};
