#include <Parallax/Renderers/Objects/GL/GLTexture.hpp>

#if PARALLAX_GRAPHICS_OPENGL_ALLOWED

namespace Parallax::Renderer
{
    GLTexture::GLTexture()
    {
        m_uid = 0;
        m_target.glTarget = 0;
        m_width.glSize = 0;
        m_height.glSize = 0;
    }

    GLTexture::~GLTexture()
    {}

    void GLTexture::create(TextureTarget target, TextureFormat format)
    {
        glGenTextures(1, &m_uid);
        m_target = target;
        m_format = format;
        bind();
    }

    void GLTexture::destroy()
    {
        glDeleteTextures(1, &m_uid);
    }

    void GLTexture::upload(TextureSize width, TextureSize height, TextureFormat uploadFormat, void* pixels, I32 mipMapLevel)
    {
        m_width = width;
        m_height = height;
        glTexImage2D(m_target.glTarget, mipMapLevel, m_format.glFormat, width.glSize, height.glSize,
            0, uploadFormat.glFormat, GL_UNSIGNED_BYTE, (const GLubyte*)pixels);
    }

    void GLTexture::generateMipMaps()
    {
        glGenerateMipmap(m_target.glTarget);
    }

    void GLTexture::configure(TextureParameters parameters)
    {
        glTexParameteri(m_target.glTarget, GL_TEXTURE_MIN_FILTER, parameters.glParameters.m_minFilter);
        glTexParameteri(m_target.glTarget, GL_TEXTURE_MAG_FILTER, parameters.glParameters.m_magFilter);
        glTexParameteri(m_target.glTarget, GL_TEXTURE_WRAP_S, parameters.glParameters.m_wrapS);
        glTexParameteri(m_target.glTarget, GL_TEXTURE_WRAP_T, parameters.glParameters.m_wrapT);
        glTexParameteri(m_target.glTarget, GL_TEXTURE_WRAP_R, parameters.glParameters.m_wrapR);
        glTexParameteri(m_target.glTarget, GL_TEXTURE_BASE_LEVEL, parameters.glParameters.m_baseLevel);
        glTexParameteri(m_target.glTarget, GL_TEXTURE_MAX_LEVEL, parameters.glParameters.m_maxLevel);
    }

    GLTexture::operator bool()
    {
        return m_uid != 0;
    }

    void GLTexture::bind()
    {
        glBindTexture(m_target.glTarget, m_uid);
    }

    void GLTexture::unbind()
    {
        glBindTexture(m_target.glTarget, 0);
    }
}

#endif
