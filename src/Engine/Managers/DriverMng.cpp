#include "DriverMng.hpp"

DriverMng::DriverMng(String p_appName, size_t p_w, size_t p_h)
{
    window_delegate     = std::make_unique<WindowDelegate>( p_appName, p_w, p_h );
    instance_delegate   = std::make_unique<InstanceDelegate>( p_appName );
    
    auto& vk_instance   = instance_delegate.get()->getInstance();
    auto& vk_window     = window_delegate.get()->getWindow();

    surface_delegate    = std::make_unique<SurfaceDelegate>( vk_instance, vk_window );

    auto& vk_surface    = surface_delegate.get()->getSurface();

    device_delegate     = std::make_unique<DeviceDelegate>( vk_instance, vk_surface);
    auto& device        = device_delegate.get()->getVkDevice();
    const auto& queueDelegate = device_delegate.get()->getQueueDelegate();
    const auto& swapDetails   = device_delegate.get()->getSwapDetails();

    swapchain_delegate  = std::make_unique<SwapchainDelegate>( device, vk_surface, swapDetails, queueDelegate );
}