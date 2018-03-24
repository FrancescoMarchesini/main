#include "glxDisplay.h"
#include <iostream>
#include "loadImage.h"

#include <GL/glew.h>

#include <GLFW/glfw3.h>

int main(int argv, char*argc[])
{
    GLuint image = loadDDS("Holstein.DDS");
    glxDisplay* win = glxDisplay::create();
    win->draw();
    delete win;
    return 0;
}
