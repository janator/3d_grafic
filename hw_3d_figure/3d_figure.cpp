// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow *window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>

int main(void) {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    return -1;
  }
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(1024, 768, "HW - 3d figure", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr,
            "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
  GLuint MatrixID = glGetUniformLocation(programID, "MVP");

  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
  // Camera matrix
  glm::mat4 View = glm::lookAt(
      glm::vec3(4, 4, 3), // Camera is at (4,3,-3), in World Space
      glm::vec3(0, 0, 0), // and looks at the origin
      glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
  );
  glm::mat4 Model = glm::mat4(1.0f);
  glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
  static const GLfloat g_vertex_buffer_data[] = {
      0.0f, 0.0f, 0.5f, //O
      0.0f, 1.0f, 0.0f, //B
      -0.22541f, 0.309f, 0.0f, //F
      0.0f, 0.0f, 0.5f, //O
      0.0f, 1.0f, 0.0f, //B
      0.22541f, 0.309f, 0.0f, //G
      0.0f, 0.0f, 0.5f, //O
      -0.951f, 0.309f, 0.0f, //A
      -0.22541f, 0.309f, 0.0f, //F
      0.0f, 0.0f, 0.5f, //O
      0.951f, 0.309f, 0.0f, //E
      0.22541f, 0.309f, 0.0f, //G
      0.0f, 0.0f, 0.5f, //O
      -0.951f, 0.309f, 0.0f, //A
      -0.36327f, -0.118f, 0.0f, //J
      0.0f, 0.0f, 0.5f, //O
      0.951f, 0.309f, 0.0f, //E
      0.36327f, -0.118f, 0.0f, //H
      0.0f, 0.0f, 0.5f, //O
      -0.5878f, -0.809f, 0.0f, //C
      -0.36327f, -0.118f, 0.0f, //J
      0.0f, 0.0f, 0.5f, //O
      0.5878f, -0.809f, 0.0f, //D
      0.36327f, -0.118f, 0.0f, //H
      0.0f, 0.0f, 0.5f, //O
      -0.5878f, -0.809f, 0.0f, //C
      0.0f, -0.38197f, 0.0f, //I
      0.0f, 0.0f, 0.5f, //O
      0.5878f, -0.809f, 0.0f, //D
      0.0f, -0.38197f, 0.0f, //I
      0.0f, 0.0f, -0.5f, //O
      0.0f, 1.0f, 0.0f, //B
      -0.22541f, 0.309f, 0.0f, //F
      0.0f, 0.0f, -0.5f, //O
      0.0f, 1.0f, 0.0f, //B
      0.22541f, 0.309f, 0.0f, //G
      0.0f, 0.0f, -0.5f, //O
      -0.951f, 0.309f, 0.0f, //A
      -0.22541f, 0.309f, 0.0f, //F
      0.0f, 0.0f, -0.5f, //O
      0.951f, 0.309f, 0.0f, //E
      0.22541f, 0.309f, 0.0f, //G
      0.0f, 0.0f, -0.5f, //O
      -0.951f, 0.309f, 0.0f, //A
      -0.36327f, -0.118f, 0.0f, //J
      0.0f, 0.0f, -0.5f, //O
      0.951f, 0.309f, 0.0f, //E
      0.36327f, -0.118f, 0.0f, //H
      0.0f, 0.0f, -0.5f, //O
      -0.5878f, -0.809f, 0.0f, //C
      -0.36327f, -0.118f, 0.0f, //J
      0.0f, 0.0f, -0.5f, //O
      0.5878f, -0.809f, 0.0f, //D
      0.36327f, -0.118f, 0.0f, //H
      0.0f, 0.0f, -0.5f, //O
      -0.5878f, -0.809f, 0.0f, //C
      0.0f, -0.38197f, 0.0f, //I
      0.0f, 0.0f, -0.5f, //O
      0.5878f, -0.809f, 0.0f, //D
      0.0f, -0.38197f, 0.0f, //I
  };

  static GLfloat g_color_buffer_data[20*3*3];
  float t = 0;
  for (int v = 0; v < 20*3 ; v++){
      float sinx = static_cast<float>(sin(t));
      float cosx = static_cast<float>(cos(t));
      g_color_buffer_data[3*v+0 ] = 1.0 - sinx;
      g_color_buffer_data[3*v+1 ] = abs(1.0 -sinx);
      g_color_buffer_data[3*v+2 ] = cosx;
    t += 2;
  }

  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  GLuint colorbuffer;
  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);
    float radius = 10.0f;
    float sinx = static_cast<float>(sin(glfwGetTime()) * radius);
    float cosx = static_cast<float>(cos(glfwGetTime()) * radius);
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View       = glm::lookAt(
        glm::vec3(0.5 * sinx, 0, 0.5 * cosx), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::mat4 Model      = glm::mat4(1.0f);
    glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,  (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0,  (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 20*3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
      glfwWindowShouldClose(window) == 0);

  // Cleanup VBO and shader
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteBuffers(1, &colorbuffer);
  glDeleteProgram(programID);
  glDeleteVertexArrays(1, &VertexArrayID);
  glfwTerminate();

  return 0;
}

