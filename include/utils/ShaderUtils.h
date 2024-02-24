
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
        out vec4 FragColor;

        void main() {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0); // white color
        }
    )glsl";


    const std::string vertexShaderSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
    )glsl";

}

#endif
