#include "DeviceDelegate.hpp"

DeviceDelegate::DeviceDelegate( VkInstance& p_instance, VkSurfaceKHR& p_surface )
: instance { p_instance }, surface { p_surface }
{
    device.physical_device = PhysicalDeviceSelector::selectBestPhysicalDevice( instance, surface );
    device.createDevice( surface );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

DeviceDelegate::~DeviceDelegate()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


