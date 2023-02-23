#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class SurfaceDelegate
{
private:
    //Reference to objetcs that form the Surface
    VkInstance& owner_instance;
    GLFWwindow& owner_window;

    // VkSurface Handler
    VkSurfaceKHR surface { VK_NULL_HANDLE };
    
public:
    explicit SurfaceDelegate(VkInstance& p_instance,GLFWwindow& p_window) noexcept;
    ~SurfaceDelegate() noexcept;

    /**
     *  @brief Gets the VKSurfaceKHR
     * 
     *  @return VKSurfaceKHR& that the manager handle
    */
    VkSurfaceKHR&
    getSurface()
    {
        return surface;
    }
};