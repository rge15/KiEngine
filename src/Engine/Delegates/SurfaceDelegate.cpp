#include "SurfaceDelegate.hpp"
#include <utilities/MacrosAssert.hpp>

SurfaceDelegate::SurfaceDelegate(VkInstance& p_instance,GLFWwindow& p_window) noexcept
: owner_instance { p_instance }, owner_window { p_window }
{
    auto result = glfwCreateWindowSurface( owner_instance, &owner_window, nullptr, &surface );

    ASSERT(result == VK_SUCCESS, "Fail the surface retreiving process")
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

SurfaceDelegate::~SurfaceDelegate()
{
    vkDestroySurfaceKHR( owner_instance, surface, nullptr );
}
