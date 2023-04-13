#pragma once
#include <utilities/typeAliases.hpp>
#include <Engine/Delegates/DelegateIncludes.hpp>

class DriverMng
{
private:
    UniqPtr<WindowDelegate>     window_delegate     { nullptr };
    UniqPtr<InstanceDelegate>   instance_delegate   { nullptr };
    UniqPtr<SurfaceDelegate>    surface_delegate    { nullptr };
    UniqPtr<DeviceDelegate>     device_delegate     { nullptr };
    UniqPtr<SwapchainDelegate>  swapchain_delegate  { nullptr };

public:
    DriverMng( String p_str, size_t p_w, size_t p_h );
    ~DriverMng() = default;

};