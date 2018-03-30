#include "App.h"

App::~App()
{
    printf("%sDistrutto classe figlio\n", LOG_APP_INFO);
}

App::App(void):glxDisplay()
{

}

void App::setup()
{
    printf("%ssetup classe dall App\n", LOG_APP_INFO);
}

void App::loop()
{
    printf("%sloop classe dall App\n", LOG_APP_INFO);
}

void App::clean()
{
    printf("%sclean classe App\n", LOG_APP_INFO);
}

//--------------------------------------------------------------
//funzioni virtuali per riceve gli input : mouse / tastiera
//--------------------------------------------------------------
void App::mouse_callback(double xpos, double ypos)
{
    printf("%s mouse : xpos = %f ypos = %f\n", LOG_APP_INFO, xpos, ypos);
}

void App::scroll_callback(double xoffset, double yoffset)
{
    printf("%s scroll : xpos = %0.3f ypos = %0.3f\n", LOG_APP_INFO, xoffset, yoffset);
}

void App::cursor_enter_call_back(int entered)
{

}

void App::mouse_button_callback(int button, int action, int mods)
{

}

void App::character_callback(unsigned int codepoint)
{

    static char result[6 + 1];

    int length = wctomb(result, codepoint);
    if (length == -1)
        length = 0;

    result[length] = '\0';

    printf("%s char string : %s \n", LOG_APP_INFO, result);
}

void App::key_callback(int key, int scancode, int action, int mods)
{
    //nella funzione base sono gia implementati i seguenti input:
    // ESC quidi APP
    // F10 restore defualt size windows
    // F11 full screen
    // F12 iconizza finistra
}

void App::drop_callback(int count, const char **paths)
{
    int i;
        for (i = 0;  i < count;  i++)
        {
          printf("%s Caricato file %s\n", LOG_APP_INFO, paths[i]);
          //quad->initTexture(paths[i]);
        };
}
