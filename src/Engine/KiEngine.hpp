#include <utilities/typeAliases.hpp>
#include <Engine/Delegates/DelegateIncludes.hpp>

class KiEngine
{
private:
    UniqPtr<WindowDelegate> window_delegate {};
    UniqPtr<InstanceDelegate> instance_delegate {};

public:

    KiEngine(/* args */);
    ~KiEngine() = default;

};