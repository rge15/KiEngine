#pragma once
#include <utilities/typeAliases.hpp>
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/MacrosAssert.hpp>


class InstanceDelegate
{
private:
    VkInstance instance { VK_NULL_HANDLE };

    VkApplicationInfo       app_info{};
    VkInstanceCreateInfo    info {};

    const Vector<const char*> required_layers = {
        "VK_LAYER_KHRONOS_validation"
    };

private:

    void
    initCreateInfo() noexcept;

    void
    createInstance() noexcept;

    void
    enableInstanceExtensions() noexcept;

    void
    enableInstanceLayers() noexcept;

    void
    initAppInfo() noexcept;

public:
    
    InstanceDelegate(/* args */);
    ~InstanceDelegate();
};