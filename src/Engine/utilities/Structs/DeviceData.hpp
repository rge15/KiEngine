#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/utilities/Structs/SwapchainDeviceDetails.hpp>
#include <Engine/utilities/Structs/PhysicalDeviceSelector.hpp> 
#include <utilities/MacrosAssert.hpp>
#include <Engine/Delegates/QueueDelegate.hpp>

struct DeviceData
{
public:
    VkPhysicalDevice    physical_device { VK_NULL_HANDLE };
    VkDevice            device          { VK_NULL_HANDLE };

    VkPhysicalDeviceFeatures device_features {};

    SwapchainDeviceDetails swap_details {};

    VkDeviceCreateInfo  create_info {};

    QueueDelegate   queue_delegate {};

public:
    void
    createDevice( VkSurfaceKHR& p_surface ) noexcept;

    ~DeviceData() noexcept;

private:

    void
    fillCreationData();

    void
    createLogicalDevice();

    void
    obtainSwapchainData(VkSurfaceKHR& p_surface);

    void
    obtainQueueData(VkSurfaceKHR& p_surface);

};
