#include <Parallax/Renderers/RendererVulkan.hpp>

#if PARALLAX_GRAPHICS_VULKAN_ALLOWED

#include <Parallax/Parallax.hpp>
#include <Parallax/Types.hpp>

#include <vulkan/vulkan.h>
#include <iostream>

namespace Parallax::Renderer::Vulkan
{
    static VkInstance                       s_instance;
    static VkPhysicalDevice                 s_physicalDevice;

    static VkPhysicalDeviceProperties       s_deviceProperties;
    static VkPhysicalDeviceMemoryProperties s_memoryProperties;

    static const char* getName(VkResult _result)
    {
        switch (_result)
		{
#define VKENUM(_ty) case _ty: return #_ty
			VKENUM(VK_SUCCESS);
			VKENUM(VK_NOT_READY);
			VKENUM(VK_TIMEOUT);
			VKENUM(VK_EVENT_SET);
			VKENUM(VK_EVENT_RESET);
			VKENUM(VK_INCOMPLETE);
			VKENUM(VK_ERROR_OUT_OF_HOST_MEMORY);
			VKENUM(VK_ERROR_OUT_OF_DEVICE_MEMORY);
			VKENUM(VK_ERROR_INITIALIZATION_FAILED);
			VKENUM(VK_ERROR_DEVICE_LOST);
			VKENUM(VK_ERROR_MEMORY_MAP_FAILED);
			VKENUM(VK_ERROR_LAYER_NOT_PRESENT);
			VKENUM(VK_ERROR_EXTENSION_NOT_PRESENT);
			VKENUM(VK_ERROR_FEATURE_NOT_PRESENT);
			VKENUM(VK_ERROR_INCOMPATIBLE_DRIVER);
			VKENUM(VK_ERROR_TOO_MANY_OBJECTS);
			VKENUM(VK_ERROR_FORMAT_NOT_SUPPORTED);
			VKENUM(VK_ERROR_SURFACE_LOST_KHR);
			VKENUM(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
			VKENUM(VK_SUBOPTIMAL_KHR);
			VKENUM(VK_ERROR_OUT_OF_DATE_KHR);
			VKENUM(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
			VKENUM(VK_ERROR_VALIDATION_FAILED_EXT);
#undef VKENUM
			default: break;
		}

		return "<VkResult?>";
    }

    bool Init()
    {
        VkResult result;

        {
            VkApplicationInfo appInfo;
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pNext = NULL;
            appInfo.pApplicationName = "Parallax Engine";
            appInfo.applicationVersion = PARALLAX_VERSION;
            appInfo.pEngineName = "Parallax Engine";
            appInfo.engineVersion = PARALLAX_VERSION;
            appInfo.apiVersion = VK_MAKE_VERSION(PARALLAX_VERSION_MAJOR, PARALLAX_VERSION_MINOR, PARALLAX_VERSION_PATCH);

            VkInstanceCreateInfo ici;
            ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            ici.pNext = NULL;
            ici.flags = 0;
            ici.pApplicationInfo = &appInfo;
            ici.enabledLayerCount = 0;
            ici.ppEnabledLayerNames = NULL;
            ici.enabledExtensionCount = 0;
            ici.ppEnabledExtensionNames = NULL;

            result = vkCreateInstance(&ici, NULL, &s_instance);
        }

        if (VK_SUCCESS != result)
        {
            std::cerr << "vkCreateInstance failed " << result << ": " << getName(result) << std::endl;
            return false;
        }

        U32 numPhysicalDevices;
        result = vkEnumeratePhysicalDevices(s_instance, &numPhysicalDevices, NULL);

        if (VK_SUCCESS != result)
        {
            std::cerr << "vkEnumeratePhysicalDevices failed " << result << ": " << getName(result) << std::endl;
            return false;
        }

        std::cout << numPhysicalDevices << " devices has been found !" << std::endl;

        VkPhysicalDevice physicalDevices[4];
        numPhysicalDevices = numPhysicalDevices < 4 ? numPhysicalDevices : 4;
        result = vkEnumeratePhysicalDevices(s_instance, &numPhysicalDevices, physicalDevices);

        if (VK_SUCCESS != result)
        {
            std::cerr << "vkEnumeratePhysicalDevices failed " << result << ": " << getName(result) << std::endl;
            return false;
        }

        s_physicalDevice = VK_NULL_HANDLE;

        for (U32 i = 0; i < numPhysicalDevices; ++i)
        {
            VkPhysicalDeviceProperties pdp;
            vkGetPhysicalDeviceProperties(physicalDevices[i], &pdp);
            std::cout << "Physical device: " << i << std::endl;
            std::cout << "\t          Name: " << pdp.deviceName << std::endl;
            std::cout << "\t   API version: " << pdp.apiVersion << std::endl;
            std::cout << "\tDriver version: " << pdp.driverVersion << std::endl;
            std::cout << "\t      VendorID: " << pdp.vendorID << std::endl;
            std::cout << "\t      DeviceID: " << pdp.deviceID << std::endl;
            std::cout << "\t          Type: " << pdp.deviceType << std::endl;
        }

        return true;
    }

    void Shutdown()
    {

    }

    RendererType GetRendererType() const
    {
        return RendererType::Vulkan;
    }

    const char* GetRendererName() const
    {
        return PARALLAX_GRAPHICS_VULKAN_NAME;
    }

    bool IsDeviceRemoved()
    {
        return false;
    }
}

#endif
