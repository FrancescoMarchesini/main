#include "glxDisplay.h"
#include <iostream>

int main(int argv, char*argc[])
{
    std::cout<<"bella li"<<std::endl;
    glxDisplay* win = glxDisplay::create();
    return 0;
}
