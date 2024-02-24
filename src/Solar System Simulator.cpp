
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <celestial/CelestialBody.h>
#include <celestial/SolarSystemModel.h>
#include <celestial/Star.h>
#include <celestial/Planet.h>
#include <utils/Vector.h>
#include <utils/ShaderUtils.h>
#include <utils/GeometryManager.h>

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

        Utilities::GeometryManager geomManager;
        geomManager.initialize();

        GLuint shaderProgram = ShaderUtils::createShaderProgram(ShaderUtils::vertexShaderSource, ShaderUtils::fragmentShaderSource);
        SolarSystem::SolarSystemModel solarSystem;
        solarSystem.setShaderProgram(shaderProgram);

        // Create a star (e.g., the Sun) and a planet (e.g., Earth)
        auto sun = std::make_unique<SolarSystem::Star>(1.989e30, Utilities::Vector(0, 0, 0), 696340, "Sun", Utilities::Vector(0, 0, 0), 0, 3.828e26, 5778);
        auto earth = std::make_unique<SolarSystem::Planet>(5.972e24, Utilities::Vector(0, 29.78, 0), 6371, "Earth", Utilities::Vector(1, 0, 0), 0);

        // Add the celestial bodies to the solar system model
        solarSystem.addCelestialBody(std::move(sun));
        solarSystem.addCelestialBody(std::move(earth));

        for (auto& body : solarSystem.getCelestialBodies()) {
            body->initializeGraphics(geomManager);
        }

        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.1f, 0.1f, 0.3f, 1.0f); // Dark blue background
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Render your solar system
            solarSystem.render();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}