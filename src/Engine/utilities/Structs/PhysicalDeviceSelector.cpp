#include "PhysicalDeviceSelector.hpp"

namespace PhysicalDeviceSelector
{

namespace // private namespace
{
    void
    getQueueFamilies( VkPhysicalDevice& p_device, Vector<VkQueueFamilyProperties>& p_families) noexcept
    {
        uint32_t family_count { 0 };
        vkGetPhysicalDeviceQueueFamilyProperties(p_device, &family_count, nullptr);
        p_families.resize( family_count );
        vkGetPhysicalDeviceQueueFamilyProperties(p_device, &family_count, p_families.data());
    }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

    uint32_t
    rateQueueDevice( VkPhysicalDevice& p_device, VkSurfaceKHR& p_surface )
    {
        bool graphic_queue { false }, present_queue { false };
        Vector<VkQueueFamilyProperties> queue_families {};

        getQueueFamilies(p_device, queue_families);

        uint32_t family_id { 0 };
        for(auto& family : queue_families)
        {
            if(!graphic_queue)
                graphic_queue = hasGraphicQueueFamily(family);

            if(!present_queue)
                present_queue = hasPresentQueue(p_device, family_id, p_surface );
            
            ++family_id;
        }

        if( graphic_queue && present_queue )
            return 100;

        return 0;
    }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

    uint32_t
    rateSwapchainDevice( VkPhysicalDevice& p_device, VkSurfaceKHR& p_surface )
    {
        uint32_t present_count { 0 };
        vkGetPhysicalDeviceSurfacePresentModesKHR( p_device, p_surface, &present_count, nullptr );

        uint32_t formats_count { 0 };
        vkGetPhysicalDeviceSurfaceFormatsKHR( p_device, p_surface, &formats_count, nullptr );

        if( present_count > 0 && formats_count > 0 )
            return 100;
        
        return 0;
    }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

    uint32_t
    rateDeviceProperties( VkPhysicalDevice& p_device )
    {
        uint32_t score = 10;

        VkPhysicalDeviceProperties properties {};
        vkGetPhysicalDeviceProperties( p_device, &properties );
        
        VkPhysicalDeviceFeatures features {};
        vkGetPhysicalDeviceFeatures( p_device, &features );
    
        if( properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU )
            score += 100; 

        score += properties.limits.maxImageDimension2D;

        if( !features.geometryShader )
            return 0;

        return score;
    }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

    uint32_t
    rateDeviceExtensions( VkPhysicalDevice& p_device )
    {
        uint32_t ext_count { 0 };
        Vector<VkExtensionProperties> extensions {};
        vkEnumerateDeviceExtensionProperties( p_device, nullptr, &ext_count, nullptr);
        extensions.resize(ext_count);
        vkEnumerateDeviceExtensionProperties( p_device, nullptr, &ext_count, extensions.data());

        Set<std::string> extension_set( required_extensions.begin(), required_extensions.end() );

        for(auto& extension : extensions)
        {
            extension_set.erase( extension.extensionName );
        }

        if( extension_set.empty() )
            return 100;
        
        return 0;
    }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

    uint32_t
    rateDevice( VkPhysicalDevice& p_device, VkSurfaceKHR& p_surface ) noexcept
    {
        uint32_t score = 0;

        auto queue_score = PhysicalDeviceSelector::rateQueueDevice( p_device, p_surface );
        if (queue_score == 0)
            return 0;

        auto swapchain_score = PhysicalDeviceSelector::rateSwapchainDevice( p_device, p_surface );
        if (swapchain_score == 0)
            return 0;

        auto properties_score = PhysicalDeviceSelector::rateDeviceProperties( p_device );
        if (properties_score == 0)
            return 0;

        auto extension_score = PhysicalDeviceSelector::rateDeviceExtensions( p_device );
        if (extension_score == 0)
            return 0;


        score += queue_score;
        score += swapchain_score;
        score += properties_score;
        score += extension_score;

        return score;
    }

} // private namespace

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

    bool
    hasGraphicQueueFamily( VkQueueFamilyProperties& p_family ) noexcept
    {
        if(p_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            return true;
        return false; 
    }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

    bool
    hasPresentQueue( VkPhysicalDevice& p_device, uint32_t p_id, VkSurfaceKHR& p_surface ) noexcept
    {
        VkBool32 present_support {};
        vkGetPhysicalDeviceSurfaceSupportKHR( p_device, p_id, p_surface, &present_support);
        if( present_support == VK_TRUE )
            return true;
        return false;
    }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

    void
    getAvailableDevices( VkInstance& p_instance, Vector<VkPhysicalDevice>& p_devices) noexcept
    {
        uint32_t device_count = 0;
        vkEnumeratePhysicalDevices( p_instance, &device_count, nullptr );
        p_devices.resize(device_count);
        vkEnumeratePhysicalDevices( p_instance, &device_count, p_devices.data() );
    }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

    VkPhysicalDevice
    selectBestPhysicalDevice( VkInstance& p_instance, VkSurfaceKHR& p_surface ) noexcept
    {
        Vector<VkPhysicalDevice> available_devices {};
        getAvailableDevices( p_instance, available_devices );

        ASSERT( available_devices.size() != 0, "There's no available devices" );

        uint32_t best_device_score  = 0;
        uint32_t best_device_id     = 0;

        uint32_t device_id = 0;
        for(auto& device : available_devices )
        {
            uint32_t device_score = rateDevice( device, p_surface );
            if( device_score > best_device_score )
            {
                best_device_id = device_id;
                best_device_score = device_score;
            }

            ++device_id;
        }

        ASSERT(best_device_score != 0, "There's no suitable physical device")

        auto device = available_devices[best_device_id];

        return device;
    }


}