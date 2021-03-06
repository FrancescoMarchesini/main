#ifndef __GLX_DISPLAY__
#define __GLX_DISPLAY__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#define LOG_GLFW               "[GLFW] [INFO] "
#define LOG_GLFW_ERROR         "[GLFW] [ERRORE] "
class glxDisplay
{
public:
    /**
     * @brief ~glxDisplay virtuale in modo da cancellare tutto dalla classe derivata
     */
    virtual ~glxDisplay();

    /**
     * @brief glxDisplay costruttore
     */
    glxDisplay();

    /**
     * @brief setup degli oggetti opengl per la classe padre
     */
    virtual void setup() {printf("%ssetup classe base\n", LOG_GLFW);}

    /**
     * @brief loop per diseganre gli oggetti nel setup all'interno del main loop GLFW
     */
    virtual void loop() {printf("%sloop classe base\n", LOG_GLFW);}

    /**
     * @brief loop per pulire openGL
     */
     virtual void clean(){printf("%sclean classe base\n", LOG_GLFW);}

    /**
     * @brief draw funzione con main loop per disegnare
     */
    void draw(glxDisplay &display);

    virtual void mouse_callback(double xpos, double ypos){}

    virtual void scroll_callback(double xoffset, double yoffset){}

    virtual void cursor_enter_call_back(int entered){}

    virtual void mouse_button_callback(int button, int action, int mods){}

    virtual void character_callback(unsigned int codepoint){}

    virtual void key_callback(int key, int scancode, int action, int mods){}

    virtual void drop_callback(int count, const char** paths){}

protected:

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

private:

    /**
     * @brief error_callback funzione per maneggiare gli errori, spero di no
     * @param error
     * @param description
     */
    static void error_callback(int error, const char* description);

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
     * @brief key_callback funzione che notifica quando un tasto è premuto rilasciato ripetuto
     * @param window finestra nella quale si opera
     * @param key   GLFW_KEY premuta
     * @param scancode
     * @param action GLFW_PRESS, GLFW_REPEAT o GLFW_RELEASE
     * @param mods tasti modali GLFW_KEY_ALT etc...
     */
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /**
     * @brief drop_callback callback per caricare file, path trascinandolo nella finestra
     * @param window
     * @param count
     * @param paths
     */
    static void drop_callback(GLFWwindow* window, int count, const char** paths);

protected:
    //oggetto finistra
    GLFWwindow* mWindow;

    //variabile per la finestra
    int mWidth;
    int mHeight;

};

#endif
