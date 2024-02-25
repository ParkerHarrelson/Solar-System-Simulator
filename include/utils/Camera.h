#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Utilities {
    class Camera {
    public:
        float radius; // Distance from the focus point
        float theta;  // Angle from the z-axis in radians
        float phi;    // Angle from the x-axis in the xy-plane in radians
        glm::vec3 focusPoint;
        glm::vec3 up;

        Camera(float radius, float theta, float phi, glm::vec3 focusPoint)
            : radius(radius), theta(theta), phi(phi), focusPoint(focusPoint), up(glm::vec3(0.0f, 1.0f, 0.0f)) {}

        glm::mat4 GetViewMatrix() {
            // Calculate the camera's position using spherical coordinates
            glm::vec3 position;
            position.x = radius * sin(theta) * cos(phi) + focusPoint.x;
            position.y = radius * cos(theta) + focusPoint.y;
            position.z = radius * sin(theta) * sin(phi) + focusPoint.z;

            // Calculate the view matrix
            return glm::lookAt(position, focusPoint, up);
        }

        void Rotate(float dTheta, float dPhi) {
            theta += dTheta;
            phi += dPhi;
        }

        void Zoom(float dRadius) {
            radius += dRadius;
        }
    };
}

#endif 

