#include "shader.h"
#include <iostream>
Shader::Shader()
{
    ID = 0;
    vertexCode = "";
    fragmentCode = "";
    geometryCode = "";
   // vShaderFile = "";
   // fShaderFile = "";
   // gShaderFile = "";
}

void Shader::checkCompileErrors(GLuint shader, std::__cxx11::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
           glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
           if(!success)
           {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                printf("%s ERRORE nella compilazione tipo : %s log : %s", LOG_SHADER, type.c_str(), infoLog);
           }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("%s ERRORE nel link tipo : %s log : %s", LOG_SHADER, type.c_str(), infoLog);

        }
    }
}

bool Shader::init(const char *vertexPath, const char *fragmentPath, const char *geomtryPath)
{
    printf("%sProvo a caricare gli shader\n", LOG_SHADER);
    //apro il file e nel durante vedo se ci sono errori
    //failbit : errori logici di input / ouput
    //badbit  : Read/write errori su input/uput operations
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        //apro il file
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        //leggo il contenuto del buffer nello stream
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        //chiudo i files
        vShaderFile.close();
        fShaderFile.close();
        //converto lo stream in stringa
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        //if presente carico il geometry shader
        if(geomtryPath != NULL)
        {
            gShaderFile.open(geomtryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }

    }
    catch(std::ifstream::failure e)
    {
        printf("%sFALLITO A LEGGERE UNO DEI FILE ERRORE : %s\n", LOG_SHADER, e.what());
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    printf("%sShader File caricati correttamente\n", LOG_SHADER);

    printf("%sCompilo gli Shader:\n", LOG_SHADER);
    unsigned int vertex, fragment;
    int succes;
    char infoLog[512];

    printf("%s1 Vertex Shader\n", LOG_SHADER);
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    printf("%s2 Fragment Shader\n", LOG_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(vertex, "FRAGMENT");

     printf("%s3 geometry Shader?\n", LOG_SHADER);
     unsigned int geometry;
     if(geomtryPath != NULL)
     {
         const char* gShaderCode = geometryCode.c_str();
         geometry = glCreateShader(GL_GEOMETRY_SHADER);
         glShaderSource(geometry, 1, &gShaderCode, NULL);
         glCompileShader(geometry);
         checkCompileErrors(geometry, "GEOMETRY");
     }
     else
     {
         printf("%sNo non presente\n", LOG_SHADER);
     }

     printf("%sAttiviamo gli shader\n", LOG_SHADER);
     ID = glCreateProgram();
     glAttachShader(ID, vertex);
     glAttachShader(ID, fragment);
     if(geomtryPath != nullptr)
         glAttachShader(ID, geometry);
     glLinkProgram(ID);
     checkCompileErrors(ID, "PROGRAM");

     printf("%sCancello gli shader che una volta linkati non sono piu necessari\n", LOG_SHADER);


     glDeleteShader(vertex);
     glDeleteShader(fragment);
     if(geomtryPath != nullptr)
        glDeleteShader(geometry);

     return true;
}

Shader* Shader::create(const char * vertexPath, const char* fragmentPath, const char* geomtryPath)
{

    Shader* sh = new Shader();

    if(!sh->init(vertexPath, fragmentPath, geomtryPath))
    {
        printf("%s FALLITO a creare l'instanza dell'oggetto shadere chiudo ed esco\n", LOG_SHADER);
        delete sh;
        return NULL;
    }

    return sh;
}

void Shader::use()
{
    glUseProgram(ID);
}

// utility uniform functions
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::deleteShader()
{
    glDeleteProgram(ID);
}


