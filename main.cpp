#include "init.h"

#include <iostream>
#include <chrono>
#include <string>


int key, scancode, action, mod;

void keyboardCallback(GLFWwindow* window, int k, int s, int a, int m)
{
    key = k;
    scancode = s;
    action = a;
    mod = m;
}

int button, mouseAction, mouseMod;

void mouseCallback(GLFWwindow* window,int b,int a,int m)
{
    button = b;
    mouseAction = a;
    mouseMod = m;
}


auto profiler = std::chrono::high_resolution_clock::now();
std::string profilerStr;
bool printProfile = false;

void msCounter()
{
    if (printProfile)
    {
        system("cls");
        std::cout << profilerStr;
        profilerStr.clear();
        printProfile = false;
        profiler = std::chrono::high_resolution_clock::now();
    }
}


GLFWwindow* window = nullptr;

float x = 0.f, y = 0.f, z = -5.f;
float rotationX = 0.f, rotationY = 0.f;



void display()
{
    auto renderStart = std::chrono::high_resolution_clock::now();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glLoadIdentity(); 

    glTranslatef(x, y, z); 

    glRotatef(rotationX, 1.0f, 0.f, 0.f);

    glRotatef(rotationY, 0.f, 1.f, 0.f);

    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f); 
    glVertex3f(-1.0f, -1.0f, 0.0f); 

    
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(1.0f, -1.0f, 0.0f); 
    glVertex3f(0.0f, 0.0f, 2.0f); 

    
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(-1.0f, -1.0f, 0.0f); 
    glVertex3f(0.0f, 0.0f, 2.0f); 

   
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f); 
    glVertex3f(-1.0f, -1.0f, 0.0f); 
    glVertex3f(0.0f, 0.0f, 2.0f); 

    glEnd();

    glFlush(); 
    glfwSwapBuffers(window);

    auto renderEnd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(renderEnd - renderStart).count();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - profiler).count() >= 500)
        profilerStr = "Render process took " + std::to_string(duration) + "ms\n", printProfile = true;
}

void reshapee(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 200.0);  
    glMatrixMode(GL_MODELVIEW);
}

int width = 800, height = 600;

double xcursor, ycursor;

void events(GLFWwindow* window)
{
    auto eventStart = std::chrono::high_resolution_clock::now();
    glfwPollEvents();

    
    if (action == GLFW_PRESS)
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_W:
            z += 0.05f;
            break;
        case GLFW_KEY_S:
            z -= 0.05f;
            break;
        case GLFW_KEY_A:
            x += 0.05f;
            break;
        case GLFW_KEY_D:
            x -= 0.05f;
            break;
        case GLFW_KEY_SPACE:
            y -= 0.05f;
            rotationX += 0.5f;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            y += 0.05f;
            rotationX -= 0.5f;
            break;
        }


    
    if (mouseAction==GLFW_PRESS && button==GLFW_MOUSE_BUTTON_LEFT)
    {
        double xoffset, yoffset;
        glfwGetCursorPos(window, &xoffset, &yoffset);
        xoffset -= xcursor;
        yoffset -= ycursor;

        rotationX += yoffset * 0.2f;
        rotationY += xoffset * 0.2f;
        glfwGetCursorPos(window, &xcursor, &ycursor);
    }

	
    auto eventEnd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(eventEnd - eventStart).count();
    if (printProfile)
        profilerStr += "Event process took " + std::to_string(duration) + "ms\n";
}



int main()
{
   
    init(window, "Pyramid", width,height);


    reshape(window, width, height); 

    glfwSetKeyCallback(window, keyboardCallback);

    glfwSetMouseButtonCallback(window, mouseCallback);

    glfwSetFramebufferSizeCallback(window, reshape);

    glfwGetCursorPos(window, &xcursor, &ycursor);

    while (!glfwWindowShouldClose(window)) 
    {
        display();

        events(window);

        msCounter();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
