#include "glxDisplay.h"
#include <iostream>

int main(int argv, char*argc[])
{

    glxDisplay* win = glxDisplay::create();
    win->draw();
    delete win;
    return 0;
}
