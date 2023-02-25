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

private:

    void
    selectBestPhysicalDevice() noexcept;

    void
    getAvailableDevices(Vector<VkPhysicalDevice>& p_devices) noexcept;

    uint32_t
    rateDevice( VkPhysicalDevice& p_device ) const noexcept;

public:
    DeviceDelegate(VkInstance& p_instance, VkSurfaceKHR& p_surface);
    ~DeviceDelegate();
};

