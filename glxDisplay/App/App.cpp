#include "App.h"


App::App(void):glxDisplay()
{

}

App::~App()
{

}

App* App::init()
{
    App* app = new App();
    if(!app)
    {
        printf("%sFalitto a creae L'app\n", LOG_APP_ERROR);
        return NULL;
    }
    app->create();
}

bool App::setup()
{
    printf("%sSetup virtuale\n", LOG_APP_INFO);
}

void App::loop()
{
    printf("%sDraw virtuale\n", LOG_APP_INFO);
}
