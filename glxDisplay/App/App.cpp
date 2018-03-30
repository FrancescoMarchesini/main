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
