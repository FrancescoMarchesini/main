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

    /**
     * @brief framebuffer_size_callback funzione di callback per il resize del viewport, ovvero lo spazio di disegno
     * @param window oggetto finestra sul quale applicare il resize
     * @param width largezza viewport
     * @param height altezza view port
     */
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);


    void processInput(GLFWwindow* window);

    //oggetto finistra
    GLFWwindow* mWindow;

    //variabile per la finestra
    int mWidth;
    int mHeight;

    float r;
    float g;
    float b;
    float a;
};

#endif
