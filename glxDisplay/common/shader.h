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

        /**
         * @brief use funzione per utilizzare gli shader caricati da dichiare prima del draw dell'oggeto
         */
        void use();

        //Semplici warp delle funzioni di utility di openGl per settare i parametri degli shader
        //mancano tutti i get value....
        void setBool(std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec2(const std::string &name, float x, float y) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w);
        void setMat2(const std::string &name, const glm::mat2 &mat) const;
        void setMat3(const std::string &name, const glm::mat3 &mat) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;

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
