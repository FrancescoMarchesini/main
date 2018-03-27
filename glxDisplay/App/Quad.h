#ifndef _QUAD_H_
#define _QUAD_H_

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "../common/shader.h"

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

    Shader* shader;
    GLuint vbo;
    GLuint vao;
    //La seguente stuttura dati sarà condivisa sa tutte le istanze della
    //classe
    static const float vertices[9];
};
#endif
