#ifndef _APP_H_
#define _APP_H_
#include "glxDisplay.h"

#define LOG_APP_INFO         "[APP] [INFO] "
#define LOG_APP_ERROR        "[APP] [ERRORE] "

class App : public glxDisplay
{
public:

        static App* init();

        virtual ~App();

        bool setup();

        void loop();

protected:

        App();
};

#endif
