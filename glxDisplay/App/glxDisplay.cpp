#include "glxDisplay.h"


glxDisplay::glxDisplay()
{
    mWindow = NULL;
    mWidth = 512;
    mHeight = 512;
}

glxDisplay::~glxDisplay()
{
    glfwTerminate();
    mWindow = NULL;
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

    return true;
}

//ogni qualvolta che c'è un resize della windows questa funzione viene eseguita
void glxDisplay::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    //RICORDARSI CHE LE VARIBILE DELLE mWidth ED mHeight NON VENGONO AGGIORNATE
    //NON SO NEANCHE SE PUO' ESSERE UN PROBLEMA
    //mWidth = width;
    //mHeight = height;
    glViewport(0, 0, width, height );
    printf("%s Resize viewport avvenuto %d X %d \n", LOG_GLFW, width, height);
}

bool glxDisplay::initGL()
{
    //gestiamo i possibili errori prima di tutto
    glfwSetErrorCallback(error_callback);

    //init glew
    glfwMakeContextCurrent(mWindow);

    //init cursore costum
    GLFWcursor* cursor = initCostumCursor();
    glfwSetCursor(mWindow, cursor);

    //funzione call back per resize windows
    glfwSetFramebufferSizeCallback(mWindow, glxDisplay::framebuffer_size_callback);

    //funzione call_back per ottenere cordinate del mouse all'interno dello schermo
    glfwSetCursorPosCallback(mWindow, glxDisplay::mouse_callback);
    //funzione call_back per ottenere lo scrollo della rotella
    glfwSetScrollCallback(mWindow, glxDisplay::scroll_callback);
    //funzione callback per cursore dentro o fuori la finistra
    glfwSetCursorEnterCallback(mWindow, cursor_enter_call_back);
    //funzione callback per tasti mouse
    glfwSetMouseButtonCallback(mWindow, mouse_button_callback);

    //funzione callback per input tastiera
    glfwSetKeyCallback(mWindow, glxDisplay::key_callback);
    //funzione callback per ottenere lo stream input
    glfwSetCharCallback(mWindow, character_callback);

    //NOTARE LA DOPPIA CHIMATA DELLA FUNZIONE NON SO SE PUO DARE PROBLEMI
    //UNA CHIAMATA E PER IL MOUSE L'ALTRA PER LA TASTIRA
    /**
     * @brief glfwSetInputMode listener sugli eventi
     * args 1 : finesrtra nella quale stare in ascoloto
     * args 2 : Cosa ascoltare in questo il mouse
     * args 3 : come ascolotare
     */
    //glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    /**
     * @brief glfwSetInputMode listener sugli eventi
     * args 1 : finesrtra nella quale stare in ascoloto
     * args 2 : Cosa ascoltare in questo caso i tasti premuti
     * args 3 : alla premitura di un tasto il valore di ritorno è GLFW_PRESS
     */
    //glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);

    //glfwSetInputMode(mWindow, GLFW_STICKY_MOUSE_BUTTONS, 1);
    /////////////////////////////////////////////////////////////

    glewExperimental == true;
    if(glewInit() != GLEW_OK)
    {
        printf("%s ERRORE initializzazione glew \n", LOG_GLFW);
        return -1;
    }

    return true;
}

glxDisplay* glxDisplay::create()
{
    glxDisplay *vp = new glxDisplay();

    if( !vp )
           return NULL;

    if( !vp->initWindow())
    {
        printf("%s ERRORE fallito a creare finestra X11 \n", LOG_GLFW);
        delete vp;
        return NULL;
    }

    if( !vp->initGL())
    {
        printf("%s ERRORE fallito OpenGL \n", LOG_GLFW);
        delete vp;
        return NULL;
    }

    printf("%s TOP tutto è OK \n", LOG_GLFW);
    return vp;
}


void glxDisplay::draw()
{
    //main loop per diseganre
    while(!glfwWindowShouldClose(mWindow))
    {

        //pulisci lo schermo ad ogni loop
        glClearColor(0.f, 0.f, 0.4f, 0.f);
        glClear( GL_COLOR_BUFFER_BIT );

        //swap del buffer
        glfwSwapBuffers(mWindow);

        // sempre in ascolto degli eventi
        //glfwPollEvents();
        //aggiorna gli eventi nel mouse solo quando ci sono
        glfwWaitEvents();
    }
    glfwTerminate();
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
    printf("%s mouse : xpos = %f ypos = %f\n", LOG_GLFW, xpos, ypos);
}

void glxDisplay::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    printf("%s scroll : xpos = %0.3f ypos = %0.3f\n", LOG_GLFW, xoffset, yoffset);
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
}

void glxDisplay::character_callback(GLFWwindow* window, unsigned int codepoint)
{
    printf("%s tasto unicode : %d \n", LOG_GLFW, codepoint);
    static char result[6 + 1];

    int length = wctomb(result, codepoint);
    if (length == -1)
        length = 0;

    result[length] = '\0';
    printf("%s char string : %s \n", LOG_GLFW, result);
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
             printf("%s Tasto U : restore default size %d X %d \n", LOG_GLFW, w, h);
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
}
