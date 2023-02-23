#include "KiEngine.hpp"

KiEngine::KiEngine(String p_appName, size_t p_w, size_t p_h) noexcept
{
    window_delegate     = std::make_unique<WindowDelegate>( p_appName, p_w, p_h );
    instance_delegate   = std::make_unique<InstanceDelegate>( p_appName );
    
    auto& vk_instance   = instance_delegate.get()->getInstance();
    auto& vk_window     = window_delegate.get()->getWindow();

    surface_delegate    = std::make_unique<SurfaceDelegate>( vk_instance, vk_window );

    


}