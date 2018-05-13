#pragma once

#include "basis.h"
#include "model.h"

/*!
\file
\brief Header file with Worker class.
*/

namespace param {
/*!
  \brief Class producing transformations of one Model.
  \author Fznamznon
  \section ex1 Example
  \snippet test.cpp example
*/
class Worker {
private:
  /// Controlled model
  Model m;
  /// Set of affine bases
  std::vector<Basis> b;
  /// Barycentric coordinates of model vertices
  std::vector<double> b_coords;
  /*!
  \brief Vector contains for each basis indices of vertices for which this basis
  acts.
  */
  std::vector<std::vector<size_t>> indices;
  /// Initialized = all barycentric coordinates are calculated.
  bool initialized;

public:
  Worker() = delete;
  /*!
  Contructor with one basis.
  */
  Worker(Model model, Basis basis) : m(model), initialized(false) {
    b.push_back(basis);
  }
  /*!
  Contructor with several bases.
  */
  Worker(Model model, std::vector<Basis> basis)
      : m(model), b(basis), initialized(false) {}

  /*!
  Initializes this worker. In other words computes barycentric coordinates.
  */
  void initialize();
  /*!
  Transforms model. If worker not initialized method initialize will be called.
  */
  void transformModel();
  /*!
  Sets new basis to use with old barycentric coordinates to transform model
  */
  void setBasis(std::vector<Basis> basis) { this->b = basis; }

  void setBasis(Basis basis) { this->b[0] = basis; }

  Model& getModel() { return this->m; }

  ~Worker() = default;
};
} // namespace param
