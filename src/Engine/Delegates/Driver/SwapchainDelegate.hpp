#pragma once
#include <utilities/Includes/graphicInclude.hpp>
#include <Engine/Delegates/Driver/QueueDelegate.hpp>
#include <Engine/utilities/Structs/SwapchainDeviceDetails.hpp>

class SwapchainDelegate
{
private:
    VkDevice&       device_;
    VkSurfaceKHR&   surface_;
    
    const SwapchainDeviceDetails&   swapDetails_;
    const QueueDelegate&            queueDel_;

    VkSwapchainKHR swapchain_ { VK_NULL_HANDLE };
    
    VkSwapchainCreateInfoKHR createInfo_ {};

    Vector<uint32_t>    queueFamilies_;
    Vector<VkImage>     swapImages_;
    Vector<VkImageView> viewImages_;

public:
    SwapchainDelegate(
        VkDevice& p_device, VkSurfaceKHR& p_surface,
        const SwapchainDeviceDetails& p_devDetails, const QueueDelegate& p_queueDelegate
    ) noexcept;
    
    ~SwapchainDelegate();

    inline
    const VkSwapchainCreateInfoKHR&
    getSwapchainInfo() const { return createInfo_; };

    inline
    const Vector<VkImageView>&
    getSwapchainImageViews() const { return viewImages_; };

    inline
    VkSwapchainKHR&
    getSwapchain() { return swapchain_; };


private:
    void
    initCreateInfo();
    
    void
    createSwapchain();

    void
    selectImageCount();

    void
    selectColorAndFormat();

    void
    selectQueueFamiliesImages();

    void
    selectPresentMode();

    void
    getSwapchainImages();

    void
    getImageViews();


};