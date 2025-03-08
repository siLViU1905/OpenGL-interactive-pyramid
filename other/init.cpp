#include "init.h"

bool init(GLFWwindow*& window, const char* name, int width, int height)
{
    if (!glfwInit())
        return false;

    window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window)
        return false;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = true;

    GLenum err = glewInit();
    if (err != GLEW_OK)
        return false;


    glEnable(GL_DEPTH_TEST);

    return true;
}

void reshape(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 200.0); 
    glMatrixMode(GL_MODELVIEW);
}
