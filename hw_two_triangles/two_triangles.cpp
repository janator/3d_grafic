// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>

int main(void) {
  if( !glfwInit() )
  {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    getchar();
    return -1;
  }
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow( 1024, 768, "HW - Two triangles", NULL, NULL);
  if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
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
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  GLuint programID_1 = LoadShaders( "VertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
  GLuint programID_2 = LoadShaders( "VertexShader.vertexshader", "ColorFragmentShader2.fragmentshader" );

  static const GLfloat g_vertex_buffer_data[] = {
      -0.4f, -0.8f, 0.0f,
      -0.4f, 0.8f, 0.0f,
      0.4f, 0.0f, 0.0f,
      0.0f, -0.8f, 0.0f,
      0.0f, 0.8f, 0.0f,
      0.8f, 0.0f, 0.0f
  };
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  do{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID_1);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,  (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3); // 12*3 indices starting at 0 -> 12 triangles
    glUseProgram(programID_2);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,  (void*)0);
    glDrawArrays(GL_TRIANGLES, 3, 3);
    glDisableVertexAttribArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
      glfwWindowShouldClose(window) == 0 );
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteProgram(programID_2);
  glDeleteProgram(programID_1);
  glfwTerminate();
  return 0;
}