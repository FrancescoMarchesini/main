#ifndef __GLX_DISPLAY__
#define __GLX_DISPLAY__

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define LOG_GLFW         "[GLFW ]"
class glxDisplay
{
public:
    /**
     * @brief create
     * @return
     */
    static glxDisplay* create();

    /**
     * @brief create
     * @return
     */
    //~glxDisplay();

    /**
     * @brief setTitle
     * @param str
     * funzione per settare il titolo della finestra
     */
    void setTitle(const char *str);
    void setSize(uint32_t widht, uint32_t height);

private:
    glxDisplay();

    /**
     * @brief initWindow
     * funzione per fare l'init della finestra glfw
     * @return true o false
     */
    bool initWindow();

    /**
     * @brief iniGL
     * inizializzazione di glew.h
     * @return true o false
     */
    bool iniGL();

    //oggetto finistra
    GLFWwindow* mWindow;

    //variabile per la finestra
    uint32_t mWidth;
    uint32_t mHeight;
};

#endif
