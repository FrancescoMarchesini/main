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
     * @brief create funzione statica per creare l'instanza della classe
     * @return
     */
    static glxDisplay* create();

    ~glxDisplay();

    /**
     * @brief draw funzione con main loop per disegnare
     */
    void draw();

private:
    glxDisplay();

    /**
     * @brief initWindow init della finestra glfw
     * @return true o false
     */
    bool initWindow();

    /**
     * @brief iniGLinizializzazione init di glew.h
     * @return true o false
     */
    bool initGL();

    //oggetto finistra
    GLFWwindow* mWindow;

    //variabile per la finestra
    uint32_t mWidth;
    uint32_t mHeight;
};

#endif
