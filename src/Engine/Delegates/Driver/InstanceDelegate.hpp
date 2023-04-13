#pragma once
#include <utilities/typeAliases.hpp>
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/MacrosAssert.hpp>


class InstanceDelegate
{
private:
    //Vulkan Instance Handler  
    VkInstance instance { VK_NULL_HANDLE };

    //Name of the App
    String app_name {};
    
    //Application Info
    VkApplicationInfo       app_info{};
    //Instance Creation Info
    VkInstanceCreateInfo    info {};

    //Required Instance layers to init the app
    const Vector<const char*> required_layers = {
        "VK_LAYER_KHRONOS_validation"
    };

private:

    /**
     *  @brief Method that fills the instance creation info
    */
    void
    initCreateInfo() noexcept;

    /**
     *  @brief Method that creates the instance
    */
    void
    createInstance() noexcept;

    /**
     *  @brief Method that enable the instance extensions
    */
    void
    enableInstanceExtensions() noexcept;

    /**
     *  @brief Method that enable the instance layers
    */
    void
    enableInstanceLayers() noexcept;

    /**
     *  @brief Method that fills the app creation info
    */
    void
    initAppInfo() noexcept;

public:
    explicit InstanceDelegate( String p_appName = "AppName" );
    ~InstanceDelegate();

    /**
     *  @brief Getter to obtain a reference to the Vulkan Instance
     * 
     *  @return Reference to the Vulkan Instance
    */
    VkInstance&
    getInstance()
    {
        return instance;
    }
};