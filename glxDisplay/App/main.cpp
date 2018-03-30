#include "App.h"

int main(int argv, char*argc[])
{
    App app;
    glxDisplay *display = &app;
    display->draw(app);

    return 0;
}
