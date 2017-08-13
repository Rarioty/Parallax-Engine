#include <Parallax/Video/Video.hpp>

#include <Parallax/Video/Decoders/VideoDecoder.hpp>
#include <Parallax/Video/Demultiplexer.hpp>
#include <Parallax/Debug/Debug.hpp>

/*
 * Rendering objects
 */
#include <Parallax/Renderers/Objects/VertexArray.hpp>
#include <Parallax/Renderers/Objects/Program.hpp>
#include <Parallax/Renderers/Objects/Texture.hpp>
#include <Parallax/Renderers/Objects/Buffer.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

namespace Parallax::Video
{
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;

    static bool                             s_playing;
    static std::chrono::time_point<clock_>  s_startTime;

    static Renderer::Texture*               s_texture;
    static Renderer::VertexArray*           s_vao;
    static Renderer::Buffer*                s_pixelBuffer;
    static Renderer::Buffer*                s_quad;
    static Renderer::Program*               s_program;

    void uploadFrame(Renderer::Buffer* pbo, Renderer::Texture* tex, Video::Decoder::Video::Frame::Ptr frame)
    {
        if (!frame)
            return;

        tex->bind();

        pbo->bind();
        pbo->upload({
            .glSize = frame->m_numBytes
        }, frame->m_bytes);

        tex->upload({
            .glSize = (I32)frame->m_width
        }, {
            .glSize = (I32)frame->m_height
        }, {
            .glFormat = GL_RGB
        }, 0);
        pbo->unbind();

        tex->generateMipMaps();
        tex->unbind();
    }

    static const char* vertexShader = ""
    "#version 130\n"
    "\n"
    "uniform mat4 viewMatrix, projectionMatrix;\n"
    "\n"
    "in vec2 position;\n"
    "in vec2 texCoords;\n"
    "\n"
    "out vec2 coords;\n"
    "\n"
    "void main() {\n"
    "	coords = texCoords;\n"
    "	gl_Position = projectionMatrix * viewMatrix * vec4(position,0.0,1.0);\n"
    "}\n";

    static const char* fragmentShader = ""
    "#version 130\n"
    "\n"
    "uniform sampler2D texUnit;\n"
    "\n"
    "in vec2 coords;\n"
    "\n"
    "out vec4 color;\n"
    "\n"
    "void main() {\n"
    "    color = texture(texUnit,coords);\n"
    "}\n";

    bool Init()
    {
		avcodec_register_all();
		av_register_all();
		avformat_network_init();

        s_playing = false;

        s_texture = Renderer::CreateTexture();
        s_vao = Renderer::CreateVertexArray();
        s_pixelBuffer = Renderer::CreateBuffer();
        s_quad = Renderer::CreateBuffer();
        s_program = Renderer::CreateProgram();

        s_texture->create({
            .glTarget = GL_TEXTURE_2D
        }, {
            .glFormat = GL_RGB
        });

        Renderer::TextureParameters::GLTextureParameters glParam;
        glParam.setFilters(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
        glParam.setLevels(0, 10);
        s_texture->configure({
            .glParameters = glParam
        });

        s_pixelBuffer->create({
            .glTarget = GL_PIXEL_UNPACK_BUFFER
        }, {
            .glUsage = GL_STREAM_DRAW
        });

        s_quad->create({
            .glTarget = GL_ARRAY_BUFFER
        }, {
            .glUsage = GL_STATIC_DRAW
        });

        s_vao->create();

        Renderer::VertexLayout layout;
        layout.addAttribute({
            .glAttribute = {
                .location = 0,
                .size = 2,
                .type = GL_FLOAT
            }
        });
        layout.addAttribute({
            .glAttribute = {
                .location = 1,
                .size = 2,
                .type = GL_FLOAT
            }
        });
        layout.fitStrideToAttributes();
        s_quad->configure(layout);
        s_vao->unbind();
        s_quad->unbind();

        s_program->addSource({
            .glType = GL_VERTEX_SHADER
        }, vertexShader);
        s_program->addSource({
            .glType = GL_FRAGMENT_SHADER
        }, fragmentShader);
        s_program->create();
        s_program->compile();
        s_program->link({{"color", {
            .glLoc = 0
        }}}, {{"position", {
            .glLoc = 0
        }}, {"texCoords", {
            .glLoc = 1
        }}});
        s_program->bind();
        s_program->setUniform(s_program->getUniformLocation("texUnit"), 0);
        s_program->setUniform(s_program->getUniformLocation("viewMatrix"), glm::mat4(1.f));

        // TODO: Set it elsewhere !
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);

        return true;
    }

    void Shutdown()
    {
        if (s_texture)
            delete s_texture;
        if (s_vao)
            delete s_vao;
        if (s_pixelBuffer)
            delete s_pixelBuffer;
        if (s_quad)
            delete s_quad;
        if (s_program)
            delete s_program;

        s_texture = nullptr;
        s_vao = nullptr;
        s_pixelBuffer = nullptr;
        s_program = nullptr;

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

        float vertices[] = {
			0,0, 0,1,
			1,0, 1,1,
			1,1, 1,0,
			0,1, 0,0
		};

        s_pixelBuffer->upload({
            .glSize = Decoder::Video::GetBytesPerFrame()
        }, NULL);
        s_quad->upload({
            .glSize = sizeof(vertices)
        }, vertices);

        uploadFrame(s_pixelBuffer, s_texture, Decoder::Video::NextFrame());
        s_startTime = clock_::now();
    }

    void WindowResized(U32 width, U32 height)
    {
        if (s_program)
        {
            float aspect = height / (float)width;
            s_program->setUniform(s_program->getUniformLocation("projectionMatrix"),glm::ortho(
                0.f, 1.f, 0.f, aspect, -1.f, 1.f
            ));

            float x = 0;
            float y = 0;
            float w = 1;
            float h = aspect;

            I32 vW = Decoder::Video::GetWidth();
            I32 vH = Decoder::Video::GetHeight();

            float vR = vH / (float)vW;
            float hNew = w * vR;
            float wNew = w;

            if (hNew > h)
            {
                float scale = h / hNew;
                wNew *= scale;
                hNew *= scale;
            }

            x += (w - wNew) / 2.f;
            y += (h - hNew) / 2.f;

            float vertices[] = {
				x, y,
				0, 1,

				x+wNew, y,
				1, 1,

				x+wNew, y+hNew,
				1, 0,

				x, y+hNew,
				0, 0
            };

            s_quad->bind();
            s_quad->upload({
                .glSize = sizeof(vertices)
            }, vertices);
            s_quad->unbind();
        }
    }

    void Draw()
    {
        if (!s_playing)
            return;

        glClear(GL_COLOR_BUFFER_BIT);

        double elapsed = std::chrono::duration_cast<second_>(clock_::now() - s_startTime).count();
        double target  = Decoder::Video::GetNextTime();

        if (elapsed >= target)
        {
            uploadFrame(s_pixelBuffer, s_texture, Decoder::Video::NextFrame());
        }

        s_texture->bind();
        s_vao->bind();
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        s_vao->unbind();
        s_texture->unbind();
    }
}
