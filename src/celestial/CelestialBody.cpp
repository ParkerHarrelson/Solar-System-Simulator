
#include <celestial/CelestialBody.h>
#include <iostream>

using namespace SolarSystem;

void CelestialBody::initializeGraphics(Utilities::GeometryManager& geomManager) {
    Utilities::GeometryManager::GeometryData geomData = geomManager.createSphereGeometry(radius, longitudeSegments, latitudeSegments);
    this->geometryID = geomData.VAO;
    this->numIndices = geomData.indicesCount;
}

void CelestialBody::draw(GLuint shaderProgram) {
    Utilities::GeometryManager::GeometryData geomData = Utilities::GeometryManager::getGeometryData(this->geometryID);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(currentPosition.getX(), currentPosition.getY(), currentPosition.getZ()));
    std::printf("Position: (%d, %d, %d)\n", currentPosition.getX(), currentPosition.getY(), currentPosition.getZ());
    model = glm::scale(model, glm::vec3(radius, radius, radius));

    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(geomData.VAO);
    glDrawElements(GL_TRIANGLES, geomData.indicesCount, GL_UNSIGNED_INT, 0);
}
