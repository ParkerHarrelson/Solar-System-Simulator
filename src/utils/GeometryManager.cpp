
#include <utils/GeometryManager.h>
#include <vector>
#include <utils/UtilitiesNamespace.h>
#include <glm/glm.hpp>

namespace Utilities {

    std::unordered_map<GLuint, GeometryManager::GeometryData> GeometryManager::geometries;

    GLuint GeometryManager::generateSphereVAO(float radius, unsigned int longitudeBands, unsigned int latitudeBands, GLuint& indicesCount) {
        // Example implementation to generate sphere vertices and indices
        // You would replace this with your actual sphere generation logic

        std::vector<float> vertices;
        std::vector<GLuint> indices;

        for (unsigned int lat = 0; lat <= latitudeBands; lat++) {
            float theta = lat * PI / latitudeBands;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            for (unsigned int lon = 0; lon <= longitudeBands; lon++) {
                float phi = lon * 2 * PI / longitudeBands;
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);

                float x = cosPhi * sinTheta;
                float y = cosTheta;
                float z = sinPhi * sinTheta;

                vertices.push_back(radius * x);
                vertices.push_back(radius * y);
                vertices.push_back(radius * z);
            }
        }

        for (unsigned int lat = 0; lat < latitudeBands; lat++) {
            for (unsigned int lon = 0; lon < longitudeBands; lon++) {
                GLuint first = (lat * (longitudeBands + 1)) + lon;
                GLuint second = first + longitudeBands + 1;

                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }

        // Create and bind VAO
        GLuint VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Create VBO, upload vertex data
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // Create EBO, upload index data
        GLuint EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        // Setup vertex attributes (e.g., position)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind VAO
        glBindVertexArray(0);

        // Store indices count for drawing
        indicesCount = indices.size();

        // Return VAO
        return VAO;
    }

    GeometryManager::GeometryData GeometryManager::createSphereGeometry(float radius, unsigned int longitudeBands, unsigned int latitudeBands) {
        GLuint indicesCount;
        GLuint sphereVAO = generateSphereVAO(radius, longitudeBands, latitudeBands, indicesCount);
        // Store VAO and indices count
        GeometryData geomData = { sphereVAO, indicesCount };
        geometries[sphereVAO] = geomData; // Adjust how you store this based on your storage strategy
        return geomData;
    }

    // Assuming GeometryData struct and geometries map are defined within GeometryManager

    Utilities::GeometryManager::GeometryData Utilities::GeometryManager::getGeometryData(unsigned int geometryID) {
        auto it = geometries.find(geometryID);
        if (it != geometries.end()) {
            return it->second;
        }
        // Handle the case where the geometryID is not found. This could be returning a default GeometryData, or throwing an exception.
        throw std::runtime_error("Geometry ID not found.");
    }

    void GeometryManager::deleteGeometry(GLuint geometryID) {
        auto it = geometries.find(geometryID);
        if (it != geometries.end()) {
            // Delete the VAO, VBO, and EBO associated with this geometry
            glDeleteVertexArrays(1, &it->second.VAO);
            // Assuming VBO and EBO IDs are stored or can be retrieved, delete them too
            // glDeleteBuffers(1, &VBO);
            // glDeleteBuffers(1, &EBO);

            geometries.erase(it); // Remove the geometry from the map
        }
    }

    void GeometryManager::initialize() {
        // Initialize any necessary OpenGL state or manager-specific resources here
        // For example:
        glEnable(GL_DEPTH_TEST);
    }

}
