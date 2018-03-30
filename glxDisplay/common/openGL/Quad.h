#ifndef _QUAD_H_
#define _QUAD_H_

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "../common/openGL/shader.h"

#define LOG_QUAD_INFO  "[LOG_QUAD][INFO] "
#define LOG_QUAD_ERROR "[LOG_QUAD][ERROR] "
class Quad
{

public:

    ~Quad();

    /**
     * @brief create funzione per creare l'oggetto in modo statico
     * @return
     */
    static Quad* create();

    /**
     * @brief draw disegna l'oggetto
     */
    void draw();

    /**
     * @brief shader init della GLtexture
     */
    bool initTexture(const char* paths);

    /**
     * @brief cleanQuad pulisci texture e shader se non servono
     */
    void cleanQuad();

private:
    /**
     * @brief Quad costruttore
     */
    Quad();

    /**
     * @brief init isntanza dell'oggetto
     * @return
     */
    bool init();

    /**
     * @brief initBuffers
     * @return
     */
    bool initBuffers();

    Shader* shader;
    GLuint vbo;
    GLuint vao;
    GLuint ebo; //element buffer object ovvero un buffer per gli indici
    GLuint tex;

    //La seguente stuttura dati sarà condivisa sa tutte le istanze della
    //classe
    static const float vertices[32];
    static const GLint indici[6];
};
#endif
