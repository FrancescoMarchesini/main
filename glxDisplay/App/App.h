#ifndef __APP_H_
#define __APP_H_

#include "glxDisplay.h"

#define LOG_APP_INFO          "[APP] [INFO] "
#define LOG_APP_ERROR         "[APP] [ERRORE] "
class App:public glxDisplay
{
public:
    /**
     * @brief ~App distruttore virtuale
     */
    virtual ~App();

    /**
     * @brief App costruttore
     */
    App(void);

    virtual void setup() override;
    virtual void loop() override;
    virtual void clean() override;
};

#endif
