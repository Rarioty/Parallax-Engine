#ifndef PARALLAX_DEMULTIPLEXER_HPP_GUARD
#define PARALLAX_DEMULTIPLEXER_HPP_GUARD

#include <Parallax/Types.hpp>

extern "C" {
    #include <libavformat/avformat.h>
}

#include <list>

namespace Parallax
{
    namespace Video
    {
        struct PacketQueue
        {
            std::list<AVPacket>     m_packets;
            static  AVPacket        m_flushPacket;

            PacketQueue();
            bool    isEmpty();
            void    push(AVPacket packet);
            bool    pop(AVPacket* packet);
            void    flush();

            static  bool IsFlushPacket(AVPacket packet);
        };

        namespace Demultiplexer
        {
            bool                Open(const char* filepath);
            void                Close();

            bool                IsOpened();

            AVFormatContext*    GetFormat();
            I32                 GetStreamIndex(AVMediaType type);
            AVStream*           GetStream(I32 streamIndex);
            PacketQueue*        GetPacketQueue(I32 streamIndex);

            void                Demultiplex(I32 streamIndex);
            void                SeekToTime(double time);
        }
    }
}

#endif
