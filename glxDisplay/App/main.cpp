#include "App.h"
#include "../common/Gstreamer/gstreamer.h"

int main(int argv, char*argc[])
{
    GStreamer cam;

    App app;
    glxDisplay *display = &app;
    display->draw(app);

    return 0;
}
