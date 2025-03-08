#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef INITH
#define INITH

bool init(GLFWwindow*& window, const char* name, int width, int height);

void display();

void reshape(GLFWwindow* window,int w,int h);

#endif
