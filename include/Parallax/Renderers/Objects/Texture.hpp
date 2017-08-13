#ifndef PARALLAX_TEXTURE_HPP_GUARD
#define PARALLAX_TEXTURE_HPP_GUARD

#include <Parallax/Platform.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
    #include <Parallax/Renderers/RendererGL.hpp>
#endif

namespace Parallax
{
    namespace Renderer
    {
        union TextureParameters
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            struct GLTextureParameters
            {
                GLenum m_minFilter, m_magFilter;
                GLenum m_wrapS, m_wrapT, m_wrapR;
                GLint m_baseLevel, m_maxLevel;

                GLTextureParameters();
                void    setFilters(GLenum min, GLenum mag);
                void    setWrap(GLenum s, GLenum t, GLenum r = GL_REPEAT);
                void    setLevels(GLint base, GLint max);
            } glParameters;
#endif
        };

        union TextureTarget
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            GLenum  glTarget;
#endif
        };

        union TextureFormat
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            GLenum  glFormat;
#endif
        };

        union TextureSize
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            GLsizei     glSize;
#endif
        };

        struct Texture
        {
            TextureTarget   m_target;
            TextureFormat   m_format;
            TextureSize     m_width, m_height;

            virtual         ~Texture(){};
            virtual void    create(TextureTarget target, TextureFormat format) = 0;
            virtual void    destroy() = 0;
            virtual void    upload(TextureSize width, TextureSize height,
                TextureFormat uploadFormat, void* pixels, I32 mipMapLevel = 0) = 0;
            virtual void    generateMipMaps() = 0;
            virtual void    configure(TextureParameters params) = 0;

            virtual explicit operator bool() = 0;

            virtual void    bind() = 0;
            virtual void    unbind() = 0;

            static void     unbind(TextureTarget target);
            static void     setActiveUnit(I32 unit);
        };

        Texture*    CreateTexture();
    }
}

#endif
