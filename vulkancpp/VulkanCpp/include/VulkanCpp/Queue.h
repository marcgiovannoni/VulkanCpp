/*
 *  Queue.h
 *
 *  Created by Marc Giovannoni on 20/04/2016
 */

#ifndef     __QUEUE_H__
#define     __QUEUE_H__

//
// System includes
//

#include <vulkan/vulkan.h>

//
// Project includes
//

#include "VulkanCpp_Fwd.h"
#include "../src/Internal.hpp"

namespace VulkanCpp
{
    class Queue : public Internal::VkWrapper<VkQueue>
    {
        // TODO: Do not expose publicly
    public:
        Queue();
        explicit Queue(VkQueue vkQueue);
        ~Queue();

    public:
        Queue(const Queue&) = delete;
        Queue(Queue&&) = default;
        Queue& operator=(const Queue&) = delete;
        Queue& operator=(Queue&&) = default;

        void waitIdle();
        void submit(VkSubmitInfo* vkSubmitInfo);
    };
}

#endif  //  __QUEUE_H__
