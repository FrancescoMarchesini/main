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
        printf("%sFalitto a creae L'app", LOG_APP_ERROR);
        return NULL;
    }
    app->create();
}
