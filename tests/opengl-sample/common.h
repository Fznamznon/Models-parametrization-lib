#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <string.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <worker.h>

const double START = 0.0;
const double STOP = 1.0;

vec3 lvAVG = {-0.06723282854999998, 0.06897249222500001, 0.055131804300000004};

bool loadAssImp(const char *path, std::vector<unsigned int> &indices,
                std::vector<float> &vertices,
                std::vector<float> &normals) {

  Assimp::Importer importer;

  const aiScene *scene = importer.ReadFile(
      path, 0 /*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
  if (!scene) {
    fprintf(stderr, importer.GetErrorString());
    getchar();
    return false;
  }
  const aiMesh *mesh =
      scene->mMeshes[0]; // In this simple example code we always use the 1rst
                         // mesh (in OBJ files there is often only one anyway)

  // Fill vertices positions
  vertices.reserve(mesh->mNumVertices);
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    aiVector3D pos = mesh->mVertices[i];
    vertices.push_back(pos.x);
    vertices.push_back(pos.y);
    vertices.push_back(pos.z);
  }

  // Fill vertices normals
  normals.reserve(mesh->mNumVertices);
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    aiVector3D n = mesh->mNormals[i];
    normals.push_back(n.x);
    normals.push_back(n.y);
    normals.push_back(n.z);
  }

  // Fill face indices
  indices.reserve(3 * mesh->mNumFaces);
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    // Assume the model has only triangles.
    indices.push_back(mesh->mFaces[i].mIndices[0]);
    indices.push_back(mesh->mFaces[i].mIndices[1]);
    indices.push_back(mesh->mFaces[i].mIndices[2]);
  }

  // The "scene" pointer will be deleted automatically by "importer"
  return true;
}

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
    vertices.push_back(vec3(pos.x, pos.y, pos.z));
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

void systole(double start, double stop, double cur,
             std::vector<Basis> startBasis, std::vector<Basis> endBasis,
             std::vector<Basis> &result) {
  for (size_t j = 0; j < startBasis.size(); ++j) {
    std::vector<vec3> spoints = startBasis[j].getPoints();
    std::vector<vec3> epoints = endBasis[j].getPoints();
    std::vector<vec3> respoints(epoints.size());
    for (size_t i = 0; i < epoints.size(); ++i) {
      double hx = (epoints[i].x - spoints[i].x) / (stop - start);
      double hy = (epoints[i].y - spoints[i].y) / (stop - start);
      double hz = (epoints[i].z - spoints[i].z) / (stop - start);

      respoints[i].x = spoints[i].x + (cur - start) * hx;
      respoints[i].y = spoints[i].y + (cur - start) * hy;
      respoints[i].z = spoints[i].z + (cur - start) * hz;
    }
    result[j].setPoints(respoints);
  }
}

void diastole(double start, double stop, double cur,
              std::vector<Basis> startBasis, std::vector<Basis> endBasis,
              std::vector<Basis> &result) {
  for (size_t j = 0; j < startBasis.size(); ++j) {
    std::vector<vec3> spoints = startBasis[j].getPoints();
    std::vector<vec3> epoints = endBasis[j].getPoints();
    std::vector<vec3> respoints(epoints.size());
    for (size_t i = 0; i < epoints.size(); ++i) {
      double hx = (epoints[i].x - spoints[i].x) / (stop - start);
      double hy = (epoints[i].y - spoints[i].y) / (stop - start);
      double hz = (epoints[i].z - spoints[i].z) / (stop - start);

      respoints[i].x = epoints[i].x - (cur - stop) * hx;
      respoints[i].y = epoints[i].y - (cur - stop) * hy;
      respoints[i].z = epoints[i].z - (cur - stop) * hz;
    }
    result[j].setPoints(respoints);
  }
}

void heartCycle(double cur, std::vector<Basis> startBasis,
              std::vector<Basis> endBasis, std::vector<Basis> &result) {
  static int direction = 1;
  if (fabs(cur - START) <= 0.0001) {
    direction = 1;
  }
  if (fabs(cur - STOP) <= 0.0001) {
    direction = -1;
  }
  if (direction > 0) {
    systole(START, STOP, cur, startBasis, endBasis, result);
  } else {
    diastole(START, STOP, cur, startBasis, endBasis, result);
  }
}

GLuint LoadShaders(const char *vertex_file_path,
                   const char *fragment_file_path) {

  // Create the shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // Read the Vertex Shader code from the file
  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if (VertexShaderStream.is_open()) {
    std::stringstream sstr;
    sstr << VertexShaderStream.rdbuf();
    VertexShaderCode = sstr.str();
    VertexShaderStream.close();
  } else {
    printf("Impossible to open %s.\n ",
           vertex_file_path);
    getchar();
    return 0;
  }

  // Read the Fragment Shader code from the file
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if (FragmentShaderStream.is_open()) {
    std::stringstream sstr;
    sstr << FragmentShaderStream.rdbuf();
    FragmentShaderCode = sstr.str();
    FragmentShaderStream.close();
  }

  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Compile Vertex Shader
  printf("Compiling shader : %s\n", vertex_file_path);
  char const *VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL,
                       &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }

  // Compile Fragment Shader
  printf("Compiling shader : %s\n", fragment_file_path);
  char const *FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL,
                       &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }

  // Link the program
  printf("Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL,
                        &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }

  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}
