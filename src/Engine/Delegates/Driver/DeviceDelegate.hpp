#pragma once
#include <Engine/utilities/Structs/DeviceData.hpp>
#include <utilities/MacrosAssert.hpp>
#include <Engine/utilities/typeAliases.hpp>
#include <Engine/utilities/Structs/PhysicalDeviceSelector.hpp>

class DeviceDelegate
{
private:
    VkInstance&     instance;
    VkSurfaceKHR&   surface;

    DeviceData      device;

public:
    DeviceDelegate(VkInstance& p_instance, VkSurfaceKHR& p_surface);
    ~DeviceDelegate() = default;

    inline
    VkDevice& getVkDevice(){ return device.device; };

    inline
    QueueDelegate& getQueueDelegate(){ return device.queue_delegate; };

    inline
    SwapchainDeviceDetails& getSwapDetails(){ return device.swap_details; };

};

