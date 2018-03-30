#ifndef __APP_H_
#define __APP_H_

#include "../common/glfwDisplay/glxDisplay.h"
#include "../common/openGL/Quad.h"
#include "../common/openGL/openGLText2D.h"

#define LOG_APP_INFO          "[APP] [INFO] "
#define LOG_APP_ERROR         "[APP] [ERRORE] "
class App:public glxDisplay
{
public:
    /**
     * @brief ~App distruttore virtuale
     */
    virtual ~App();

    /**
     * @brief App costruttore
     */
    App(void);

    /**
     * @brief setup funzione nella quale fare il esetup del disegno
     */
    virtual void setup() override;

    /**
     * @brief loop funzione nella quale disegnare : main loop
     */
    virtual void loop() override;

    /**
     * @brief clean funzione per pulire gli oggetti di gl prima di chiudere
     */
    virtual void clean() override;

    //-------------------------------------------------------------------------
    //funzioni per ricevere input----------------------------------------------
    //-------------------------------------------------------------------------
    /**
     * @brief mouse_callback get mouse position insied window
     * @param xpos get xpos
     * @param ypos get ypos
     */
    virtual void mouse_callback(double xpos, double ypos) override;

    /**
     * @brief scroll_callback get scroll mouse
     * @param xoffset get xoffset [0-1] trackpad
     * @param yoffset get xoffset [0-1] mouse
     */
    virtual void scroll_callback(double xoffset, double yoffset) override;

    /**
     * @brief cursor_enter_call_back get if curson enter on window
     * @param entered in if yes or no
     */
    virtual void cursor_enter_call_back(int entered) override;

    /**
     * @brief mouse_button_callback get mouse botton press
     * @param button which botton left / right / center
     * @param action
     * @param mods  if pressed / released
     */
    virtual void mouse_button_callback(int button, int action, int mods);

    /**
     * @brief character_callback get the carater pressed
     * @param codepoint codepoint definition
     */
    virtual void character_callback(unsigned int codepoint);

    /**
     * @brief key_callback get key pressed
     * @param key wich key GLFW_KEY_X
     * @param scancode
     * @param action
     * @param mods pressed / release
     */
    virtual void key_callback(int key, int scancode, int action, int mods);

    /**
     * @brief drop_callback drop file inside window
     * @param count
     * @param paths
     */
    virtual void drop_callback(int count, const char** paths);

private:
    Quad* quad;
    openGLText* text;

};

#endif
