#ifndef PARALLAX_RENDERER_VULKAN_HPP_GUARD
#define PARALLAX_RENDERER_VULKAN_HPP_GUARD

#include <Parallax/Renderers/IRenderer.hpp>
#include <Parallax/Platform.hpp>

#if PARALLAX_GRAPHICS_VULKAN_ALLOWED

#include <vulkan/vulkan.h>

namespace Parallax
{
    namespace Renderer
    {
        class RendererVulkan : public IRenderer
        {
        public:
            RendererVulkan();
            ~RendererVulkan() override;

            bool            init() override;

            RendererType    getRendererType() const override;
            const char*     getRendererName() const override;

            bool            isDeviceRemoved() override;

        private:
            VkInstance                          m_instance;
            VkPhysicalDevice                    m_physicalDevice;

            VkPhysicalDeviceProperties          m_deviceProperties;
            VkPhysicalDeviceMemoryProperties    m_memoryProperties;
        };
    }
}

#endif

#endif
