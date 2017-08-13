#ifndef PARALLAX_GL_TEXTURE_HPP_GUARD
#define PARALLAX_GL_TEXTURE_HPP_GUARD

#include <Parallax/Renderers/Objects/Texture.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED

namespace Parallax
{
    namespace Renderer
    {
        struct GLTexture : Texture
        {
            GLuint  m_uid;

            GLTexture();
            ~GLTexture();
            void create(TextureTarget target, TextureFormat format);
            void destroy();
            void upload(TextureSize width, TextureSize height,
                TextureFormat uploadFormat, void* pixels, I32 mipMapLevel = 0);
            void generateMipMaps();
            void configure(TextureParameters params);

            explicit operator bool();

            void bind();
            void unbind();

            static void unbind(TextureTarget target);
            static void setActiveUnit(I32 unit);
        };
    }
}

#endif

#endif
