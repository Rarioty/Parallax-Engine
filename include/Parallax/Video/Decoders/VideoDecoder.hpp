#ifndef PARALLAX_VIDEO_DECODER_HPP_GUARD
#define PARALLAX_VIDEO_DECODER_HPP_GUARD

#include <Parallax/Types.hpp>
#include <memory>

namespace Parallax
{
    namespace Video
    {
        namespace Decoder
        {
            namespace Video
            {
                struct Frame
                {
                    typedef std::shared_ptr<Frame> Ptr;

                    U32     m_width;
                    U32     m_height;
                    U32     m_numBytes;
                    U8*     m_bytes;

                    double  m_outTime;

                    ~Frame();
                    static Ptr create(double o, U32 w, U32 h, U32 sz, U8* ptr);

                private:
                    Frame();
                    Frame(const Frame&) =delete;
                    Frame& operator=(const Frame&) =delete;
                };

                bool        Init();
                void        Shutdown();

                U32         GetWidth();
                U32         GetHeight();
                U32         GetBytesPerFrame();
                bool        IsLastFrame();

                Frame::Ptr  PreviousFrame();
                Frame::Ptr  NextFrame();

                I64         GetCurrentFrame();
                double      GetCurrentTime();
                double      GetNextTime();
            }
        }
    }
}

#endif
