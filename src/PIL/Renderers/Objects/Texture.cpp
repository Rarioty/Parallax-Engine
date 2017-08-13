#include <Parallax/Renderers/Objects/Texture.hpp>

#include <Parallax/Renderers/Objects/GL/GLTexture.hpp>

namespace Parallax
{
    namespace Renderer
    {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
        TextureParameters::GLTextureParameters::GLTextureParameters()
        {
            m_minFilter = GL_NEAREST_MIPMAP_LINEAR;
            m_magFilter = GL_LINEAR;
            m_wrapS = GL_REPEAT;
            m_wrapT = GL_REPEAT;
            m_wrapR = GL_REPEAT;
            m_baseLevel = 0;
            m_maxLevel = 1000;
        }

        void TextureParameters::GLTextureParameters::setFilters(GLenum min, GLenum mag)
        {
            m_minFilter = min;
            m_magFilter = mag;
        }

        void TextureParameters::GLTextureParameters::setWrap(GLenum s, GLenum t, GLenum r)
        {
            m_wrapS = s;
            m_wrapT = t;
            m_wrapR = r;
        }

        void TextureParameters::GLTextureParameters::setLevels(GLint base, GLint max)
        {
            m_baseLevel = base;
            m_maxLevel = max;
        }
#endif

        void Texture::unbind(TextureTarget target)
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            if (GetRendererType() == RendererType::OpenGL)
            {
                glBindTexture(target.glTarget, 0);
            }
#endif
        }

        void Texture::setActiveUnit(I32 unit)
        {
#if PARALLAX_GRAPHICS_OPENGL_ALLOWED
            if (GetRendererType() == RendererType::OpenGL)
            {
                glActiveTexture(GL_TEXTURE0 + unit);
            }
#endif
        }

        Texture* CreateTexture()
        {
            #if PARALLAX_GRAPHICS_OPENGL_ALLOWED
                    if (Renderer::GetRendererType() == Renderer::RendererType::OpenGL)
                        return new GLTexture();
            #endif

            return nullptr;
        }
    }
}
