#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define LOG_SHADER "[LOG_SHADER] "
class Shader
{
    public:
        static Shader* create(const char * vertexPath, const char* fragmentPath, const char* geomtryPath = nullptr);
        void use();
        void setBool(std::string &name, bool value) const;

    private:
        Shader();
        bool init(const char * vertexPath, const char* fragmentPath, const char* geomtryPath = nullptr);
        void checkCompileErrors(GLuint shader, std::string type);

    //varibili della classe
    unsigned int ID;
    std::string vertexCode;
    std::string fragCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
};
#endif
