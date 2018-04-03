#ifndef __GSTREAMER_H
#define __GSTREAMER_H

#include <gst/gst.h>
#include <string.h>
#include <sstream>

#define LOG_GST_INFO   "[LOG_GST] [INFO] "
#define LOG_GST_ERRROR "[LOG_GST] [ERROR] "

class GStreamer
{

    ~GStreamer();

    /**
     * @brief GStreamer construttore
     */
    GStreamer();

private:
    /**
     * @brief initGstream di gstream
     * @return
     */
    bool initGstream();

    /**
     * @brief init della suddetta classe
     * @return
     */
    bool init();

    /**
     * @brief buildLauchstr costruzione della stringa di lancio
     * @return
     */
    bool buildLauchstr();

    GstElement *mPipeline;
    GstBus *mBus;
    GstMessage *mMsg;

    std::string mLaunchString;
};
#endif

