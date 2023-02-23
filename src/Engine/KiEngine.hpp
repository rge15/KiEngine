#include <utilities/typeAliases.hpp>
#include <Engine/Delegates/DelegateIncludes.hpp>

class KiEngine
{
private:
    UniqPtr<WindowDelegate> window_delegate { nullptr };
    UniqPtr<InstanceDelegate> instance_delegate { nullptr };
    UniqPtr<SurfaceDelegate> surface_delegate { nullptr };

public:

    KiEngine(
        String p_appName = "AppName",
        size_t p_w = 1280 , size_t p_h = 720
    ) noexcept;
    
    ~KiEngine() = default;

};