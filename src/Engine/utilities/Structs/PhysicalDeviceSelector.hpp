#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <Engine/utilities/typeAliases.hpp>
#include <utilities/MacrosAssert.hpp>

namespace PhysicalDeviceSelector
{

	const Vector<const char*> required_extensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

    namespace
    {
        void
        getQueueFamilies( VkPhysicalDevice& p_device, Vector<VkQueueFamilyProperties>& p_families) noexcept;
    
        uint32_t
        rateQueueDevice( VkPhysicalDevice& p_device, VkSurfaceKHR& p_surface );

        uint32_t
        rateSwapchainDevice( VkPhysicalDevice& p_device, VkSurfaceKHR& p_surface );

        uint32_t
        rateDeviceProperties( VkPhysicalDevice& p_device );

        uint32_t
        rateDeviceExtensions( VkPhysicalDevice& p_device );

        uint32_t
        rateDevice( VkPhysicalDevice& p_device ) noexcept;

    }

    void
    getAvailableDevices( VkInstance& p_instance, Vector<VkPhysicalDevice>& p_devices) noexcept;

    VkPhysicalDevice
    selectBestPhysicalDevice( VkInstance& p_instance, VkSurfaceKHR& p_surface ) noexcept;

    bool
    hasGraphicQueueFamily( VkQueueFamilyProperties& p_family ) noexcept;

    bool
    hasPresentQueue( VkPhysicalDevice& p_device, uint32_t p_id, VkSurfaceKHR& p_surface ) noexcept;

}