#ifndef _OPENGL_TEXT_2D_
#define _OPENGL_TEXT_2D_

#include <vector>
#include <cstring>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "common/shader.h"
#include "common/loadImageOnTexture.h"

class openGLText
{
public:

    /**
     * Distruttore un giorno capiremo come usarlo
     */
    ~openGLText();

     /**
     * @brief create funzione per crere l'instanza della classe
     * @param texturePath il path alla texture DDS
     * @return il puntarore all'instanza della classe
     */
    static openGLText* create(const char* texturePath);

    /**
     * @brief printText funzione per fare il render del testo
     * @param text il testo da disegnare
     * @param x la coordinate dell'ascissa
     * @param y la coordinata dell'ordinata
     * @param size la grandezza del testo, viva le mipMap
     */
    void printText(const char* text, int x, int y, int size);

    /**
     * @brief cleanupText2D funzione per pulire le variabili non piu utilizzate
     */
    void cleanupText2D();

private:
    /**
     * @brief openGLText costruttore della classe
     */
    openGLText();

    /**
     * @brief init della classe
     * @param texturePath path alla texture dei fonti, non mi piace
     * @return
     */
    bool init(const char* texturePath);

    //varibili della classe
    unsigned int Text2DTextureID;       //id della texture
    unsigned int Text2DVertexBufferID;  //vbo nel quale inserire la texture
    unsigned int Text2DUVBufferID;      //uv buffer
    unsigned int Text2DShaderID;        //shader
    unsigned int Text2DUniformID;       //settaggio dello shader
};

#endif
