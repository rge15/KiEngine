#include <utilities/typeAliases.hpp>
#include <Engine/Delegates/DelegateIncludes.hpp>

#include <Engine/Managers/DriverMng.hpp>

class KiEngine
{
private:
    DriverMng driver_ { "KiEngine",  1280, 720 };

    //TODO : Plantear siguiente parte motor Render/Rsc/WorkMng ...


public:

    KiEngine(
        String p_appName = "AppName",
        size_t p_w = 1280 , size_t p_h = 720
    ) noexcept;
    
    ~KiEngine() = default;

};