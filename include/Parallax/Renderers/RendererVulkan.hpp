#ifndef RENDERER_VULKAN_HPP
#define RENDERER_VULKAN_HPP

#include <Parallax/Renderers/IRenderer.hpp>
#include <Parallax/Renderers/Config.hpp>

#if PARALLAX_CONFIG_RENDERER_VULKAN

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
