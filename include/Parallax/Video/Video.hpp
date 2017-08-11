#ifndef PARALLAX_VIDEO_HPP_GUARD
#define PARALLAX_VIDEO_HPP_GUARD

#include <Parallax/Types.hpp>
#include <string>

namespace Parallax
{
    namespace Video
    {
        bool Init();
        void Shutdown();

        void PlayVideo(const char* filename);
        void Draw();
    }
}

#endif
