
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
    camera->Zoom(static_cast<float>(yoffset) * -20.0e11f);
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
        const double G = 6.67430e-11; // Gravitational constant in m^3 kg^-1 s^-2
        const double massSun = 1.989e30; // Mass of the Sun in kg
        const double massEarth = 5.972e24; // Mass of the Earth in kg
        const double distanceEarthSun = 1.496e6; // Average distance from Earth to Sun in meters
        const double radiusSun = 6.9634e8; // Radius of the Sun in meters
        const double radiusEarth = 6.371e6; // Radius of the Earth in meters

        // Assuming a circular orbit for simplicity:
        const double velocityMagnitudeEarth = std::sqrt(G * massSun / distanceEarthSun);
        Utilities::Vector velocityEarth(0, velocityMagnitudeEarth, 0); // Earth's velocity is tangential, so if the Sun is at the origin, then velocity is in the Y-axis.

        // Create Sun and Earth
        auto sun = std::make_unique<SolarSystem::Star>(
            massSun, // Mass of the Sun
            Utilities::Vector(0, 0, 0), // Sun's velocity (stationary in this simple model)
            radiusSun / 1e3, // Radius of the Sun in kilometers for drawing
            "Sun", // Name
            Utilities::Vector(0, 0, 0), // Sun's position at the origin
            0, // Angular velocity
            3.828e26, // Luminosity in Watts
            5778 // Surface temperature in Kelvin
        );

        auto earth = std::make_unique<SolarSystem::Planet>(
            massEarth, // Mass of the Earth
            velocityEarth, // Earth's initial velocity
            radiusEarth / 1e3, // Radius of the Earth in kilometers for drawing
            "Earth", // Name
            Utilities::Vector(distanceEarthSun, 0, 0), // Earth's initial position along the X-axis
            0 // Angular velocity
        );

        // Mars, for example
        const double massMars = 6.4171e23; // Mass of Mars in kg
        const double distanceMarsSun = 2.279e8; // Average distance from Mars to Sun in meters
        const double radiusMars = 3.3895e4; // Radius of Mars in meters
        const double velocityMagnitudeMars = std::sqrt(G * massSun / distanceMarsSun);
        Utilities::Vector velocityMars(0, velocityMagnitudeMars, 0);

        auto mars = std::make_unique<SolarSystem::Planet>(
            massMars,
            velocityMars,
            radiusMars / 1e3, // Radius in kilometers for drawing
            "Mars",
            Utilities::Vector(distanceMarsSun, 0, 0),
            0
        );

        // Venus, as another example
        const double massVenus = 4.8675e24; // Mass of Venus in kg
        const double distanceVenusSun = 1.082e8; // Average distance from Venus to Sun in meters
        const double radiusVenus = 6.0518e3; // Radius of Venus in meters
        const double velocityMagnitudeVenus = std::sqrt(G * massSun / distanceVenusSun);
        Utilities::Vector velocityVenus(0, velocityMagnitudeVenus, 0);

        auto venus = std::make_unique<SolarSystem::Planet>(
            massVenus,
            velocityVenus,
            radiusVenus / 1e3, // Radius in kilometers for drawing
            "Venus",
            Utilities::Vector(distanceVenusSun, 0, 0),
            0
        );

        // Add the celestial bodies to the solar system model
        solarSystem.addCelestialBody(std::move(sun));
        solarSystem.addCelestialBody(std::move(earth));
        solarSystem.addCelestialBody(std::move(mars));
        solarSystem.addCelestialBody(std::move(venus));

        for (auto& body : solarSystem.getCelestialBodies()) {
            body->initializeGraphics(geomManager);
        }

        Utilities::Camera camera(
            50000000000000.0f, // Distance from the origin
            glm::radians(85.0f), // Slightly decrease theta for initial view
            glm::radians(90.0f), // phi
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

            // Update the projection matrix with the new aspect ratio
            glm::mat4 projection = glm::perspective(
                glm::radians(45.0f), // Field of View Angle
                aspectRatio, // Aspect Ratio
                1e7f, // Near clipping plane (10 million km)
                3e20f // Far clipping plane (300 million km, ensuring that the whole distance is visible)
            );


            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) camera.Rotate(-0.0001f, 0.0f);
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) camera.Rotate(0.0001f, 0.0f);
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) camera.Rotate(0.0f, -0.0001f);
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) camera.Rotate(0.0f, 0.0001f);

            // Update view matrix
            glm::mat4 view = camera.GetViewMatrix();


            // Render your solar system
            solarSystem.calculateForceVectorsBasedOnTimestep(1.0f, 30.0f);
            solarSystem.calculateTotalForces();
            solarSystem.updateCelestialBodyPositionsAndVelocities(1.0f);
            solarSystem.render(view, projection); // Pass the view and projection matrices to the render function

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}