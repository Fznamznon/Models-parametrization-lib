#include "common.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

using namespace std;

GLFWwindow *window;

int main(void) {
  // Initialise GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window =
      glfwCreateWindow(1024, 768, "Red triangle", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to open GLFW window. \n");
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  // Create and compile our GLSL program from the shaders
  GLuint programID = LoadShaders("SimpleVertexShader.vertexshader",
                                 "SimpleFragmentShader.fragmentshader");

  GLfloat g_vertex_buffer_data[] = {
      -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
  };

  vector<unsigned int> indices;
  vector<double> vertices;
  vector<double> normals;
  bool load = loadAssImp("heart.obj", indices, vertices, normals);
  if (!load)
    printf("FAIL");

  GLuint vertexbuffer;
  GLuint elementbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double), &vertices[0],
               GL_STATIC_DRAW);
  glGenBuffers(1, &elementbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, elementbuffer);
  glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &vertices[0], GL_STATIC_DRAW);
  do {
    // for (int i = 0; i < 9; ++i) {
    //   g_vertex_buffer_data[i] += 0.001;
    // }

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but
                             // must match the layout in the shader.
                          3, // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                          );

    // Draw the triangle !
    // glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1
    // triangle

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

    // Draw the triangles !
    glDrawElements(GL_TRIANGLES,      // mode
                   indices.size(),    // count
                   GL_UNSIGNED_INT, // type
                   (void *)0          // element array buffer offset
                   );

    glDisableVertexAttribArray(0);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);

  // Cleanup VBO
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteProgram(programID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}

