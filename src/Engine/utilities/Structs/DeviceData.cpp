#include "DeviceData.hpp"

void
DeviceData::createDevice(VkSurfaceKHR& p_surface) noexcept
{
    if( physical_device == VK_NULL_HANDLE )
    {
        printf("Pls select a physical device");
        return;
    }

    if( device != VK_NULL_HANDLE )
    {
        printf("Theres already a device created");
        return;
    }

    obtainQueueData( p_surface );
    obtainSwapchainData(p_surface);
    fillCreationData();
    createLogicalDevice();
    queue_delegate.obtainQueueHandlers( device );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

DeviceData::~DeviceData() noexcept
{
    if( device != VK_NULL_HANDLE )
    {
        vkDeviceWaitIdle( device );
        vkDestroyDevice( device, nullptr );
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceData::fillCreationData()
{
    vkGetPhysicalDeviceFeatures( physical_device, &device_features );

    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.pNext = nullptr;
    create_info.flags = 0;
    create_info.enabledExtensionCount = PhysicalDeviceSelector::required_extensions.size();
    create_info.ppEnabledExtensionNames = PhysicalDeviceSelector::required_extensions.data();
    create_info.enabledLayerCount = 0;
    create_info.ppEnabledLayerNames = nullptr;
    create_info.pEnabledFeatures = &device_features;

    auto& queue_info = queue_delegate.queues_info;
    create_info.queueCreateInfoCount = queue_info.size();
    create_info.pQueueCreateInfos = queue_info.data();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceData::createLogicalDevice()
{
    auto result = vkCreateDevice( physical_device, &create_info, nullptr, &device );

    ASSERT( result == VK_SUCCESS, "Error creating the logical device")
    printf("Logical device created succesfully");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceData::obtainSwapchainData(VkSurfaceKHR& p_surface)
{
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR( physical_device, p_surface, &swap_details.capabilities );

    uint32_t presentCount { 0 };
    vkGetPhysicalDeviceSurfacePresentModesKHR( physical_device, p_surface, &presentCount, nullptr );
    swap_details.presentModes.resize(presentCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR( physical_device, p_surface, &presentCount, &swap_details.presentModes[0] );

    uint32_t formatCount { 0 };
    vkGetPhysicalDeviceSurfaceFormatsKHR( physical_device, p_surface, &formatCount, nullptr);
    swap_details.formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR( physical_device, p_surface, &formatCount, &swap_details.formats[0]);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceData::obtainQueueData(VkSurfaceKHR& p_surface)
{
    ASSERT( physical_device != VK_NULL_HANDLE, "Select a physical device before getting queue IDS");
    
    queue_delegate.getQueueIds( physical_device, p_surface );
    queue_delegate.fillQueueCreationInfo();
}
