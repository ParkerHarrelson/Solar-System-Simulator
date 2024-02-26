
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
#include <utils/Camera.h>

static void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    auto camera = static_cast<Utilities::Camera*>(glfwGetWindowUserPointer(window));
    camera->Zoom(static_cast<float>(yoffset) * -2.0e2f);
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

        // Define the celestial bodies with small values for a simple simulation
        const float starRadius = 10.0f; // Star radius in km
        const float planetRadius = 5.0f; // Planet radius in km
        const float planetDistance = 600.0f; // Distance of the planet from the star in km

        // Star at the origin
        auto star = std::make_unique<SolarSystem::Star>(
            1000000000000.0f, // Small mass for the star in kg
            Utilities::Vector(0.0f, 0.0f, 0.0f), // Stationary star
            starRadius, // Radius in km
            "Star",
            Utilities::Vector(0.0f, 0.0f, 0.0f), // Star's position at the origin
            0.0f, // Angular velocity
            1.0f, // Luminosity in arbitrary units
            3000.0f // Surface temperature in Kelvin
        );

        auto planet = std::make_unique<SolarSystem::Planet>(
            500.0f, // Small mass for the planet in kg
            Utilities::Vector(0.003334f, 0.0f, 0.0f), // Orbital velocity in km/s for a stable orbit
            planetRadius, // Radius in km
            "Planet",
            Utilities::Vector(-600.0f, 0.0f, 0.0f), // Position near the star along the x-axis
            0.0f // Angular velocity
        );


        solarSystem.addCelestialBody(std::move(star));
        solarSystem.addCelestialBody(std::move(planet));


        for (auto& body : solarSystem.getCelestialBodies()) {
            body->initializeGraphics(geomManager);
        }

        Utilities::Camera camera(
            1000.0f, // Position the camera 100 km from the origin, which is far enough to see both bodies
            glm::radians(90.0f), // Theta, angle from the z-axis in radians, looking from a higher point
            glm::radians(0.0f), // Phi, angle from the x-axis in the xy-plane in radians, looking directly at the origin
            glm::vec3(0.0f, 0.0f, 0.0f) // focusPoint at the origin
        );


        glfwSetWindowUserPointer(window, &camera);

        glfwSetScrollCallback(window, scroll_callback);

        while (!glfwWindowShouldClose(window)) {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height); // Get the current window size
            float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Dark blue background
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Setup the projection matrix
            float nearPlane = 1.0f; // 1 km from the camera
            float farPlane = 10000.0f; // 100 km from the camera, enough to see both celestial bodies
            float fieldOfView = 45.0f; // Field of view in degrees

            glm::mat4 projection = glm::perspective(
                glm::radians(fieldOfView), // Convert field of view to radians
                aspectRatio, // Aspect ratio of the window
                nearPlane, // Near clipping plane
                farPlane // Far clipping plane
            );            

            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) camera.Rotate(-0.0001f, 0.0f);
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) camera.Rotate(0.0001f, 0.0f);
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) camera.Rotate(0.0f, -0.0001f);
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) camera.Rotate(0.0f, 0.0001f);

            // Update view matrix
            glm::mat4 view = camera.GetViewMatrix();

            // Render your solar system
            solarSystem.calculateForceVectorsBasedOnTimestep(10.0f, 30.0f);
            solarSystem.calculateTotalForces();
            solarSystem.updateCelestialBodyPositionsAndVelocities(10.0f);
            solarSystem.render(view, projection); // Pass the view and projection matrices to the render function

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}