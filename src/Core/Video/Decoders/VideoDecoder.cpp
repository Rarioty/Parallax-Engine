#include <Parallax/Video/Decoders/VideoDecoder.hpp>

#include <Parallax/Video/Demultiplexer.hpp>
#include <Parallax/Debug/Debug.hpp>
#include <cstring>

extern "C" {
	#include <libswscale/swscale.h>
    #include <libavutil/imgutils.h>
}

namespace Parallax::Video::Decoder::Video
{
    Frame::Frame()
        : m_width(0)
        , m_height(0)
        , m_numBytes(0)
        , m_bytes(nullptr)
        , m_outTime(0)
    {}

    Frame::~Frame()
    {
        if (m_bytes)
            delete[] m_bytes;
    }

    Frame::Ptr Frame::create(double o, U32 w, U32 h, U32 sz, U8* ptr)
    {
        Frame* frame = new Frame;

        frame->m_outTime = o;
        frame->m_width = w;
        frame->m_height = h;
        frame->m_numBytes = sz;
        frame->m_bytes = new U8[sz];
        if (ptr)
            memcpy(frame->m_bytes, ptr, sz);

        return Ptr(frame);
    }

    static PacketQueue*         s_packetQueue;
    static I32                  s_streamIndex;
    static AVStream*            s_stream;
    static AVCodecParameters*   s_parameters;
	static AVCodecContext* 		s_context;
    static AVFrame              *s_frame, *s_frameRGB;
    static SwsContext*          s_swsContext;

    static double               s_clock;
    static double               s_nextFrameTime;
    static I64                  s_currentFrame;
    static I64                  s_currentDts;
    static U32                  s_width, s_height, s_bytesPerFrame;
    static bool                 s_lastFrame;

    bool Init()
    {
		I32 result;

        PARALLAX_WARN(Demultiplexer::IsOpened(), "Demultiplexer is not open yet !");
        if (!Demultiplexer::IsOpened())
            return false;

        I32 stream = Demultiplexer::GetStreamIndex(AVMEDIA_TYPE_VIDEO);
        PARALLAX_WARN(stream >= 0, "Can't find video stream with the demultiplexer !");
        if (stream < 0)
            return false;

		PARALLAX_TRACE("Video stream is %d", stream);

        s_packetQueue = Demultiplexer::GetPacketQueue(stream);
        s_streamIndex = stream;
        s_stream = Demultiplexer::GetStream(stream);
        s_parameters = s_stream->codecpar;

		AVCodec* codec = avcodec_find_decoder(s_parameters->codec_id);
		s_context = avcodec_alloc_context3(codec);
		result = avcodec_open2(s_context, codec, NULL);

		PARALLAX_WARN(result >= 0, "Can't open codec ! error: %d", result);

		avcodec_parameters_to_context(s_context, s_parameters);

        s_frame = av_frame_alloc();
        s_frameRGB = av_frame_alloc();

        s_clock = 0.0;
        s_nextFrameTime = 0.0;
        s_currentFrame = 0;
        s_lastFrame = false;

        I64 frameNumber = s_stream->nb_frames;
        double frameRate = av_q2d(s_stream->r_frame_rate);
        double bitRate = s_parameters->bit_rate / 1000000.0;

        PARALLAX_TRACE("Video stream:\n\t%lld frames\n\t%f frames/sec\n\t%f bits/sec",
            frameNumber, frameRate, bitRate);

        s_width = s_parameters->width;
        s_height = s_parameters->height;
        s_bytesPerFrame = av_image_get_buffer_size(
            AV_PIX_FMT_RGB24, s_width, s_height, 32);

        s_swsContext = sws_getCachedContext(
            s_swsContext,
            s_width,
            s_height,
            s_context->pix_fmt,
            s_width,
            s_height,
            AV_PIX_FMT_RGB24,
            SWS_BILINEAR,
            NULL,
            NULL,
            NULL
        );

        return true;
    }

    void Shutdown()
    {
        if (s_frame)
            av_free(s_frame);
        if(s_frameRGB)
            av_free(s_frameRGB);
        if (s_swsContext)
            sws_freeContext(s_swsContext);
    }

    U32 GetWidth()
    {
        return s_width;
    }

    U32 GetHeight()
    {
        return s_height;
    }

    U32 GetBytesPerFrame()
    {
        return s_bytesPerFrame;
    }

    bool IsLastFrame()
    {
        return s_lastFrame;
    }

	void seekToFrame(I64 frame)
	{
		Demultiplexer::SeekToTime(frame * av_q2d(s_stream->time_base));
	}

    Frame::Ptr PreviousFrame()
    {
        I64 pts = (s_currentFrame - 1);

        seekToFrame(pts);

        while (true)
        {
			Frame::Ptr frame = NextFrame();

			if (!frame)
				break;

			if (s_currentFrame > pts)
				break;

			if (s_currentFrame == pts)
				return frame;
        }

		return Frame::Ptr();
    }

	int decode(int* complete, AVPacket* packet)
	{
		int ret;

		*complete = 0;

		if (packet)
		{
			ret = avcodec_send_packet(s_context, packet);

			if (ret < 0)
			{
				return ret == AVERROR_EOF ? 0 : ret;
			}
		}

		ret = avcodec_receive_frame(s_context, s_frame);
		if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
			return ret;
		if (ret >= 0)
			*complete = 1;

		return 0;
	}

	Frame::Ptr NextFrame()
	{
		AVPacket packet;
		av_init_packet(&packet);

		while (true)
		{
			if (s_packetQueue->isEmpty())
				Demultiplexer::Demultiplex(s_streamIndex);

			if (!s_packetQueue->pop(&packet))
			{
				s_lastFrame = true;
				break;
			}

			if (PacketQueue::IsFlushPacket(packet))
			{
				avcodec_flush_buffers(s_context);
				continue;
			}

			char errorMessage[512];
			I32 complete = 0;
			I32 error = 0;

			error = decode(&complete, &packet);
			av_strerror(error, errorMessage, 512);
			PARALLAX_WARN(error >= 0, "Error while decoding packet ! error: %d (%s)", error, errorMessage);

			av_packet_unref(&packet);

			if (complete)
			{
				s_currentDts = packet.dts;
				s_currentFrame = s_frame->pts;
				s_currentDts = s_frame->pkt_dts;
				s_clock = s_currentFrame * av_q2d(s_stream->time_base);

				double delay = 0.0;
				delay = av_q2d(s_context->time_base);
				delay += s_frame->repeat_pict * (delay * 0.5);
				s_nextFrameTime = s_clock + delay;

				Frame::Ptr res = Frame::create(s_clock, s_width, s_height, s_bytesPerFrame, nullptr);
				av_image_fill_arrays(s_frameRGB->data, s_frameRGB->linesize,
					res->m_bytes, AV_PIX_FMT_RGB24, s_width, s_height, 1);
				sws_scale(s_swsContext, (U8 const* const*)s_frame->data, s_frame->linesize,
					0, s_height, s_frameRGB->data, s_frameRGB->linesize);

				return res;
			}
		}

		return Frame::Ptr();
	}

	I64 GetCurrentFrame()
	{
		return s_currentFrame;
	}

	double GetCurrentTime()
	{
		return s_clock;
	}

	double GetNextTime()
	{
		return s_nextFrameTime;
	}
}
