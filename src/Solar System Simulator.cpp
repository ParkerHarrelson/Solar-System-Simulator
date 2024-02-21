// Solar System Simulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const float PI = 3.1415927;

static void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(void) {
    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    if (mode != nullptr) {

        int screenWidth = mode->width;
        int screenHeight = mode->height;

        printf("Screen resolution: %d x %d\n", screenWidth, screenHeight);
        printf("Scaling down resolution from full screen...");
        
        int windowWidth = static_cast<int>(screenWidth * 0.75);
        int windowHeight = static_cast<int>(screenHeight * 0.75);

        window = glfwCreateWindow(windowWidth, windowHeight, "Solar System Simulator", NULL, NULL);
        if (!window) {
            glfwTerminate();
            std::cerr << "Failed to open GLFW window\n";
            return -1;
        }

        glfwSetWindowPos(window, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);

        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize window...\n";
            return -1;
        }

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}