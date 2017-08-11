#include <Parallax/Video/Demultiplexer.hpp>

#include <Parallax/Debug/Debug.hpp>

#include <mutex>
#include <map>

namespace Parallax::Video
{
    AVPacket PacketQueue::m_flushPacket;

    PacketQueue::PacketQueue()
    {
        std::once_flag once;
        std::call_once(once, [&](){
            av_init_packet(&m_flushPacket);
            m_flushPacket.data = (U8*)"FLUSH";
        });
    }

    bool PacketQueue::isEmpty()
    {
        return m_packets.empty();
    }

    void PacketQueue::push(AVPacket packet)
    {
        AVPacket tmp;
        av_init_packet(&tmp);
        av_packet_ref(&tmp, &packet);

        m_packets.push_back(tmp);
    }

    bool PacketQueue::pop(AVPacket* packet)
    {
        if (!m_packets.empty())
        {
            *packet = m_packets.front();
            m_packets.pop_front();
            return true;
        }

        return false;
    }

    void PacketQueue::flush()
    {
        for (AVPacket& p : m_packets)
        {
            if (!PacketQueue::IsFlushPacket(p))
                av_packet_unref(&p);
        }

        m_packets.clear();
        m_packets.push_back(m_flushPacket);
    }

    bool PacketQueue::IsFlushPacket(AVPacket packet)
    {
        return packet.data == m_flushPacket.data;
    }

    namespace Demultiplexer
    {
        static AVFormatContext*             s_formatContext = nullptr;
        static std::map<I32, PacketQueue*>  s_packetQueues;

        bool Open(const char* filepath)
        {
            AVFormatContext* format = nullptr;
            char errorBuffer[512];
            I32 result;

            result = avformat_open_input(&format, filepath, NULL, NULL);
            PARALLAX_WARN(result >= 0, "Can't open file %s ! error: %d", filepath, result);
            if (result < 0)
            {
                av_strerror(result, errorBuffer, 512);
                PARALLAX_TRACE("Error string: %s", errorBuffer);
                return false;
            }

            result = avformat_find_stream_info(format, NULL);
            PARALLAX_WARN(result >= 0, "Can't find stream info ! error: %d", result);
            if (result < 0)
                return false;

            s_formatContext = format;

            return true;
        }

        void Close()
        {
            if (s_formatContext)
            {
                avformat_close_input(&s_formatContext);

                for (auto packetQueue : s_packetQueues)
                    delete packetQueue.second;
                s_packetQueues.clear();
            }
        }

        bool IsOpened()
        {
            return s_formatContext != nullptr;
        }

        AVFormatContext* GetFormat()
        {
            return s_formatContext;
        }

        AVStream* GetStream(I32 streamIndex)
        {
            PARALLAX_WARN(streamIndex >= 0 && streamIndex < s_formatContext->nb_streams, "Index is outside stream indexes range !");
            if (streamIndex < 0 || streamIndex >= s_formatContext->nb_streams)
                return nullptr;

            return s_formatContext->streams[streamIndex];
        }

        I32 GetStreamIndex(AVMediaType type)
        {
            return av_find_best_stream(s_formatContext, type, -1, -1, NULL, 0);
        }

        PacketQueue* GetPacketQueue(I32 streamIndex)
        {
            I32 result;

            PARALLAX_WARN(streamIndex >= 0 && streamIndex < s_formatContext->nb_streams, "Index is outside stream indexes range !");
            if (streamIndex < 0 || streamIndex >= s_formatContext->nb_streams)
                return nullptr;

            // Check if one already exists
            if (s_packetQueues.count(streamIndex))
                return s_packetQueues[streamIndex];

            // Get the stream
            AVStream* stream = s_formatContext->streams[streamIndex];

            // And the codec parameters
            AVCodecParameters* parameters = stream->codecpar;

            // Find the decoder
            AVCodec* codec = avcodec_find_decoder(parameters->codec_id);

            // Generate context
            AVCodecContext* context = avcodec_alloc_context3(codec);
            avcodec_parameters_to_context(context, parameters);

            // Initialize the decoder
            result = avcodec_open2(context, codec, NULL);
            PARALLAX_WARN(result >= 0, "Can't open decoder !");
            if (result < 0)
                return nullptr;

            // Allocate some storage
            context->opaque = (U64*)av_malloc(sizeof(U64));

            // Create the new PacketQueue
            PacketQueue* queue = new PacketQueue;
            s_packetQueues[streamIndex] = queue;

            return queue;
        }

        void Demultiplex(I32 streamIndex)
        {
            I32 result;

            PARALLAX_WARN(streamIndex >= 0 && streamIndex < s_formatContext->nb_streams, "Index is outside stream indexes range !");
            if (streamIndex < 0 || streamIndex >= s_formatContext->nb_streams)
                return;

            if (s_packetQueues.count(streamIndex))
            {
                AVPacket packet;

                while (true)
                {
                    result = av_read_frame(s_formatContext, &packet);
                    PARALLAX_WARN(result >= 0, "Can't read frame ! error: %d", result);
                    if (result < 0)
                        return;

                    if (s_packetQueues.count(packet.stream_index))
                    {
                        s_packetQueues[packet.stream_index]->push(packet);

                        if (packet.stream_index == streamIndex)
                            return;
                    }
                    else
                    {
                        av_packet_unref(&packet);
                    }
                }
            }
        }

        void SeekToTime(double time)
        {
            I64 ts = time * AV_TIME_BASE - AV_TIME_BASE;

            avformat_seek_file(s_formatContext, -1, INT64_MIN, ts, ts, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);

            for (auto p : s_packetQueues)
                p.second->flush();
        }
    }
}
