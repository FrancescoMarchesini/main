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

#define LOG_TEXT_INFO       "[LOG_TEXT] [INFO]   "
#define LOG_TEXT_ERRORE     "[LOG_TEXT] [ERRORE] "


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

    /**
     * @brief drawTexture disegna la texture a partire dai dati caricati
     * @param vertices  vettore con le cordinate delle singole lettere
     * @param uv_buffer vettore con le cordinate UV delle sinole lettere
     * @return
     */
    bool drawTexture(const std::vector<glm::vec2> & vertices, const std::vector<glm::vec2> & uv_buffer);

    //varibili della classe
    unsigned int textureID;       //id della texture
    unsigned int vertexBufferID;  //vbo nel quale inserire la texture
    unsigned int UVBufferID;      //uv buffer
    Shader* shader;               //shader
    unsigned int Uniform2DID;       //settaggio dello shader
};

#endif
