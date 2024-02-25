
#ifndef SHADERUTILS_H
#define SHADERUTILS_H

#include <string>
#include <GL/glew.h>

namespace ShaderUtils {
    GLuint compileShader(GLenum type, const std::string& source);
    GLuint createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    //void checkCompileErrors(GLuint shader, std::string type);

    const std::string fragmentShaderSource = R"glsl(
        #version 330 core
        in vec3 vertexColor; // Receive color from vertex shader

        out vec4 FragColor;

        void main() {
            FragColor = vec4(vertexColor, 1.0); // Output the color received from the vertex shader
        }
    )glsl";


    const std::string vertexShaderSource = R"glsl(
       #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor; // Add layout for vertex color

        out vec3 vertexColor; // Pass color to the fragment shader

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            vertexColor = aColor; // Pass the vertex color through to the fragment shader
        }
    )glsl";

}

#endif