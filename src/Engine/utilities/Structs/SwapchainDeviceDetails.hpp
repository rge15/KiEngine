#pragma once
#include <utilities/typeAliases.hpp>
#include <utilities/Includes/graphicInclude.hpp>

struct SwapchainDeviceDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    Vector<VkSurfaceFormatKHR> formats;
    Vector<VkPresentModeKHR> presentModes;
};
