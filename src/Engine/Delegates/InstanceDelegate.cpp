#include "InstanceDelegate.hpp"

InstanceDelegate::InstanceDelegate(/* args */)
{
    initCreateInfo();
    createInstance();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

InstanceDelegate::~InstanceDelegate()
{
    vkDestroyInstance( instance, nullptr);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
InstanceDelegate::initCreateInfo() noexcept
{
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = 0;
    info.pApplicationInfo = &app_info;

    enableInstanceExtensions();

    enableInstanceLayers();

    initAppInfo();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
InstanceDelegate::createInstance() noexcept
{
    auto result = vkCreateInstance(&info, nullptr, &instance);

    ASSERT( result == VK_SUCCESS, "Vulkan Instance failed" );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
InstanceDelegate::enableInstanceExtensions() noexcept
{
    uint32_t ext_count = 0;
    const char** ext_names;

    ext_names = glfwGetRequiredInstanceExtensions( &ext_count );

    info.enabledExtensionCount = ext_count;
    info.ppEnabledExtensionNames = ext_names;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
InstanceDelegate::enableInstanceLayers() noexcept
{
    info.enabledLayerCount = required_layers.size();
    info.ppEnabledLayerNames = required_layers.data();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
InstanceDelegate::initAppInfo() noexcept
{
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pNext = nullptr;
    app_info.pEngineName = "KiEngine";
    app_info.pApplicationName = "TestEngine01";
    app_info.apiVersion = VK_MAKE_API_VERSION(0,1,3,0);
    app_info.applicationVersion = VK_MAKE_VERSION(1,0,0);
    app_info.engineVersion = VK_MAKE_VERSION(0,1,1);
}