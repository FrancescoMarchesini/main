#include "shader.h"

Shader::Shader()
{
    ID = NULL;
    vertexCode = NULL;
    fragCode = NULL;
    geometryCode = NULL;
    vShaderFile = NULL;
    fShaderFile = NULL;
    gShaderFile = NULL;
}

void Shader::checkCompileErrors(GLuint shader, std::__cxx11::string type)
{
    GLuint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
           glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
           if(!success)
           {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                printf("&s ERRORE nella compilazione tipo : %s log : %s", LOG_SHADER, type, infoLog);
           }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("&s ERRORE nel link tipo : %s log : %s", LOG_SHADER, type, infoLog);

        }
    }
}

bool Shader::init(const char *vertexPath, const char *fragmentPath, const char *geomtryPath)
{
    printf("%s Provo a caricare gli shader\n", LOG_SHADER);
    //apro il file e nel durante vedo se ci sono errori
    //failbit : errori logici di input / ouput
    //badbit  : Read/write errori su input/uput operations
    vShaderFile.excetions(std::ifstream::failbit || std::ifstream::badbit);
    fShaderFile.excetions(std::ifstream::failbit || std::ifstream::badbit);
    gShaderFile.excetions(std::ifstream::failbit || std::ifstream::badbit);
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
        fshaderFile.close();
        //converto lo stream in stringa
        vertexCode = vShaderFile.str();
        fragmentCode = fShaderFile.str();
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
        printf("%s FALLITO A LEGGERE UNO DEI FILE ERRORE : %s\n", LOG_SHADER, e);
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    printf("%s Shader caricati correttamente\n", LOG_SHADER);

    printf("%s Linko gli Shader\n", LOG_SHADER);
    unsigned int vertex, fragment;
    int succes;
    char infoLog[512];

    printf("%s Iniziamo con il Vertex Shader :)\n", LOG_SHADER);
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    printf("%s Coninuiamo con il Fragment Shader\n", LOG_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(vertex, "FRAGMENT");

     printf("%s Finiamo con il geometry Shader se presente\n", LOG_SHADER);
     unsigned int geometry;
     if(geomtryPath != NULL)
     {
         const char* gshaderCode = geometry.c_str();
         geometry = glCreateShader(GL_GEOMETRY_SHADER);
         glShaderSource(geometry, 1, &gShaderCode, NULL);
         glCompileShader(geometry);
         checkCompileErrors(geometry, "GEOMETRY");
     }
     else
     {
         printf("%s No il geometry non è presetne :( \n", LOG_SHADER);
     }

     printf("%s Attiviamo gli shader \n", LOG_SHADER);
     ID = glCreateProgram();
     glAttachShader(ID, vertex);
     glAttachShader(ID, fragment);
     if(geomtryPath != nullptr)
         glAttachShader(ID, geometry);
     glLinkProgram(ID);
     checkCompileErrors(ID, "PROGRAM");

     printf("%s Pulisco gli shader che una volta linkati non sono piu necessari\n", LOG_SHADER);
     glDeleteShader(vertex);
     glDeleteShader(fragment);
     if(geomtryPath != nullptr)
        glDeleteShader(geometry);

     return true;
}

Shader* Shader::create(const char * vertexPath, const char* fragmentPath, const char* geomtryPath = nullptr)
{
    vShaderFile = vertexPath;
    fShaderFile = fragmentPath;
    if(geomtryPath != nullptr)
        gShaderFile = geomtryPath;

    Shader* sh = new Shader();

    if(!sh->init())
    {
        printf("%s FALLITO a creare l'instanza dell'oggetto shadere chiudo ed esco\n", LOG_SHADER);
        delete sh;
        return NULL;
    }
}

void use()
{
    glUseProgram(ID);
}

// utility uniform functions
void setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void setVec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

