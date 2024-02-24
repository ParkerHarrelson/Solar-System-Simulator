#ifndef GEOMETRYMANAGER_H
#define GEOMETRYMANAGER_H

#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <GL/glew.h>

namespace Utilities {

    class GeometryManager {
    public:
        struct GeometryData {
            GLuint VAO;
            GLuint indicesCount;
        };

        static void initialize();
        static GeometryData createSphereGeometry(float radius, unsigned int longitudeBands, unsigned int latitudeBands);
        static void deleteGeometry(GLuint geometryID);
        static GeometryData getGeometryData(unsigned int geometryID);

    private:
        static GLuint generateSphereVAO(float radius, unsigned int longitudeBands, unsigned int latitudeBands, GLuint& indicesCount);
        static std::unordered_map<GLuint, GeometryData> geometries;
    };

}

#endif
