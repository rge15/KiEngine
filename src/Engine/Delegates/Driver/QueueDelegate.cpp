#include "QueueDelegate.hpp"

void
QueueDelegate::getQueueIds( VkPhysicalDevice& p_device, VkSurfaceKHR& p_surface ) noexcept
{
    Vector<VkQueueFamilyProperties> family_queues;
    uint32_t family_count { 0 };
    vkGetPhysicalDeviceQueueFamilyProperties( p_device, &family_count, nullptr );
    family_queues.resize(family_count);
    vkGetPhysicalDeviceQueueFamilyProperties( p_device, &family_count, family_queues.data() );

    using namespace PhysicalDeviceSelector;

    int i = 0;
    for(auto& family : family_queues)
    {
        if( !(graphic_id.has_value()) && hasGraphicQueueFamily( family ) )
            graphic_id = i;

        if( !(present_id.has_value()) && hasPresentQueue( p_device, i, p_surface ));
            present_id = i;

        i++;
    }

    ASSERT( graphic_id.has_value() , "There's no graphic queue available in this device" )
    ASSERT( present_id.has_value() , "There's no present queue available in this device" )

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
QueueDelegate::fillQueueCreationInfo() noexcept
{
    Set<uint32_t> family_ids { graphic_id.value(), present_id.value() };
    
    VkDeviceQueueCreateInfo info {};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    info.pNext = nullptr;
    info.queueCount = 1;
    info.flags = 0;
    info.pQueuePriorities = &queue_priority; 

    for(auto id : family_ids)
    {
        info.queueFamilyIndex = id;
        queues_info.emplace_back( info );
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
QueueDelegate::obtainQueueHandlers( VkDevice& p_device ) noexcept
{
    ASSERT( graphic_id.has_value() , "There's no graphic family id to get the handler" )
    ASSERT( present_id.has_value() , "There's no present family id to get the handler" )

    vkGetDeviceQueue( p_device, graphic_id.value(), 0, &graphic_queue );
    vkGetDeviceQueue( p_device, present_id.value(), 0, &present_queue );
}
