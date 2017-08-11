#include <Parallax/Video/Video.hpp>

#include <Parallax/Video/Decoders/VideoDecoder.hpp>
#include <Parallax/Video/Demultiplexer.hpp>
#include <Parallax/Debug/Debug.hpp>

#include <boost/timer.hpp>

namespace Parallax::Video
{
    static bool             s_playing;
    static boost::timer*    s_timer;

    bool Init()
    {
        av_register_all();

        s_playing = false;
        s_timer = nullptr;

        return true;
    }

    void Shutdown()
    {
        Decoder::Video::Shutdown();
        Video::Demultiplexer::Close();
    }

    void PlayVideo(const char* filename)
    {
        bool resultB;

        resultB = Demultiplexer::Open(filename);
        PARALLAX_FATAL(resultB, "Can't open file %s in the demultiplexer !", filename);

        resultB = Decoder::Video::Init();
        PARALLAX_FATAL(resultB, "Can't initialize video decoder !");

        s_playing = true;
        s_timer = new boost::timer();
    }

    void Draw()
    {
        if (!s_playing)
            return;

        double elapsed = s_timer->elapsed();
        double target = Decoder::Video::GetNextTime();

        if (elapsed >= target)
        {
            // Do something
        }
    }
}
