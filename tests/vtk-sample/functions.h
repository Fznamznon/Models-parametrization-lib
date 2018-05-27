#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkUnstructuredGridGeometryFilter.h>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <param.hpp>

using namespace param;
using namespace std;

vec3 lvAVG = {-0.06723282854999998, 0.06897249222500001, 0.055131804300000004};

bool readBasisFromObj(const char *path, std::vector<Basis> &out) {

  Assimp::Importer importer;

  const aiScene *scene = importer.ReadFile(
      path, 0 /*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
  if (!scene) {
    fprintf(stderr, importer.GetErrorString());
    getchar();
    return false;
  }
  const aiMesh *mesh = scene->mMeshes[0];

  std::vector<vec3> vertices;
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    aiVector3D pos = mesh->mVertices[i];
    vertices.push_back(vec3(pos.x * 10, pos.y * 10, pos.z * 10));
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    std::vector<vec3> points;
    size_t ind = mesh->mFaces[i].mIndices[0];
    points.push_back(vertices[ind]);
    ind = mesh->mFaces[i].mIndices[1];
    points.push_back(vertices[ind]);
    ind = mesh->mFaces[i].mIndices[2];
    points.push_back(vertices[ind]);
    points.push_back(lvAVG);
    Scope *s = new TetrahedronScope(points);
    Basis b(points, s);
    out.push_back(b);
  }

  // The "scene" pointer will be deleted automatically by "importer"
  return true;
}

Model CreateModelFromVTKData(vtkSmartPointer<vtkUnstructuredGrid> data) {
  vector<double> vertices;

  vtkPoints* points = data->GetPoints();
  for (int i = 0; i < points->GetNumberOfPoints(); ++i) {
    double x[3];
    points->GetPoint(i, x);
    vertices.push_back(x[0]);
    vertices.push_back(x[1]);
    vertices.push_back(x[2]);
  }

  Model M(vertices);
  return M;

}

void UpdateVTKDataFromModel(vtkSmartPointer<vtkUnstructuredGrid> data, Model& m) {
  vector<double> vertices;

  vtkPoints* points = data->GetPoints();
  vector<double> vertex = m.getVertices();
  size_t changed = 0;
  for (int i = 0; i < vertex.size(); i += 3) {
    double old_x[3];
    double new_x[3];
    points->GetPoint(i / 3, old_x);
    double x[3] = {vertex[i], vertex[i + 1], vertex[i + 2]};
    points->SetPoint(i / 3, x);
    points->GetPoint(i / 3, new_x);
    if (old_x[0] != new_x[0] || old_x[1] != new_x[1] || old_x[2] != new_x[2]) {
      // printf("CHANGED \n");
      changed++;
    }
  }
  printf("CHANGED %d \n", changed);
}
