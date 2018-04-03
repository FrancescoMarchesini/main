#include <../common/Gstreamer/gstreamer.h>

GStreamer::~GStreamer()
{

}

GStreamer::GStreamer()
{
    mPipeline = NULL;
    mBus = NULL;
    mMsg = NULL;


    if(!initGstream())
    {
        printf("%saiiia fallito a fare l'init di gstreamer\n", LOG_GST_ERRROR);
    }

    if(!init())
    {
        printf("%saiiia fallito a fare l'init della classe\n", LOG_GST_ERRROR);
    }
}

bool GStreamer::initGstream()
{
    int argc = 0;
    //char * argv[] = {"none"};

    if(!gst_init_check(&argc, NULL, NULL))
    {
       printf("%sFallito a fare gst_init, Molto Malen\n", LOG_GST_ERRROR);
       return false;
    }

    //faccio il print della versione attualmente in uso di Gstreamer
    uint32_t ver[] = {0, 0, 0, 0};
    gst_version(&ver[0], &ver[1], &ver[2], &ver[3]);
    printf("%sGStream inizializzato con la versione %u.%u.%u.%u\n", LOG_GST_INFO, ver[0], ver[1], ver[2], ver[3]);

   return true;
}

bool GStreamer::buildLauchstr()
{
    std::ostringstream ss;
    ss << "playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm";
    mLaunchString = ss.str();
    printf("%sStringa di lancio gst : %s\n",LOG_GST_INFO, mLaunchString.c_str());
    return true;
}

bool GStreamer::init()
{
    if( !buildLauchstr())
    {
        printf("%sFallito a creare la stringa di lancio, ritenta\n", LOG_GST_ERRROR);
        return false;
    }

    //parso la pipeline creata precedentemente
    mPipeline = gst_parse_launch(mLaunchString.c_str(), NULL);

    //creo l'oggetto pipeline
    GstPipeline* pipeline = GST_PIPELINE(mPipeline);
    if(!pipeline)
    {
        printf("%sFallito a creare la Pipeline\n", LOG_GST_ERRROR);
        return false;
    }

    //creo l'elmento bus per i messaggi da Gstreamer
    mBus = gst_element_get_bus(mPipeline);
    if(!mBus)
    {
        printf("%sFallito a creare il Bus dei messaggi\n", LOG_GST_ERRROR);
        return false;
    }

    return true;
}

