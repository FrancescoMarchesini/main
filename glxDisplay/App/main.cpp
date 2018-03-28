#include "App.h"
#include <iostream>

int main(int argv, char*argc[])
{

    App * my = App::init();
    if(!my->setup())
    {
        printf("[LOG_MAIN]ok tutte le tue funzioni gl sono ok");
    }

    my->loop();

    my->draw();

    delete my;

    return 0;
}
