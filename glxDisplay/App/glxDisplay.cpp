#include "glxDisplay.h"


glxDisplay::glxDisplay()
{
    mWindow = NULL;
    mWidth = 512;
    mHeight = 512;
    r = 0.f;
    g = 0.f;
    b = 0.4f;
    a = 0.f;
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
    //init glew
    glfwMakeContextCurrent(mWindow);
    //funzione call back per resize windows
    glfwSetFramebufferSizeCallback(mWindow, glxDisplay::framebuffer_size_callback);
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
    /**
     * @brief glfwSetInputMode listener sugli eventi
     * args 1 : finesrtra nella quale stare in ascoloto
     * args 2 : Cosa ascoltare in questo caso i tasti premuti
     * args 3 : alla premitura di un tasto il valore di ritorno è GLFW_PRESS
     */
    glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);

    //main loop per diseganre
    while(!glfwWindowShouldClose(mWindow))
    {
        //porcesso gli input
        processInput(mWindow);

        //pulisci lo schermo ad ogni loop
        glClearColor(r, g, b, a);
        glClear( GL_COLOR_BUFFER_BIT );

        //swap del buffer
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    glfwTerminate();
}

void glxDisplay::processInput(GLFWwindow *window)
{
    if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        printf("%s Chiuso la finestra \n", LOG_GLFW);
    }

    //restore window size
    if(glfwGetKey(mWindow, GLFW_KEY_U) == GLFW_PRESS)
    {
        printf("%s Tasto U : restore default size %d X %d \n", LOG_GLFW, mWidth, mHeight);
        glfwRestoreWindow(mWindow);
    }

    //massimizza la finistra
    if(glfwGetKey(mWindow, GLFW_KEY_I) == GLFW_PRESS)
    {
        printf("%s Tasto I : massimizzato finestra \n", LOG_GLFW);
        glfwMaximizeWindow(mWindow);
        //VEDERE COME OTTENERE LE NUOVE DIMESIONSIONI
    }

    //minimizza la finestra
    if(glfwGetKey(mWindow, GLFW_KEY_O) == GLFW_PRESS)
    {
        //ATTENZIONE SE LA FINISTRA VIENE MINIMIZZATA SCOMPARE E
        //NON SI PUO FAR NIENTE A PARTE CHE CHIUDERE IL TODOS
        printf("%s Tasto O : minimizza finistra \n", LOG_GLFW);
        glfwHideWindow(mWindow);
    }

    //mostra la finistra
    if(glfwGetKey(mWindow, GLFW_KEY_P) == GLFW_PRESS)
    {
        //DOVREBBE VISUALIZZARE LA FINISTRA QUANDO E MINIMIZZATA
        //MA NON ESSENDOCI PIU LA FINISTRA NON CE IL CONSTESTO NEL
        //QUALE SCHIACCIARE IL BOTTONE !!! :(
        printf("%s Tasto P : mostra finestra \n", LOG_GLFW);
        glfwShowWindow(mWindow);
    }

}
