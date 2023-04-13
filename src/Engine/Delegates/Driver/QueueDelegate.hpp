#pragma once
#include <utilities/MacrosAssert.hpp>
#include <Engine/utilities/typeAliases.hpp>
#include <utilities/Includes/graphicInclude.hpp>
#include <Engine/utilities/Structs/PhysicalDeviceSelector.hpp>

struct QueueDelegate
{
private:
    Opt<uint32_t> graphic_id, present_id; 

    VkQueue graphic_queue { VK_NULL_HANDLE };
    VkQueue present_queue { VK_NULL_HANDLE };

    float queue_priority { 1.f };

public:
    Vector<VkDeviceQueueCreateInfo> queues_info {};

public:
    QueueDelegate() = default;
    ~QueueDelegate() = default;

    void
    getQueueHandlers();

    void
    getQueueIds( VkPhysicalDevice& p_device, VkSurfaceKHR& p_surface ) noexcept;

    void
    fillQueueCreationInfo() noexcept;

    void
    obtainQueueHandlers( VkDevice& p_device ) noexcept;

    inline
    uint32_t getGraphicQueueID() const noexcept{ return graphic_id.value(); };

    inline
    uint32_t getPresentQueueID() const noexcept{ return present_id.value(); };

};

