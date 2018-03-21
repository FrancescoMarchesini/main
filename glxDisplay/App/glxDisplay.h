#ifndef __GLX_DISPLAY__
#define __GLX_DISPLAY__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
     * @brief initCostumCursor funzione nerd per cambiare l'apparenza del cursore
     * @return il cursore creato
     */
    GLFWcursor* initCostumCursor();

    ///NOTA CHE QUESTE FUNZIONI SONO STATICHE PERCHE QUANDO VENGONO CHIAMATE DALLE
    ///FUNZIONI CALL BACK DI GLFW SE NON STATICHE NON COMPILA E DA IL SEGUENTE ERRORE :
    ///"invalid use of non-static member function"
    /**
     * @brief framebuffer_size_callback funzione di callback per il resize del viewport, ovvero lo spazio di disegno
     * @param window oggetto finestra sul quale applicare il resize
     * @param width largezza viewport
     * @param height altezza view port
     */
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    /**
     * @brief mouse_callBack funzione che viene chiamata ogni volta che il mouse si muove ritornato la posizone del mouse
     * @param window oggetto sul quale chiamare opera la funzione
     * @param xpos  x posizone del mouse
     * @param ypos  y posizione del mouse
     */
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    /**
     * @brief scroll_callback funzione callback per ottenere l'ammontare di rotazione della rotella del mouse o del trackpad
     * @param window
     * @param xpos
     * @param ypos
     */
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    /**
     * @brief cursor_enter_call_back funzione che avvisa se il courso entra o esce dalla finistra
     * @param window
     * @param entered
     */
    static void cursor_enter_call_back(GLFWwindow* window, int entered);

    /**
     * @brief mouse_button_callback funzione che i tasti del mouse
     * @param button
     * @param action
     * @param mods
     */
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    /**
     * @brief character_callback funzione per ricevere i tasti premuti nella metdoologia stream inout continuo
     * @param window
     * @param codepoint il tast premuto è dato sotto forma unicode standart
     */
    static void character_callback(GLFWwindow* window, unsigned int codepoint);


    /**
     * @brief processInput funzione per mettersi in ascolto degli input da tastiera sulla finestra
     * @param window oggetto finestra
     */
    void processInput(GLFWwindow* window);

    //oggetto finistra
    GLFWwindow* mWindow;

    //variabile per la finestra
    int mWidth;
    int mHeight;
};

#endif
