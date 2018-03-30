#include "glxDisplay.h"

glxDisplay::glxDisplay()
{
    mWindow = NULL;
    mWidth = 512;
    mHeight = 512;

    if( !initWindow())
    {
        printf("%s ERRORE fallito a creare finestra X11 \n", LOG_GLFW);

    }

    if( !initGL())
    {
        printf("%s ERRORE fallito OpenGL \n", LOG_GLFW);
    }

    printf("%s TOP tutto è OK \n", LOG_GLFW);
}

glxDisplay::~glxDisplay()
{
    glfwTerminate();
    mWindow = NULL;
    printf("%sDistrutto classe Padre\n", LOG_GLFW);
}

bool glxDisplay::initWindow()
{
    if( !glfwInit() )
    {
        printf("%s ERRORE initializzazione glfw fallita \n", LOG_GLFW);
        return -1;
    }

    //parametri per la creazione della finistra e i vari supporti
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //apro la finestra e creao il contesto openGL
    mWindow = glfwCreateWindow(mWidth, mHeight, "First", NULL, NULL);
    if(mWindow == NULL)
    {
        printf("%s ERRORE initializzazione finestra fallita \n", LOG_GLFW);
        glfwTerminate();
        return -1;
    }

    //funzione per le callback void
    glfwSetWindowUserPointer(mWindow, this);
    return true;
}

bool glxDisplay::initGL()
{
    //gestiamo i possibili errori prima di tutto
    glfwSetErrorCallback(error_callback);

    //init glew
    glfwMakeContextCurrent(mWindow);
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        printf("%s ERRORE initializzazione glew \n", LOG_GLFW);
        glfwTerminate();
        return -1;
    }
    printf("%s Inizializzato GLFW e GLEW\n", LOG_GLFW);

    //init cursore costum
    GLFWcursor* cursor = initCostumCursor();
    glfwSetCursor(mWindow, cursor);

    //funzione call back per resize windows
    glfwSetFramebufferSizeCallback(mWindow, glxDisplay::framebuffer_size_callback);

    glfwSetCursorPosCallback(mWindow, mouse_callback);              //get mouse pos
    glfwSetScrollCallback(mWindow, scroll_callback);                //get mouse scroll
    glfwSetCursorEnterCallback(mWindow, cursor_enter_call_back);    //get coursore insied/outside windows
    glfwSetMouseButtonCallback(mWindow, mouse_button_callback);     //get mouse botton
    glfwSetKeyCallback(mWindow, key_callback);                      //get key pressey
    glfwSetCharCallback(mWindow, character_callback);               //get charater pressed
    glfwSetDropCallback(mWindow, drop_callback);                    //drop file insied windows

    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(mWindow, GLFW_STICKY_MOUSE_BUTTONS, 1);
    printf("%s Initializzato Tutte le funzione CallBack per Input e Varie\n", LOG_GLFW);

    // Dark blue background
    //glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    printf("%s Attivato le varie funzioni di openGL\n", LOG_GLFW);

    return true;
}

void glxDisplay::draw(glxDisplay &display)
{
    //////////////////////////////////////////////////////////////
    display.setup();
    /////////////////////////////////////////////////////////////

    while(!glfwWindowShouldClose(mWindow))
    {

        glClearColor(0.f, 0.f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //////////////////////////////////////////////////////////////
        display.loop();
        //////////////////////////////////////////////////////////////

        glfwSwapBuffers(mWindow);
        glfwWaitEvents();
    }

    //////////////////////////////////////////////////////////////
    display.clean();
    //////////////////////////////////////////////////////////////

    glfwTerminate();
}


//ogni qualvolta che c'è un resize della windows questa funzione viene eseguita
void glxDisplay::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    //RICORDARSI CHE LE VARIBILE DELLE mWidth ED mHeight NON VENGONO AGGIORNATE
    //NON SO NEANCHE SE PUO' ESSERE UN PROBLEMA
    //mWidth = width;
    //mHeight = height;
    //La funzione glViewport trasforma le Normalize Device Cordinate nelle cordinate screen-space
    //questo poi passate al fragment shader
    glViewport(0, 0, width, height );
    printf("%s Resize viewport avvenuto %d X %d \n", LOG_GLFW, width, height);
}

void glxDisplay::error_callback(int error, const char *description)
{
    printf("%s ORRORE : %s \n", LOG_GLFW, description);
}

GLFWcursor *glxDisplay::initCostumCursor()
{
    unsigned char pixels[16 * 16 * 4];
    memset(pixels, 0xff, sizeof(pixels));
    GLFWimage image;
    image.width = 16;
    image.height = 16;
    image.pixels = pixels;
    GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
    return cursor;
}

void glxDisplay::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    glxDisplay* obj =(glxDisplay*)glfwGetWindowUserPointer(window);
    obj->mouse_callback(xpos, ypos);
}

void glxDisplay::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    glxDisplay* obj =(glxDisplay*)glfwGetWindowUserPointer(window);
    obj->scroll_callback(xoffset, yoffset);
}

void glxDisplay::cursor_enter_call_back(GLFWwindow *window, int entered)
{

    if(entered)
    {
        printf("%s tu sei dentro \n", LOG_GLFW);
    }
    else
    {
        printf("%s tu sei fuori \n", LOG_GLFW);
    }

    glxDisplay* obj =(glxDisplay*)glfwGetWindowUserPointer(window);
    obj->cursor_enter_call_back(entered);
}

void glxDisplay::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(action != GLFW_PRESS)
        return;

    switch(button)
    {
        case GLFW_MOUSE_BUTTON_LEFT:
        {
             printf("%s Tasto sinistro mouse \n", LOG_GLFW);
             break;
        }
        case GLFW_MOUSE_BUTTON_MIDDLE:
        {
            printf("%s Tasto centrale mouse \n", LOG_GLFW);
            break;
        }
        case GLFW_MOUSE_BUTTON_RIGHT:
        {
            printf("%s Tasto destro mouse \n", LOG_GLFW);
            break;
        }
    }

    glxDisplay* obj =(glxDisplay*)glfwGetWindowUserPointer(window);
    obj->mouse_button_callback(button, action, mods);
}

void glxDisplay::character_callback(GLFWwindow* window, unsigned int codepoint)
{

    //funzione virtuale per scrivere codice qui dalla classe derviata
    glxDisplay* obj =(glxDisplay*)glfwGetWindowUserPointer(window);
    obj->character_callback(codepoint);
}

void glxDisplay::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    //fai l'azione solo quando il tasto è premuto
    if(action != GLFW_PRESS)
        return;

    switch(key)
    {
        case GLFW_KEY_ESCAPE:
        {
             glfwSetWindowShouldClose(window, true);
             printf("%s Chiuso la finestra \n", LOG_GLFW);
        }

        case GLFW_KEY_F10:
        {
             glfwRestoreWindow(window);
             int w, h = 0;
             glfwGetWindowSize(window, &w, &h);
             printf("%s Tasto F10 : restore default size %d X %d \n", LOG_GLFW, w, h);
             break;
        }

        case GLFW_KEY_F11:
        {
             glfwMaximizeWindow(window);
             int w, h = 0;
             glfwGetWindowSize(window, &w, &h);
             printf("%s F11 : massimizzato la finestra %d X %d \n", LOG_GLFW, w, h);
             break;
        }

        case GLFW_KEY_F12:
        {
             glfwIconifyWindow(window);
             printf("%s Tasto O : iconizzo la finistra \n", LOG_GLFW);
             break;
        }
    }

    //funzione virtuale per scrivere codice qui dalla classe derviata
    glxDisplay* obj =(glxDisplay*)glfwGetWindowUserPointer(window);
    obj->key_callback(key, scancode, action, mods);
}

void glxDisplay::drop_callback(GLFWwindow* window, int count, const char** paths)
{  
    glxDisplay* obj =(glxDisplay*)glfwGetWindowUserPointer(window);
    obj->drop_callback(count, paths);
}
